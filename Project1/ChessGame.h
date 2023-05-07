#pragma once
#include "Game.h"
class ChessGame :
    public Game
{
public:
	// Ctors
	ChessGame(int rowSize = 8, int colSize = 8);
	ChessGame(const ChessGame& other);
	ChessGame(ChessGame&& other);
	ChessGame(istream& in);

	const ChessGame& operator=(ChessGame&& other);


	// checks if someone won
	virtual void isGameOver();

	virtual void makeMove(const vector<Position>& posArr);

	// GET
    virtual int getMaxStoneAmount() const { return maxStonesAmount; }
	virtual int getMovePosAmount() const { return movePosAmount; }

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

private:
	static const int maxStonesAmount = 16;
	static const int movePosAmount = 2;

	void eatStone(const Position& toRemove, Color op);
	void moveStone(Stone* stone, const Position& dest);
};

