#include "ChessQueen.h"

ChessQueen::ChessQueen(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'q' : 'Q')
{

}

ChessQueen::ChessQueen(const ChessQueen& other) : chessAndCheckers_Stone(other)
{
}

ChessQueen::ChessQueen(ChessQueen&& other): chessAndCheckers_Stone(move(other))
{
}

ChessQueen::ChessQueen(chessAndCheckers_Stone && other):chessAndCheckers_Stone(move(other))
{
	_mark = _player == Color::WHITE ? 'q' : 'Q';
}

ChessQueen::ChessQueen(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessQueen::calcDangersAndValidMoves(Board & board)
{
	checkDiagonals(-1, 0, board);
	checkDiagonals(-1, 1, board);
	checkDiagonals(0, 1, board);
	checkDiagonals(1, 1, board);
	checkDiagonals(1, 0, board);
	checkDiagonals(1, -1, board);
	checkDiagonals(0, -1, board);
	checkDiagonals(-1, -1, board);
}

void ChessQueen::save(ostream& out) const
{
	type tp = type::chessQueen;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessQueen::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
