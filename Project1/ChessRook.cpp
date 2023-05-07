#include "ChessRook.h"

ChessRook::ChessRook(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'r' : 'R')
{
}

ChessRook::ChessRook(const ChessRook& other) : chessAndCheckers_Stone(other)
{
}

ChessRook::ChessRook(ChessRook&& other): chessAndCheckers_Stone(move(other))
{
}

ChessRook::ChessRook(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessRook::calcDangersAndValidMoves(Board & board)
{
	checkDiagonals(1, 0, board);
	checkDiagonals(0, 1, board);
	checkDiagonals(-1, 0, board);
	checkDiagonals(0, -1, board);
}

void ChessRook::save(ostream& out) const
{
	type tp = type::chessRook;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessRook::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
