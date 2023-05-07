#pragma once
#include "chessAndCheckers_Stone.h"
class CheckersKing :
	public chessAndCheckers_Stone
{
public:
	// Ctor
	CheckersKing(const Position& pos, Color color);
	CheckersKing(const CheckersKing& other);
	CheckersKing(CheckersKing&& other);
	CheckersKing(chessAndCheckers_Stone&& other);
	CheckersKing(istream& in);

	virtual void calcDangersAndValidMoves(Board& board);

	// checks an offset line from the stone position for valid moves
	virtual void checkDiagonals(int i, int j, Board& board);

	virtual void checkSimpleDiagonals(int i, int j, Board& board) {};

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

};

