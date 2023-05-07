#pragma once
#include "Position.h"
enum class Color{WHITE,BLACK};
static string ColorStr[]{ "White", "Black" };
enum class type { checkersKing, checkersPawn, chessKing, chessQueen, chessKnight, chessBishop, chessRook, chessPawn, amazona };

template <class T>
void mySwap(T* a, T* b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

class Stone
{
public:
	// Ctor
	Stone(const Position& pos, Color color, char mark);
	Stone(istream& in);

	// Dtor
	virtual ~Stone() {}

	// GET
	inline Color getColor() const { return _player; }
	inline const Position& getPos() const { return _pos; }
	inline const char getMark() const { return _mark; }

	// SET
	inline void setColor(Color color) { _player = color; }
	inline void setPos(const Position& pos) { _pos = pos; }
	inline void setMark(char mark) { _mark = mark; }

	virtual void resetValidMovesAndDangers() {};

	virtual bool isInValidPos(const Position& pos) { return false; };

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

protected:
	Color _player;
	Position _pos;
	char _mark;
};

