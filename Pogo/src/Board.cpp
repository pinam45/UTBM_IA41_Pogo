#include <cstdlib>
#include "Board.hpp"

//TODO
void Board::move(int fromX, int fromY, int toX, int toY,int n) {

}

bool Board::isAllowed(int fromX, int fromY, int toX, int toY, int n) {
	return false;
}

int manhattanDist(int x, int y, int x2, int y2) {
	return abs(x - x2) + abs (y - y2);
}


