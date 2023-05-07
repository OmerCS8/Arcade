#pragma once
#include "chessAndCheckers_Stone.h"
class ChessBishop :
	public chessAndCheckers_Stone
{
public:
	ChessBishop(const Position& pos, Color color);
	ChessBishop(const ChessBishop& other);
	ChessBishop(ChessBishop&& other);
	ChessBishop(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

