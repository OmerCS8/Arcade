#pragma once
#include "AmazonCell.h"
class Board
{
public:
	// Ctors
	Board();
	Board(int rowSize, int colSize);
	Board(const Board& other);
	Board(Board&& other);
	Board(istream& in);
	// Dtor
	virtual ~Board();

	const Board& operator=(Board&& other);
	const Board& operator=(const Board& other);

	// GET
	inline vector<vector<Cell*>>& getBoard() { return _board; }
	inline const vector<vector<Cell*>>& getBoard() const { return _board; }
	inline int getRowSize() const { return _rowSize; }
	inline int getColSize() const { return _colSize; }
	const Cell* getCellAtPos(const Position& pos) const;
	Cell* getCellAtPos(const Position& pos);

	// recieves a player and a stone mark and returns the position on board of the first stone of that mark in the player stones array
	const Position& getStonePos(Color player, char mark);

	// checks if the recieved position is in the board
	bool isInBoard(const Position& pos) const;
	bool isInBoard(const Position& pos);

	// resets all valid moves and dangers of all cells
	void resetValidMovesAndDangers();

	// Print Operator
	friend ostream& operator<<(ostream& os, const Board& board);

	void save(ostream& out) const;
	void load(istream& in);
	void saveBoard(ostream& out) const;
	void loadBoard(istream& in);

protected:
	vector<vector<Cell*>> _board;
	int _rowSize;
	int _colSize;

	// frees the cells array from memory
	void deleteBoard();
};

