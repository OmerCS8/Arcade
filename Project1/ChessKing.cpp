#include "ChessKing.h"

ChessKing::ChessKing(const Position & pos, Color color):chessAndCheckers_Stone(pos, color, color == Color::WHITE ? 'k' : 'K')
{
}

ChessKing::ChessKing(const ChessKing& other) :chessAndCheckers_Stone(other)
{
}

ChessKing::ChessKing(ChessKing&& other): chessAndCheckers_Stone(move(other))
{
}

ChessKing::ChessKing(istream& in) : chessAndCheckers_Stone(in)
{
}

void ChessKing::calcDangersAndValidMoves(Board & board)
{
	checkSimpleDiagonals(-1, 0, board);
	checkSimpleDiagonals(-1, 1, board);
	checkSimpleDiagonals(0, 1, board);
	checkSimpleDiagonals(1, 1, board);
	checkSimpleDiagonals(1, 0, board);
	checkSimpleDiagonals(1, -1, board);
	checkSimpleDiagonals(0, -1, board);
	checkSimpleDiagonals(-1, -1, board);
}

void ChessKing::save(ostream& out) const
{
	type tp = type::chessKing;
	out.write(rCastC_c(&tp), sizeof(tp));
	chessAndCheckers_Stone::save(out);
}

void ChessKing::load(istream& in)
{
	chessAndCheckers_Stone::load(in);
}
