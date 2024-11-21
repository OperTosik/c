#ifndef PROGRAM
#define PROGRAM 1

#include <vector>

class Cell;
class IntCell;
class Snake;

class Cell {
private:
    double x;
    double y;
public:
    Cell();
    Cell(double xx, double yy);
    Cell(const Cell& cell);

    double getX(const Cell& cell);
    double getY(const Cell& cell);
};

class IntCell {
private:
    int n;
    int m;
public:
    std::vector<std::vector<Cell>> intCell;

    IntCell(int nn, int mm);

    
};

#endif