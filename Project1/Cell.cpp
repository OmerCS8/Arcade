#include "Cell.h"
#include "chessAndCheckers_Stone.h"

Cell::Cell(const Position& pos) : _pos(pos), _hasStone(false), _stone(nullptr)
{
}
Cell::Cell(istream& in): _stone(nullptr)
{
	load(in);
}
vector<Position>& Cell::getDangers() {
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getDangers();
}

vector<Position>& Cell::getValidMoves() {
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getValidMoves();
}

const vector<Position>& Cell::getDangers() const
{
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getDangers();
}

const vector<Position>& Cell::getValidMoves() const
{
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getValidMoves();
}

int Cell::getValidMovesAmount() const
{
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getValidMovesAmount();
}

int Cell::getDangersAmount() const
{
	if (!_hasStone) {
		throw invalid_argument("No Stone in this position");
	}
	else
		return static_cast<chessAndCheckers_Stone*>(_stone)->getDangersAmount();
}

void Cell::resetValidMovesAndDangers()
{
	if (_hasStone) {
		_stone->resetValidMovesAndDangers();
	}
}

void Cell::save(ostream& out) const
{
	CellType ctp = CellType::chessAndCheckers;
	out.write(rCastC_c(&ctp), sizeof(ctp));
	_pos.save(out);
	out.write(rCastC_c(&_hasStone), sizeof(_hasStone));
}

void Cell::load(istream& in)
{
	_pos.load(in);
	in.read(rCastC(&_hasStone), sizeof(_hasStone));
}
