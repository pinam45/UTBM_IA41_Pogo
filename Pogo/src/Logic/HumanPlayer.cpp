#include <Logic/HumanPlayer.hpp>

HumanPlayer::HumanPlayer(Pawn pawn, UI<PlayerPawnStackType, PLAYER_BOARD_WIDTH, PLAYER_BOARD_HEIGHT>& ui)
	: Player(pawn), m_ui(ui) {

}

PawnsMove HumanPlayer::chooseMove(const Board<PlayerPawnStackType, PLAYER_BOARD_WIDTH, PLAYER_BOARD_HEIGHT>& board) {
	return m_ui.chooseMove(board, m_pawn);
}
