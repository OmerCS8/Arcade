#include "CheckersKing.h"

CheckersKing::CheckersKing(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'O' : 'X')
{
}

CheckersKing::CheckersKing(const CheckersKing& other) : chessAndCheckers_Stone(other)
{
	_mark = other._mark;
}

CheckersKing::CheckersKing(CheckersKing&& other): chessAndCheckers_Stone(move(other))
{
}

CheckersKing::CheckersKing(chessAndCheckers_Stone && other):chessAndCheckers_Stone(move(other))
{
	_mark = _player == Color::WHITE ? 'O' : 'X';
}

CheckersKing::CheckersKing(istream& in): chessAndCheckers_Stone(in)
{}

void CheckersKing::calcDangersAndValidMoves(Board & board)
{
	checkDiagonals(1, 1, board);
	checkDiagonals(1, -1, board);
	checkDiagonals(-1, 1, board);
	checkDiagonals(-1, -1, board);
}

void CheckersKing::checkDiagonals(int i, int j, Board & board)
{
	int k = 1;
	Position pos(_pos.getRow() + k * i, _pos.getCol() + k * j);
	while (board.isInBoard(pos) && !board.getCellAtPos(pos)->getHasStone()) {
		addValidMove(pos);
		++k;
		pos.setRow(_pos.getRow() + k * i);
		pos.setCol(_pos.getCol() + k * j);
	}
	Position dest(pos.getRow() + i, pos.getCol() + j);
	if (board.isInBoard(dest) && board.getCellAtPos(pos)->getColor() != _player && !board.getCellAtPos(dest)->getHasStone()) {
		addValidMove(dest);
		static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(pos)->getStone())->addDanger(_pos);
	}
}

void CheckersKing::save(ostream& out) const
{
	type tp = type::checkersKing;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void CheckersKing::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
