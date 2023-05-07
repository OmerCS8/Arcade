#pragma once
#include "Game.h"
class CheckersGame :
    public Game
{
public:
	

	// Ctors
	CheckersGame(int rowSize = 8, int colSize = 8);
	CheckersGame(const CheckersGame& other);
	CheckersGame(CheckersGame&& other);
	CheckersGame(istream& in);

	const CheckersGame& operator=(CheckersGame&& other);

	// GET
	virtual int getMaxStoneAmount() const { return maxStonesAmount; }
	virtual int getMovePosAmount() const { return movePosAmount; }

	// checks if someone won
	virtual void isGameOver();

	virtual void makeMove(const vector<Position>& posArr);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

private:
	static const int maxStonesAmount = 12;
	static const int movePosAmount = 2;


	void moveStone(Stone* stone, const Position& dest);
	// checks if the recieved player has any valid moves left
	bool areMovesLeft(Player& p);
	void eatStone(const Position& toRemove, Color op);
};

