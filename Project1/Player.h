#pragma once
#include "ChessBishop.h"
#include "ChessQueen.h"
#include "ChessKing.h"
#include "ChessPawn.h"
#include "ChessRook.h"
#include "ChessKnight.h"
#include "CheckersPawn.h"
#include "CheckersKing.h"
class Player
{
public:
	// Ctors
	Player(Color color);
	Player(const Player& other);
	Player(Player&& other);
	Player(istream& in);

	// Dtor
	~Player();

	const Player& operator=(Player&& other);
	const Player& operator=(const Player& other);

	// GET
	int getStonesLeft() const { return _stones.size(); }
	vector<Stone*>& getStones() { return _stones; }
	const vector<Stone*>& getStones() const { return _stones; }
	Color getColor() const { return _color; }

	// SET
	void setStones(const vector<Stone*>& stones) { _stones = stones; }

	// load and save to file
	void save(ostream& out) const;
	void load(istream& in);
	void saveStones(ostream& out) const;
	void loadStones(istream& in);

protected:
	vector<Stone*> _stones;
	Color _color;

	// frees the stones array from memory
	void deleteStones();
};

