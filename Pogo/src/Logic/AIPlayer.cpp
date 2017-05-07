#include <Logic/AIPlayer.hpp>
#include <chrono>
#include <cfloat>

PawnsMove AIPlayer::chooseMove(const Board<PawnStack16>& board)  {
	AIPlayer::Node root {};
	Board <PawnStack16> boardCopy (board);
	std::vector <PawnsMove> moves = firstMoves(board);

	auto t1 = std::chrono::high_resolution_clock::now();
	buildTree(m_depth,m_pawn,root,boardCopy);
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms elapsed buildTree" << std::endl;
	alphaBeta(root);
	t1 = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t2).count() << " ms elapsed AlphaBeta" << std::endl;

	unsigned int minValDepth = getMinDepth(root);
	std::vector <Node*> bestNodes;
	/* fill the list of best nodes (minimal depth and same val as root.val) */
	for(unsigned int i = 0; i < root.children.size() ; ++i) {
		if(root.children[i].val == root.val && getMinDepth(root.children[i]) == minValDepth - 1 )
			bestNodes.push_back(&root.children[i]);
	}

	/* choose a random best node */
	int ran = rand()%bestNodes.size();
	Node* chosenNode = bestNodes[ran];

	int index;
	/* find the index of the matching move*/
	for(unsigned i = 0 ; i < root.children.size(); ++i) {
		if(&root.children[i] == chosenNode) {
			index = i;
			break;
		}
	}

	PawnsMove choice = moves[index];
	return choice;
}

void AIPlayer::buildChildren(const PawnsMove& move, unsigned int depth, Pawn toPlay, Node& root, Board<PawnStack16>& board) const{
	Node child = Node{};
	board.apply(move);
	root.children.push_back(child);
	buildTree(depth -1,!toPlay,root.children.back(),board);
	// restore the board
	board.apply(PawnsMove{move.toX, move.toY, move.fromX, move.fromY, move.pawnNumber});
}
//TODO optimize buildTree
void AIPlayer::buildTree( unsigned int depth, Pawn toPlay, Node& root, Board<PawnStack16>& board) const {
	if( depth == 0 ) {
		root.val = eval(board);
		return;
	}


	for(unsigned int x = 0 ; x < 3; ++x) {
		for( unsigned int y = 0 ; y < 3 ; ++y) {
			unsigned int stackSize = board[x][y].size();
			if(stackSize && board[x][y].get(stackSize-1) == toPlay) {
				for(unsigned int i = 0; i < 3; ++i) {
					for(unsigned int j = 0; j < 3; ++j) {
						int dist = ManhattanDistance(x, y, i, j);

						if(stackSize >= 3 && (dist == 3 || dist == 1) )
							buildChildren(PawnsMove{x,y,i,j,3},depth,toPlay,root,board);
						else if(stackSize >= 2 && dist == 2)
							buildChildren(PawnsMove{x,y,i,j,2},depth,toPlay,root,board);

						if(dist == 1)
							buildChildren(PawnsMove{x,y,i,j,1},depth,toPlay,root,board);
					}
				}
			}
		}
	}
	// case the game ends before depth == 0
	root.val = eval(board);
}

std::vector<PawnsMove> AIPlayer::firstMoves(const Board<PawnStack16>& board) const {
	std::vector <PawnsMove> firstMoves ;
	for(unsigned int x = 0 ; x < 3; ++x) {
		for( unsigned int y = 0 ; y < 3 ; ++y) {
			unsigned int stackSize = board[x][y].size();
			if(stackSize && board[x][y].get(stackSize-1) == this->m_pawn) {
				for(unsigned int i = 0; i < 3; ++i) {
					for(unsigned int j = 0; j < 3; ++j) {
						int dist = ManhattanDistance(x, y, i, j);

						if(stackSize >= 3 && (dist == 3 || dist == 1))
							firstMoves.push_back(PawnsMove{x,y,i,j,3});
						else if(stackSize >= 2 && dist == 2)
							firstMoves.push_back(PawnsMove{x,y,i,j,2});
						if(dist == 1)
							firstMoves.push_back(PawnsMove{x,y,i,j,1});
					}
				}
			}
		}
	}
	return  firstMoves;
}

float AIPlayer::eval(const Board<PawnStack16>& board) const{ //TODO better val
	float eval = 0;
	float stackCount = 0 ;
	for(int x = 0; x < 3; ++x) {
		for(int y =0 ; y < 3 ; ++y) {
			if(board[x][y].size()) {
				++stackCount;
				if(board[x][y].get(board[x][y].size()-1) == this->m_pawn) // ia controls the stack
					++eval;
			}
		}
	}
	return eval/stackCount;
}

void AIPlayer::alphaBeta(AIPlayer::Node& root) {
	root.val = maxValue(root,-FLT_MAX,FLT_MAX);
}

float AIPlayer::maxValue(AIPlayer::Node & root, float alpha, float beta) {
	if(root.children.empty())
		return root.val;

	root.val = -FLT_MAX;
	for(AIPlayer::Node& n : root.children) {
		root.val = std::max(root.val,minValue(n,alpha,beta));
	/*	if(root.val >= beta)
			return root.val;
		alpha = std::max(alpha,root.val);
	 */
	}
	return root.val;
}

float AIPlayer::minValue(AIPlayer::Node & root,float alpha, float beta) {
	if(root.children.empty())
		return root.val;

	root.val = FLT_MAX;
	for(AIPlayer::Node& n : root.children) {
		root.val = std::min(root.val,maxValue(n,alpha,beta));
	/*	if(root.val <= alpha)
			return root.val;
		beta = std::min(beta,root.val);
	 */
	}
	return root.val;
}

unsigned int AIPlayer::getMinDepth(const Node& root) {
	if(root.children.empty())
		return 0;

	unsigned int min = UINT32_MAX;
	for(const Node& n : root.children) {
		if(n.val == root.val) {
			unsigned int depth = 1 + getMinDepth(n)	;
			if(min > depth)
				min = depth;
		}
	}

	return min;
}
