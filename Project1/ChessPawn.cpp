#include "ChessPawn.h"

ChessPawn::ChessPawn(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'p' : 'P')
{
}

ChessPawn::ChessPawn(const ChessPawn& other) : chessAndCheckers_Stone(other)
{
}

ChessPawn::ChessPawn(ChessPawn&& other) : chessAndCheckers_Stone(move(other))
{
}

ChessPawn::ChessPawn(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessPawn::calcDangersAndValidMoves(Board& board)
{
	if (_player == Color::WHITE) {
		Position move(_pos.getRow() - 1, _pos.getCol());
		if (!board.getCellAtPos(move)->getHasStone())
		{
			if (isValidMove(_pos, move, board)) {
				addValidMove(move);
			}
			if (_pos.getRow() == 6) {
				move.setRow(4);
				if (!board.getCellAtPos(move)->getHasStone() && isValidMove(_pos, move, board)) {
					addValidMove(move);
				}
			}
		}
		Position diag(_pos.getRow() - 1, _pos.getCol() + 1);
		if (board.isInBoard(diag) && board.getCellAtPos(diag)->getHasStone() && board.getCellAtPos(diag)->getColor() != _player && isValidMove(_pos, diag, board)) {
			addValidMove(diag);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(diag)->getStone())->addDanger(_pos);
		}
		diag.setCol(_pos.getCol() - 1);
		if (board.isInBoard(diag) && board.getCellAtPos(diag)->getHasStone() && board.getCellAtPos(diag)->getColor() != _player && isValidMove(_pos, diag, board)) {
			addValidMove(diag);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(diag)->getStone())->addDanger(_pos);
		}
	}
	if (_player == Color::BLACK) {
		Position move(_pos.getRow() + 1, _pos.getCol());
		if (!board.getCellAtPos(move)->getHasStone())
		{
			if (isValidMove(_pos, move, board)) {
				addValidMove(move);
			}
			if (_pos.getRow() == 1) {
				move.setRow(3);
				if (!board.getCellAtPos(move)->getHasStone() && isValidMove(_pos, move, board)) {
					addValidMove(move);
				}
			}
		}
		Position diag(_pos.getRow() + 1, _pos.getCol() + 1);
		if (board.isInBoard(diag) && board.getCellAtPos(diag)->getHasStone() && board.getCellAtPos(diag)->getColor() != _player && isValidMove(_pos, diag, board)) {
			addValidMove(diag);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(diag)->getStone())->addDanger(_pos);
		}
		diag.setCol(_pos.getCol() - 1);
		if (board.isInBoard(diag) && board.getCellAtPos(diag)->getHasStone() && board.getCellAtPos(diag)->getColor() != _player && isValidMove(_pos, diag, board)) {
			addValidMove(diag);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(diag)->getStone())->addDanger(_pos);
		}
	}
}

void ChessPawn::save(ostream& out) const
{
	type tp = type::chessPawn;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessPawn::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
