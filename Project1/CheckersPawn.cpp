#include "CheckersPawn.h"

CheckersPawn::CheckersPawn(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'o' : 'x')
{
}

CheckersPawn::CheckersPawn(const CheckersPawn& other): chessAndCheckers_Stone(other)
{
}

CheckersPawn::CheckersPawn(CheckersPawn&& other) : chessAndCheckers_Stone(move(other))
{
}

CheckersPawn::CheckersPawn(istream& in) : chessAndCheckers_Stone(in)
{
}

void CheckersPawn::calcDangersAndValidMoves(Board & board)
{
	if (_player == Color::WHITE) {
		checkSimpleDiagonals(1, 1, board);
		checkSimpleDiagonals(1, -1, board);
	}
	else if (_player == Color::BLACK) {
		checkSimpleDiagonals(-1, 1, board);
		checkSimpleDiagonals(-1, -1, board);
	}
}

void CheckersPawn::checkSimpleDiagonals(int i, int j, Board& board)
{
	int row = _pos.getRow();
	int col = _pos.getCol();;
	Position pos(row + i, col + j);
	if (board.isInBoard(pos) && !board.getCellAtPos(Position(row + i,col + j))->getHasStone()) {
		addValidMove(pos);
	}
	else {
		pos.setRow(row + 2 * i);
		pos.setCol( col + 2 * j);
		if (board.isInBoard(pos) && board.getCellAtPos(Position(row + i,col + j))->getColor() != _player && !board.getCellAtPos(Position(row + 2 * i,col + 2 * j))->getHasStone()) {
			addValidMove(pos);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(Position(row + i,col + j))->getStone())->addDanger(_pos);
		}
	}
}

void CheckersPawn::save(ostream& out) const
{
	type tp = type::checkersPawn;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void CheckersPawn::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
