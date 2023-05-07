#pragma once
#include "chessAndCheckers_Stone.h"

class CheckersPawn :
	public chessAndCheckers_Stone
{
public:
	// Ctor
	CheckersPawn(const Position& pos, Color color);
	CheckersPawn(const CheckersPawn& other);
	CheckersPawn(CheckersPawn&& other);
	CheckersPawn(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	virtual void checkDiagonals(int i, int j, Board& board) {}

	// checks offset from stone position for valid moves
	virtual void checkSimpleDiagonals(int i, int j, Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

