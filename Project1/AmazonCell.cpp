#include "AmazonCell.h"


AmazonCell::AmazonCell(const Position & pos):Cell(pos), _hasArrow(false)
{
}

AmazonCell::AmazonCell(istream& in): Cell(in)
{
	in.read(rCastC(&_hasArrow), sizeof(_hasArrow));
	loadMovesOrDangers(in);
}

AmazonCell::~AmazonCell()
{
	_validMovesOrDangers.clear();
}

vector<Position>& AmazonCell::getDangers() {
	if (_hasStone) {
		throw invalid_argument("This is not an empty cell");
	}
	else
		return _validMovesOrDangers;
}

vector<Position>& AmazonCell::getValidMoves() {
	if (!_hasStone) {
		throw invalid_argument("There is no Amazon in this cell");
	}
	else
		return _validMovesOrDangers;
}

const vector<Position>& AmazonCell::getDangers() const
{
	if (!_hasStone) {
		throw invalid_argument("There is no Amazon in this cell");
	}
	else
		return _validMovesOrDangers;
}

const vector<Position>& AmazonCell::getValidMoves() const
{
	if (_hasStone) {
		throw invalid_argument("This is not an empty cell");
	}
	else
		return _validMovesOrDangers;
}

bool AmazonCell::isInValidMovesOrDangers(const Position & pos) const
{
	for (int i = 0; i < _validMovesOrDangers.size(); ++i) {
		if (_validMovesOrDangers[i] == pos)
			return true;
	}
	return false;
}

void AmazonCell::addValidMoveOrDanger(const Position & pos)
{
	_validMovesOrDangers.push_back(pos);
}

void AmazonCell::resetValidMovesAndDangers()
{
	_validMovesOrDangers.clear();
}

void AmazonCell::save(ostream& out) const
{
	CellType ctp = CellType::amazon;
	out.write(rCastC_c(&ctp), sizeof(ctp));
	_pos.save(out);
	out.write(rCastC_c(&_hasStone), sizeof(_hasStone));
	out.write(rCastC_c(&_hasArrow), sizeof(_hasArrow));
	saveMovesOrDangers(out);
}

void AmazonCell::load(istream& in)
{
	Cell::load(in);
	in.read(rCastC(&_hasArrow), sizeof(_hasArrow));
	loadMovesOrDangers(in);
}

void AmazonCell::saveMovesOrDangers(ostream& out) const
{
	int size = _validMovesOrDangers.size();
	out.write(rCastC_c(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_validMovesOrDangers[i].save(out);
	}
}

void AmazonCell::loadMovesOrDangers(istream& in)
{
	int size;
	in.read(rCastC(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_validMovesOrDangers.push_back(Position(in));
	}
}

