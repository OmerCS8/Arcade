#include "chessAndCheckers_Stone.h"

chessAndCheckers_Stone::chessAndCheckers_Stone(const Position& pos, Color color, char mark):Stone(pos,color, mark),
_validMoves(vector<Position>()),  _dangers(vector<Position>())
{
}
chessAndCheckers_Stone::chessAndCheckers_Stone(const chessAndCheckers_Stone& other) : Stone(other), _validMoves(vector<Position>()), _dangers(vector<Position>())
{
	*this = other;
}
chessAndCheckers_Stone::chessAndCheckers_Stone(chessAndCheckers_Stone&& other):
	Stone(other._pos, other._player, other._mark), 
	_dangers(vector<Position>()),
	_validMoves(vector<Position>())
{
	*this = move(other);
}
chessAndCheckers_Stone::chessAndCheckers_Stone(istream& in): Stone(in)
{
	loadValidMoves(in);
	loadDangers(in);
}
chessAndCheckers_Stone::~chessAndCheckers_Stone()
{
	_dangers.clear();
	_validMoves.clear();
}

const chessAndCheckers_Stone& chessAndCheckers_Stone::operator=(const chessAndCheckers_Stone& other)
{
	if (this != &other) {
		_validMoves = other._validMoves;
		_dangers = other._dangers;
	}
	return *this;
}

const chessAndCheckers_Stone& chessAndCheckers_Stone::operator=(chessAndCheckers_Stone&& other)
{
	if (this != &other)
	{
		Stone::operator=(move(other));

		_dangers = move(other._dangers);
		_validMoves = move(other._validMoves);
	}

	return *this;
}

void chessAndCheckers_Stone::resetValidMovesAndDangers()
{
	_dangers.clear();
	_validMoves.clear();
}
void chessAndCheckers_Stone::checkDiagonals(int i, int j, Board & board)
{
	int k = 1;
	Position pos(_pos.getRow() + k * i, _pos.getCol() + k * j);
	while (board.isInBoard(pos) && !board.getCellAtPos(pos)->getHasStone()) {
		if(isValidMove(_pos, pos, board))
			addValidMove(pos);
		++k;
		pos.setRow(_pos.getRow() + k * i);
		pos.setCol(_pos.getCol() + k * j);
	}
	if (board.isInBoard(pos) && board.getCellAtPos(pos)->getColor() != _player && isValidMove(_pos, pos, board)) {
		addValidMove(pos);
		static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(pos)->getStone())->addDanger(_pos);
	}
}
void chessAndCheckers_Stone::checkSimpleDiagonals(int i, int j, Board & board)
{
	int row = _pos.getRow();
	int col = _pos.getCol();;
	Position pos(row + i, col + j);
	if (board.isInBoard(pos) && isValidMove(_pos, pos, board)) {
		if(!board.getCellAtPos(Position(row + i, col + j))->getHasStone())
			addValidMove(pos);
		else if (board.getCellAtPos(Position(row + i, col + j))->getHasStone() && board.getCellAtPos(Position(row + i, col + j))->getColor() != _player) {
			addValidMove(pos);
			static_cast<chessAndCheckers_Stone*>(board.getCellAtPos(pos)->getStone())->addDanger(_pos);
		}
	}
}
void chessAndCheckers_Stone::addDanger(Position& pos) {
	_dangers.push_back(pos);
}
void chessAndCheckers_Stone::addValidMove(Position& pos) {
	_validMoves.push_back(pos);
}

bool chessAndCheckers_Stone::isInValidPos(const Position& pos)
{
	for (int i = 0; i < _validMoves.size(); i++) {
		if (pos.getRow() == _validMoves[i].getRow() && pos.getCol() == _validMoves[i].getCol())
			return true;
	}
	return false;
}



bool chessAndCheckers_Stone::isKingThreatened(Color player, Board& board)
{
	Position kingPos = board.getStonePos(player,'k');
	if (searchOffestLine(0, 1, "rq", 2, player, kingPos, board) || searchOffestLine(1, 0, "rq", 2, player, kingPos, board) || searchOffestLine(-1, 0, "rq", 2, player, kingPos, board) || searchOffestLine(0, -1, "rq", 2, player, kingPos, board)) {
		return true;
	}
	if (searchOffestLine(1, 1, "qb", 2, player, kingPos, board) || searchOffestLine(-1, 1, "qb", 2, player, kingPos, board) || searchOffestLine(-1, -1, "qb", 2, player, kingPos, board) || searchOffestLine(1, -1, "qb", 2, player, kingPos, board)) {
		return true;
	}
	if (
		searchOffset(2, 1, 'n', player, kingPos, board) || searchOffset(-2, 1, 'n', player, kingPos, board) ||
		searchOffset(-2, -1, 'n', player, kingPos, board) || searchOffset(2, -1, 'n', player, kingPos, board) ||
		searchOffset(1, 2, 'n', player, kingPos, board) || searchOffset(-1, 2, 'n', player, kingPos, board) ||
		searchOffset(-1, -2, 'n', player, kingPos, board) || searchOffset(1, -2, 'n', player, kingPos, board))
		return true;
	if (player == Color::WHITE && (searchOffset(-1, -1, 'p', player, kingPos, board) || searchOffset(-1, 1, 'p', player, kingPos, board)))
		return true;
	if (player == Color::BLACK && (searchOffset(1, -1, 'p', player, kingPos, board) || searchOffset(1, 1, 'p', player, kingPos, board)))
		return true;
	if (
		searchOffset(-1, -1, 'k', player, kingPos, board) || searchOffset(-1, 0, 'k', player, kingPos, board) ||
		searchOffset(-1, 1, 'k', player, kingPos, board) || searchOffset(0, 1, 'k', player, kingPos, board) ||
		searchOffset(1, 1, 'k', player, kingPos, board) || searchOffset(1, 0, 'k', player, kingPos, board) ||
		searchOffset(1, -1, 'k', player, kingPos, board) || searchOffset(0, -1, 'k', player, kingPos, board))
		return true;
	return false;
}

