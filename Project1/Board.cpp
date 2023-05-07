#include "Board.h"

Board::Board() : _board(vector<vector<Cell*>>()), _rowSize(0), _colSize(0)
{
}

Board::Board(int rowSize, int colSize) : _board(vector<vector<Cell*>>()), _rowSize(rowSize), _colSize(colSize)
{
	for (int i = 0; i < rowSize; ++i) {
		_board.push_back(vector<Cell*>());
	}
}

Board::Board(const Board& other) : Board(other._rowSize, other._colSize)
{
	*this = other;
}

Board::Board(Board&& other)
{
	*this = move(other);
}

Board::Board(istream& in)
{
	load(in);
}

Board::~Board()
{
	deleteBoard();
}

const Board& Board::operator=(Board&& other)
{
	if (this != &other) {
		deleteBoard();
		_board = other._board;
		_rowSize = other._rowSize;
		_colSize = other._colSize;
		other._rowSize = 0;
		other._colSize = 0;
	}
	return *this;
}

const Board& Board::operator=(const Board& other)
{
	if (this != &other) {
		_rowSize = other._rowSize;
		_colSize = other._colSize;
		try {
			for (int i = 0; i < _rowSize; ++i) {
				for (int j = 0; j < _colSize; ++j) {
					_board[i][j] = new Cell(*other._board[i][j]);
				}
			}
		}
		catch (bad_alloc& err) {
			for (int i = _board.size(); i >= 0; --i) {
				for (int j = _board[i].size(); j >= 0; --j) {
					delete _board[i][j];
				}
			}
			throw err;
		}
	}
	return *this;
}

const Cell* Board::getCellAtPos(const Position& pos) const
{
	if (!isInBoard(pos))
		throw out_of_range("Position not in board");
	return _board[pos.getRow()][pos.getCol()];
}
Cell* Board::getCellAtPos(const Position& pos)
{
	if (!isInBoard(pos))
		throw out_of_range("Position not in board");
	return _board[pos.getRow()][pos.getCol()];
}

const Position& Board::getStonePos(Color player, char mark)
{
	for (int i = 0; i < _rowSize; ++i) {
		for (int j = 0; j < _colSize; ++j) {
			if (_board[i][j]->getHasStone() && _board[i][j]->getColor() == player && tolower(_board[i][j]->getStone()->getMark()) == mark) {
				return Position(i, j);
			}
		}
	}
}

bool Board::isInBoard(const Position& pos) const
{
	if (pos.getRow() < 0 || pos.getRow() >= _rowSize || pos.getCol() < 0 || pos.getCol() >= _colSize)
		return false;
	return true;
}
bool Board::isInBoard(const Position& pos)
{
	if (pos.getRow() < 0 || pos.getRow() >= _rowSize || pos.getCol() < 0 || pos.getCol() >= _colSize)
		return false;
	return true;
}

void Board::resetValidMovesAndDangers()
{
	for (int i = 0; i < _rowSize; ++i) {
		for (int j = 0; j < _colSize; ++j) {
			_board[i][j]->resetValidMovesAndDangers();
		}
	}
}

void Board::save(ostream& out) const
{
	out.write(rCastC_c(&_rowSize), sizeof(_rowSize));
	out.write(rCastC_c(&_colSize), sizeof(_colSize));
	saveBoard(out);
}

void Board::load(istream& in)
{
	in.read(rCastC(&_rowSize), sizeof(_rowSize));
	in.read(rCastC(&_colSize), sizeof(_colSize));
	_board = vector<vector<Cell*>>();
	for (int i = 0; i < _rowSize; ++i) {
		_board.push_back(vector<Cell*>());
	}
	loadBoard(in);
}

void Board::saveBoard(ostream& out) const
{
	for (int i = 0; i < _rowSize; i++) {
		for (int j = 0; j < _colSize; j++) {
			_board[i][j]->save(out);
		}
	}
}

void Board::loadBoard(istream& in)
{
	CellType ctp;
	for (int i = 0; i < _rowSize; ++i) {
		for (int j = 0; j < _colSize; ++j) {
			in.read(rCastC(&ctp), sizeof(ctp));
			switch (ctp)
			{
			case CellType::amazon:
				_board[i].push_back(new AmazonCell(in));
				break;
			case CellType::chessAndCheckers:
				_board[i].push_back(new Cell(in));
				break;
			}
		}
	}
}

void Board::deleteBoard()
{
	for (int i = 0; i < _rowSize; ++i) {
		for (int j = 0; j < _colSize; ++j) {
			delete _board[i][j];
		}
		_board[i].clear();
	}
	_board.clear();
}

ostream& operator<<(ostream& os, const Board& board)
{
	int i, j;

	os << "    | ";
	for (i = 0; i < board._colSize; i++) {
		if (i < 9)
			os << " " << i + 1 << " | ";
		else
			os << i + 1 << " | ";
	}
	os << "\n----";
	for (i = 0; i < board._colSize; i++) { os << "+----"; }
	os << "+\n";
	for (i = 0; i < board._rowSize; i++)
	{
		if (i < 9)
			os << "  " << i + 1 << " |";
		else
			os << " " << i + 1 << " |";
		for (j = 0; j < board._colSize; j++)
		{
			if (!board._board[i][j]->getHasStone()) {
				if (!board._board[i][j]->getHasArrow())
					os << "    |";
				else
					os << "FLAG|";
			}
			else {
				os << "  " << board._board[i][j]->getStone()->getMark() << " |";
			}
		}
		os << "\n----";
		for (j = 0; j < board._colSize; j++) { cout << "+----"; }
		os << "+" << endl;
	}
	os << endl;

	return os;
}
