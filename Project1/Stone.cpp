#include "Stone.h"

Stone::Stone(const Position& pos, Color color, char mark):_player(color), _pos(pos), _mark(mark)
{
}

Stone::Stone(istream& in)
{
	load(in);
}

void Stone::save(ostream& out) const
{
	type tp = type::amazona;
	out.write(rCastC_c(&tp), sizeof(tp));
	out.write(rCastC_c(&_player), sizeof(_player));
	_pos.save(out);
	out.write(rCastC_c(&_mark), sizeof(_mark));
}

void Stone::load(istream& in)
{
	in.read(rCastC(&_player), sizeof(_player));
	_pos.load(in);
	in.read(rCastC(&_mark), sizeof(_mark));
}
