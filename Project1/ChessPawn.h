#pragma once
#include "chessAndCheckers_Stone.h"
class ChessPawn :
	public chessAndCheckers_Stone
{
public:
	ChessPawn(const Position& pos, Color color);
	ChessPawn(const ChessPawn& other);
	ChessPawn(ChessPawn&& other);
	ChessPawn(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

