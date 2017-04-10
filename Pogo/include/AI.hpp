#ifndef UTBM_IA41_POGO_AI_HPP
#define UTBM_IA41_POGO_AI_HPP


#include <Board.hpp>
#include "Node.hpp"



class AI {
	//TODO
	Node root;
	Node current;
	Board board;
	int depth ;

	double eval () ;
	void buildTree(int depth);
	void minMax();


};


#endif //UTBM_IA41_POGO_AI_HPP