void chessAndCheckers_Stone::save(ostream& out) const
{
	out.write(rCastC_c(&_player), sizeof(_player));
	_pos.save(out);
	out.write(rCastC_c(&_mark), sizeof(_mark));
	saveValidMoves(out);
	saveDangers(out);
}

void chessAndCheckers_Stone::load(istream& in)
{
	Stone::load(in);
	loadValidMoves(in);
	loadDangers(in);
}

bool chessAndCheckers_Stone::searchOffestLine(int i, int j, string dangeringPieces, int dangeringPiecesAmount, Color player, const Position& kingPos, Board& board)
{
	int k = 1;
	Position pos(kingPos.getRow() + k * i, kingPos.getCol() + k * j);
	while (board.isInBoard(pos) && !board.getCellAtPos(pos)->getHasStone()) {
		++k;
		pos.setRow(kingPos.getRow() + k * i);
		pos.setCol(kingPos.getCol() + k * j);
	}
	if (board.isInBoard(pos) && board.getCellAtPos(pos)->getColor() != player) {
		for (int i = 0; i < dangeringPiecesAmount; ++i) {
			if (player == Color::BLACK && board.getCellAtPos(pos)->getStone()->getMark() == tolower(dangeringPieces[i])) {
				return true;
			}
			else if (player == Color::WHITE && board.getCellAtPos(pos)->getStone()->getMark() == toupper(dangeringPieces[i])) {
				return true;
			}
		}
	}
	return false;
}

bool chessAndCheckers_Stone::searchOffset(int i, int j, char dangerPiece, Color player, const Position& kingPos, Board& board)
{
	Position pos(kingPos.getRow() + i, kingPos.getCol() + j);
	if (board.isInBoard(pos) && player == Color::BLACK && board.getCellAtPos(pos)->getHasStone() && board.getCellAtPos(pos)->getStone()->getMark() == tolower(dangerPiece)) {
		return true;
	}
	else if (board.isInBoard(pos) && player == Color::WHITE && board.getCellAtPos(pos)->getHasStone()&& board.getCellAtPos(pos)->getStone()->getMark() == toupper(dangerPiece)) {
		return true;
	}
	return false;
}

bool chessAndCheckers_Stone::isValidMove(const Position & src, const Position & dest, Board& board)
{
	bool destHasStone = board.getCellAtPos(dest)->getHasStone();
	Stone* destStone = board.getCellAtPos(dest)->getStone();

	board.getCellAtPos(src)->setHasStone(false);
	board.getCellAtPos(dest)->setHasStone(true);
	board.getCellAtPos(dest)->setStone(board.getCellAtPos(src)->getStone());

	bool threatOnKing = isKingThreatened(_player, board);

	board.getCellAtPos(src)->setHasStone(true);
	board.getCellAtPos(dest)->setHasStone(destHasStone);
	board.getCellAtPos(dest)->setStone(destStone);

	return !threatOnKing;
}

void chessAndCheckers_Stone::saveValidMoves(ostream& out) const
{
	int size = _validMoves.size();
	out.write(rCastC_c(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_validMoves[i].save(out);
	}
}

void chessAndCheckers_Stone::loadValidMoves(istream& in)
{
	int size;
	in.read(rCastC(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_validMoves.push_back(Position(in));
	}
}

void chessAndCheckers_Stone::saveDangers(ostream& out) const
{
	int size = _dangers.size();
	out.write(rCastC_c(&size), sizeof(size));
	for (int i = 0; i < size; i++){
		_dangers[i].save(out);
	}
}

void chessAndCheckers_Stone::loadDangers(istream& in)
{
	int size;
	in.read(rCastC(&size), sizeof(size));
	for (int i = 0; i < size; i++) {
		_dangers.push_back(Position(in));
	}
}
