#pragma once
#include "chessAndCheckers_Stone.h"
class ChessRook :
	public chessAndCheckers_Stone
{
public:
	ChessRook(const Position& pos, Color color);
	ChessRook(const ChessRook& other);
	ChessRook(ChessRook&& other);
	ChessRook(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

