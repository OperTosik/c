CC = g++-14 $(CFLAGS)
CFLAGS = -O0 -g -std=c++14

# russianWords: russianWords.cpp utf8/utf8.h utf8/utf8.cpp
# 	$(CC) -o russianWords russianWords.cpp utf8/utf8.cpp

# clear:
# 	rm -f russianWords russianWords.exe
# 	cd utf8; make clean

app: vigenere.cpp utf8.h utf8.cpp
	$(CC) -o app vigenere.cpp utf8.cpp

clear:
	rm -f app
