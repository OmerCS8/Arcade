#pragma once
#include "chessAndCheckers_Stone.h"
class ChessKnight :
	public chessAndCheckers_Stone
{
public:
	ChessKnight(const Position& pos, Color color);
	ChessKnight(const ChessKnight& other);
	ChessKnight(ChessKnight&& other);
	ChessKnight(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);
};

