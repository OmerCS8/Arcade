#include "Position.h"


ostream & operator<<(ostream & os, const Position & pos)
{
	os << "(" << pos._row + 1 << ", " << pos._col + 1 << ")";
	return os;
}

istream & operator>>(istream & is, Position & pos)
{
	is >> pos._row;
	is >> pos._col;
	return is;
}

Position::Position(int row, int col) : _row(row), _col(col)
{
}

Position::Position(const Position& pos)
{
	_row = pos._row;
	_col = pos._col;
}

Position::Position(istream& in)
{
	load(in);
}


bool Position::operator==(const Position& other) const
{
	return _row == other._row && _col == other._col;
}

bool Position::operator!=(const Position& other) const
{
	return !(*this == other);
}

void Position::save(ostream& out) const
{
	out.write(rCastC_c(&_row), sizeof(_row));
	out.write(rCastC_c(&_col), sizeof(_col));
}

void Position::load(istream& in)
{
	in.read(rCastC(&_row), sizeof(_row));
	in.read(rCastC(&_col), sizeof(_col));
}
