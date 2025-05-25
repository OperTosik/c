//
// File "func.cpp"
// Test of small graphic package: Draw a graph of function y = f(x)
//
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gwindow.h"

const int DX = 80;
const int DY = 80;
const int LINE_WIDTH = 4;

//--------------------------------------------------
// Definition of our main class "MyWindow"
//
class MyWindow: public GWindow {    // Our main class
public:
    char field[3][3];
    bool initialized;
    Font textFont;
    bool IAmX;
    int readChannel;
    int writeChannel;
    bool finished;

    MyWindow();
    void initialize();
    void animate();
    void readMove();

    virtual void onExpose(XEvent& event);
    virtual void onKeyPress(XEvent& event);
    virtual void onButtonPress(XEvent& event);
    virtual bool onWindowClosing();
};

//----------------------------------------------------------
// Implementation of class "MyWindow"

MyWindow::MyWindow():
    initialized(false),
    textFont(0),
    IAmX(false),
    readChannel(0),
    writeChannel(0),
    finished(false)
{
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
             field[x][y] = 0;
        }
    }
}

static const char* const DEFAULT_TEXT_FONT =
    "-*-*-bold-r-*-*-24-*-*-*-*-*-*";

void MyWindow::initialize() {
    bool fontLoaded = false;

    // Try to load the default font
    if ((textFont = loadFont(DEFAULT_TEXT_FONT)) != 0) {
        fontLoaded = true;
    } else {
        fprintf(
            stderr, 
            "Cannot load the font with name \"%s\"\n", 
            DEFAULT_TEXT_FONT
        );
    }

    // In case of falure, try to load a font with the name "fixed"
    if (!fontLoaded) {
        if ((textFont = loadFont("fixed")) != 0)
            fontLoaded = true;
    }
    if (!fontLoaded) {
        perror("Cannot load a font with name \"fixed\"");
        exit(1);
    }

    setFont(textFont);
}

void MyWindow::readMove() {
    if (!finished) {
        char move[3];
        int res = read(readChannel, move, 3);
        if (res == 3) {
            printf(
                "Read: x=%d y=%d c=%d\n",
                (int) move[0], (int) move[1], (int) move[2]
            );
            int x = move[0]; int y = move[1];
            int c = move[2];
            field[x][y] = (char) c;
            redraw();
        } else if (res <= 0) {
            finished = true;
            printf("Read: res=%d (connection broken).\n", res);
        }
    }
}

//
// Process the Expose event: draw in the window
//
void MyWindow::onExpose(XEvent& /* event */) {
    if (!initialized)
        initialize();

    // Erase a window
    setForeground(getBackground());
    fillRectangle(m_RWinRect);

    // Draw field
    setForeground("black");
    for (int x = 0; x < 3; ++x) {
        fillRectangle(
            I2Rectangle(
                I2Point(DX*x - LINE_WIDTH, 0),
                LINE_WIDTH, DY*3
            )
        );
    }
    for (int y = 0; y < 3; ++y) {
        fillRectangle(
            I2Rectangle(
                I2Point(0, DX*y - LINE_WIDTH),
                DY*3, LINE_WIDTH
            )
        );
    }

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
             if (field[x][y] == 1) {
                // Cross
                drawString(
                    x*DX + DX/3,
                    y*DX + DX*2/3,
                    "X"
                );
             } else if (field[x][y] == 2) {
                // Null
                drawString(
                    x*DX + DX/3,
                    y*DX + DX*2/3,
                    "O"
                );
             }
        }
    }
}

//
// Process the KeyPress event: 
// if "q" is pressed, then close the window
//
void MyWindow::onKeyPress(XEvent& event) {
    KeySym key;
    char keyName[256];
    int nameLen = XLookupString(&(event.xkey), keyName, 255, &key, 0);
    printf("KeyPress: keycode=0x%x, state=0x%x, KeySym=0x%x\n",
        event.xkey.keycode, event.xkey.state, (int) key);
    if (nameLen > 0) {
        keyName[nameLen] = 0;
        printf("\"%s\" button pressed.\n", keyName);
        if (keyName[0] == 'q') { // quit => close window
            destroyWindow();
        }
    }
}

