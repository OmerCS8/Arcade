#pragma once
#include "Cell.h"
class AmazonCell :
    public Cell
{
public:
	// Ctor
	AmazonCell(const Position& pos = Position());
	AmazonCell(istream& in);

	// Dtor
	virtual ~AmazonCell();
	
	// GET
	virtual bool getHasArrow() const { return _hasArrow; }
	int getValidMovesOrDangersAmount() const { return _validMovesOrDangers.size(); }
	inline vector<Position> getValidMovesOrDangers() const { return _validMovesOrDangers; }
	virtual vector<Position>& getDangers() ;
	virtual vector<Position>& getValidMoves() ;
	virtual const vector<Position>& getDangers() const;
	virtual const vector<Position>& getValidMoves() const;
	virtual int getValidMovesAmount() const { return _validMovesOrDangers.size(); }
	virtual int getDangersAmount() const { return _validMovesOrDangers.size(); }

	// SET
	void setValidMovesOrDangers(const vector<Position>& validMoves) { _validMovesOrDangers = validMoves; }
	inline void setHasArrow(bool hasArrow) { _hasArrow = hasArrow; }

	// checks if the recieved position is in the valid moves or dangers array of the current cell
	bool isInValidMovesOrDangers(const Position& pos) const;
	// add the recieved position to valid moves or dangers array of the current cell
	void addValidMoveOrDanger(const Position& pos);
	// reset the valid moves and dangers of the current cell
	virtual void resetValidMovesAndDangers();

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);
	virtual void saveMovesOrDangers(ostream& out) const;
	void loadMovesOrDangers(istream& in);

private:
	bool _hasArrow;
	vector<Position> _validMovesOrDangers;
};

