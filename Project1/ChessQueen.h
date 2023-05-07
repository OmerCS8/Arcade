#pragma once
#include "chessAndCheckers_Stone.h"
class ChessQueen :
	public chessAndCheckers_Stone
{
public:
	ChessQueen(const Position& pos, Color color);
	ChessQueen(const ChessQueen& other);
	ChessQueen(ChessQueen&& other);
	ChessQueen(chessAndCheckers_Stone&& other);
	ChessQueen(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

