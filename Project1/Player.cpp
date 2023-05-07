#include "Player.h"

Player::Player(Color color) : _color(color), _stones(vector<Stone*>())
{
}

Player::Player(const Player& other) : Player(other._color)
{
	*this = other;
}

Player::Player(Player && other)
{
	*this = move(other);
}

Player::Player(istream& in)
{
	load(in);
}

Player::~Player()
{
	deleteStones();
}

const Player & Player::operator=(Player && other)
{
	if (this != &other) {
		deleteStones();
		_stones = other._stones;
		_color = other._color;
	}
	return *this;
}

const Player& Player::operator=(const Player& other)
{
	if (this != &other) {
		_color = other._color;
		try {
			for (int i = 0; i < other._stones.size(); ++i) {
				_stones.push_back(new Stone(*other._stones[i]));
			}
		}
		catch (bad_alloc& err) {
			for (int j = _stones.size(); j >= 0; --j) {
				delete _stones[j];
			}
			throw err;
		}
	}
	return *this;
}

void Player::save(ostream& out) const
{
	out.write(rCastC_c(&_color), sizeof(_color));
	saveStones(out);
}

void Player::load(istream& in)
{
	in.read(rCastC(&_color), sizeof(_color));
	loadStones(in);
}

void Player::saveStones(ostream& out) const
{
	int size = _stones.size();
	out.write(rCastC_c(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_stones[i]->save(out);
	}
}

void Player::loadStones(istream& in)
{
	int size;
	type tp;
	in.read(rCastC(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		in.read(rCastC(&tp), sizeof(tp));
		switch (tp)
		{
		case type::checkersKing:
			_stones.push_back(new CheckersKing(in));
			break;
		case type::checkersPawn:
			_stones.push_back(new CheckersPawn(in));
			break;
		case type::chessKing:
			_stones.push_back(new ChessKing(in));
			break;
		case type::chessQueen:
			_stones.push_back(new ChessQueen(in));
			break;
		case type::chessKnight:
			_stones.push_back(new ChessKnight(in));
			break;
		case type::chessBishop:
			_stones.push_back(new ChessBishop(in));
			break;
		case type::chessRook:
			_stones.push_back(new ChessRook(in));
			break;
		case type::chessPawn:
			_stones.push_back(new ChessPawn(in));
			break;
		case type::amazona:
			_stones.push_back(new Stone(in));
			break;
		}
	}
}

void Player::deleteStones()
{
	for (int i = 0; i < _stones.size(); ++i) {
		delete _stones[i];
	}
	_stones.clear();
}
