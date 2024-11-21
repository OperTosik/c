#include "snakePlug.h"

// class Cell
Cell::Cell(): x(0.), y(0.) {}

Cell::Cell(double xx, double yy): x(xx), y(yy) {}

double Cell::getX(const Cell& cell) {
    return cell.x;
}

double Cell::getY(const Cell& cell) {
    return cell.y;
}

//class IntCell

IntCell::IntCell(int nn, int mm): n(nn), m(mm) {
    std::vector<std::vector<Cell>> tmp(n, std::vector<Cell>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            tmp[i][j] = Cell((double)i, (double)j);
        }
    }
}