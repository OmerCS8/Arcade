#pragma once
#include "chessAndCheckers_Stone.h"
class ChessKing :
	public chessAndCheckers_Stone
{
public:
	ChessKing(const Position& pos, Color color);
	ChessKing(const ChessKing& other);
	ChessKing(ChessKing&& other);
	ChessKing(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);
};

