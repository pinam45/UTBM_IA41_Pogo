#ifndef UTBM_IA41_POGO_BOARD_HPP
#define UTBM_IA41_POGO_BOARD_HPP


class Board {
	//TODO
	// Stack stack[3][3] ;
	void move(int fromX, int fromY, int toX, int toY, int n);
	bool isAllowed(int fromX, int fromY, int toX, int toY, int n);
	friend int manhattanDist(int x, int y, int x2, int y2) ;
};


#endif //UTBM_IA41_POGO_BOARD_HPP