// Process mouse click
void MyWindow::onButtonPress(XEvent& event) {
    int x = event.xbutton.x;
    int y = event.xbutton.y;
    unsigned int mouseButton = event.xbutton.button;

    printf("Mouse click: x=%d, y=%d, button=%d\n", x, y, mouseButton);

    int ix = x / DX;
    int iy = y / DY;

    int c = 1;  // Cross
    if (!IAmX)
        c = 2;  // Null
    field[ix][iy] = c;
    char line[3];
    line[0] = (char) ix;
    line[1] = (char) iy;
    line[2] = (char) c;
    if (!finished) {
        int res = write(writeChannel, line, 3);
        if (res < 0) {
            finished = true;
            printf("Write: res=%d (connection broken)\n", res);
        }
    }
    redraw();
}

bool MyWindow::onWindowClosing() {
    close(readChannel);
    close(writeChannel);
    return true;
}

//
// End of class MyWindow implementation
//----------------------------------------------------------

/////////////////////////////////////////////////////////////
// Main: initialize X, create an instance of MyWindow class,
//       and start the message loop
int main() {
    int fdX[2], fdO[2];

    if (pipe(fdX) < 0) {
        perror("Pipe X error"); exit(-1);
    }
    if (pipe(fdO) < 0) {
        perror("Pipe O error"); exit(-1);
    }

    int pid = fork();
    if (pid < 0) {
        perror("Fork error"); exit(-1);
    }

    // Initialize X stuff
    if (!GWindow::initX()) {
        printf("Could not connect to X-server.\n");
        exit(1);
    }

    MyWindow w;
    const char* windowTitle = "X/O";
    int windowX = 10;
    int windowY = 10;
    if (pid != 0) {
        w.IAmX = true;
        close(fdO[0]);
        close(fdX[1]);
        w.readChannel = fdX[0];
        w.writeChannel = fdO[1];
    } else {
        windowTitle = "O/X";
        windowX = 200;
        w.IAmX = false;
        close(fdO[1]);
        close(fdX[0]);
        w.readChannel = fdO[0];
        w.writeChannel = fdX[1];
    }

    if (pid == 0) {
        windowX = 200;
        windowY = 20;
    }

    w.createWindow(
        I2Rectangle(                    // Window frame rectangle:
            I2Point(windowX, windowY),  //     left-top corner
            DX*3,    //     width
            DY*3     //     height
        ),
        R2Rectangle(                    // Coordinate rectangle:
            R2Point(-12., -9.),         //     bottom-right corner
            24., 18.                    //     width, height
        ),
        windowTitle
    );
    w.setBackground("lightGray");

    //... GWindow::messageLoop();
    // Message loop, animation
    XEvent e;
    while (GWindow::m_NumCreatedWindows > 0) {
        if (GWindow::getNextEvent(e)) {
            GWindow::dispatchEvent(e);
        } else {
            int maxFD = w.readChannel;
            fd_set readSet;
            FD_ZERO(&readSet);
            FD_SET(w.readChannel, &readSet);
            fd_set* r = &readSet;
            if (w.finished) {
                maxFD = 0;
                r = NULL;
            }

            // Sleep a bit (we use select for sleeping)
            timeval dt;
            dt.tv_sec = 0;
            dt.tv_usec = 50000; // sleeping time 0.05 sec
            int res = select(maxFD + 1, r, 0, 0, &dt);
            if (res > 0) {
                printf("Select: res=%d\n", res);
                w.readMove();
            }
        }
    }
    GWindow::closeX();

    if (pid != 0)
        wait(NULL);
    return 0;
}
