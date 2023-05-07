#pragma once
#include "Game.h"
#include "Stone.h"
#include "AmazonCell.h"

class AmazonGame :
    public Game
{
public:

	// Ctors
	AmazonGame(int rowSize = 10, int colSize = 10);
	AmazonGame(const AmazonGame& other);
	AmazonGame(AmazonGame&& other);
	AmazonGame(istream& in);


	const AmazonGame& operator=(AmazonGame&& other);

	// GET
	virtual int getMaxStoneAmount() const { return maxStonesAmount; }
	virtual int getMovePosAmount() const { return movePosAmount; }


	// iterates over all the cells and calculates the valid moves or dangers from each cell
	virtual void calcDangersAndValidMoves();

	// this function recieves 3 positions for a move and checks if the move is valid AFTER you move the Amazon
	// if so, it returns true
	bool isValidMoveWithoutStone(const Position& src, const Position& dest, const Position& arrow);

	// checks if someone won
	virtual void isGameOver();

	virtual void makeMove(const vector<Position>& posArr);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

private:
	static const int maxStonesAmount = 4;
	static const int movePosAmount = 3;

	// move Amazon according to the move recieved
	void moveStone(const Position& src, const Position& dest);
	// shoots arrow at the recieved position
	void shootArrow(const Position& arrow);
	// gets a cell and row and col offsets to calculate moves from cell in the offset direction
	void calcMovesFromCell(Cell* cell, int i, int j);

};

