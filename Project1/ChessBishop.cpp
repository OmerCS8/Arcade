#include "ChessBishop.h"

ChessBishop::ChessBishop(const Position & pos, Color color) :chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'b' : 'B')
{
}

ChessBishop::ChessBishop(const ChessBishop& other) : chessAndCheckers_Stone(other)
{
}

ChessBishop::ChessBishop(ChessBishop&& other): chessAndCheckers_Stone(move(other))
{
}

ChessBishop::ChessBishop(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessBishop::calcDangersAndValidMoves(Board & board)
{
	checkDiagonals(1, 1, board);
	checkDiagonals(1, -1, board);
	checkDiagonals(-1, 1, board);
	checkDiagonals(-1, -1, board);
}

void ChessBishop::save(ostream& out) const
{
	type tp = type::chessBishop;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessBishop::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}

