#pragma once
#include "Stone.h"
class chessAndCheckers_Stone;
enum class CellType {amazon , chessAndCheckers};
class Cell
{
public:
	// Ctor
	Cell(const Position& pos = Position());
	Cell(istream& in);

	virtual ~Cell() {};

	// GET
	inline const Position& getPos() const { return _pos; }
	inline bool getHasStone() const { return _hasStone; }
	inline Stone* getStone() const { return _stone; }
	inline Color getColor() const { return _stone->getColor(); }
	virtual bool getHasArrow() const { return false; }
	virtual vector<Position>& getDangers() ;
	virtual vector<Position>& getValidMoves() ;
	virtual const vector<Position>& getDangers() const;
	virtual const vector<Position>& getValidMoves() const;
	virtual int getValidMovesAmount() const;
	virtual int getDangersAmount() const;

	// SET
	inline void setPos(const Position& pos) { _pos = pos; }
	inline void setHasStone(bool hasStone) { _hasStone = hasStone; }
	inline void setStone(Stone* stone) { _stone = stone; }
	inline void setColor(Color color) { _stone->setColor(color); }

	// resets valid moves and dangers in stones for games where the stones has those params
	virtual void resetValidMovesAndDangers();

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

protected:
	Position _pos;
	bool _hasStone = false;
	Stone* _stone = nullptr;
};

