#include "ChessKnight.h"

ChessKnight::ChessKnight(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'n' : 'N')
{
}

ChessKnight::ChessKnight(const ChessKnight& other) : chessAndCheckers_Stone(other)
{
}

ChessKnight::ChessKnight(ChessKnight&& other): chessAndCheckers_Stone(move(other))
{
}

ChessKnight::ChessKnight(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessKnight::calcDangersAndValidMoves(Board & board)
{
	checkSimpleDiagonals(2, 1, board);
	checkSimpleDiagonals(2, -1, board);
	checkSimpleDiagonals(1, 2, board);
	checkSimpleDiagonals(1, -2, board);
	checkSimpleDiagonals(-2, 1, board);
	checkSimpleDiagonals(-2, -1, board);
	checkSimpleDiagonals(-1, 2, board);
	checkSimpleDiagonals(-1, -2, board);
}

void ChessKnight::save(ostream& out) const
{
	type tp = type::chessKnight;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessKnight::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}


