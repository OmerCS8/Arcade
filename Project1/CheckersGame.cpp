#include "CheckersGame.h"


CheckersGame::CheckersGame(int rowSize, int colSize) :Game(rowSize, colSize)
{
	int row = 0, col = 1;
	try {
		for (int i = 0; i < maxStonesAmount && row < 3; i++) {
			if (col >= colSize) {
				row += 1;
				col = (row + 1) % 2;
			}
			Position pos(row, col);
			_players[0].getStones().push_back(new CheckersPawn(pos, Color::WHITE));
			col += 2;
		}
		row = rowSize - 1, col = colSize - 2;
		for (int i = 0; i < maxStonesAmount && row> rowSize - 1 - 3; i++) {
			if (col < 0) {
				row -= 1;
				col = colSize - 1 - (row % 2);
			}
			Position pos(row, col);

			_players[1].getStones().push_back(new CheckersPawn(pos, Color::BLACK));
			col -= 2;
		}
		for (int i = 0; i < rowSize; ++i) {
			for (int j = 0; j < colSize; ++j) {
				_board.getBoard()[i].push_back(new Cell(Position(i, j)));
			}
		}
	}
	catch (bad_alloc& err) {
		clearGame();
		throw err;
	}
	for (int j = 0; j < maxStonesAmount; j++) {
		Position whitePos = _players[0].getStones()[j]->getPos();
		_board.getCellAtPos(whitePos)->setStone(_players[0].getStones()[j]);
		_board.getCellAtPos(whitePos)->setHasStone(true);
		Position blackPos = _players[1].getStones()[j]->getPos();
		_board.getCellAtPos(blackPos)->setStone(_players[1].getStones()[j]);
		_board.getCellAtPos(blackPos)->setHasStone(true);
	}

	calcDangersAndValidMoves();
}

CheckersGame::CheckersGame(const CheckersGame& other) : Game(other)
{
}

CheckersGame::CheckersGame(CheckersGame&& other)
{
	*this = move(other);
}

CheckersGame::CheckersGame(istream& in) :Game(in)
{
}

const CheckersGame& CheckersGame::operator=(CheckersGame&& other)
{
	if (this != &other) {
		Game::operator=(move(*this));
	}
	return *this;
}



void CheckersGame::isGameOver()
{
	int turnNum = static_cast<int>(_turn);
	Player& p = _players[turnNum];
	if (p.getStonesLeft() == 0) {
		_isGameOver = true;
		_winner = turnNum ? Color::WHITE : Color::BLACK;
	}
	else {
		if (!areMovesLeft(p)) {
			_isGameOver = true;
			_winner = turnNum ? Color::WHITE : Color::BLACK;
		}
	}
}

void CheckersGame::makeMove(const vector<Position>& posArr)
{
	const Position& src = posArr[0];
	const Position& dest = posArr[1];
	if (!_board.getCellAtPos(src)->getHasStone()) {
		throw invalid_argument("No stone in this cell!");
	}
	else if (_turn != _board.getCellAtPos(src)->getStone()->getColor()) {
		throw invalid_argument("You can't move this stone!");
	}
	else if (static_cast<chessAndCheckers_Stone*>(_board.getCellAtPos(src)->getStone())->getValidMovesAmount() == 0)
	{
		throw invalid_argument("there are no valid moves for this stone");
	}
	else {
		Stone* stone = _board.getCellAtPos(src)->getStone();
		if (!stone->isInValidPos(dest)) {
			throw invalid_argument("This is not a valid move!");
		}
		else {
			int iDir, jDir;
			iDir = -1 * (dest.getRow() - src.getRow()) / abs(dest.getRow() - src.getRow());
			jDir = -1 * (dest.getCol() - src.getCol()) / abs(dest.getCol() - src.getCol());
			Position cellBeforeDest(dest.getRow() + iDir, dest.getCol() + jDir);
			if (src != cellBeforeDest && _board.getCellAtPos(cellBeforeDest)->getHasStone()
				&& _board.getCellAtPos(cellBeforeDest)->getColor() != _turn) {

				eatStone(cellBeforeDest, _board.getCellAtPos(cellBeforeDest)->getColor());
			}
			stone = _board.getCellAtPos(src)->getStone();
			moveStone(stone, dest);
		}
	}
	isGameOver();
}

void CheckersGame::save(ostream& out) const
{
	gameType gtp = gameType::checkers;
	out.write(rCastC_c(&gtp), sizeof(gtp));
	Game::save(out);
}

void CheckersGame::load(istream& in)
{
	Game::load(in);
}

void CheckersGame::moveStone(Stone* stone, const Position& dest)
{
	_board.getCellAtPos(stone->getPos())->setHasStone(false);
	_board.getCellAtPos(stone->getPos())->setStone(nullptr);

	_board.getCellAtPos(dest)->setHasStone(true);
	_board.getCellAtPos(dest)->setStone(stone);
	_board.getCellAtPos(dest)->setColor(stone->getColor());

	stone->setPos(dest);

	if ((_turn == Color::WHITE && dest.getRow() == _board.getRowSize() - 1) || (_turn == Color::BLACK && dest.getRow() == 0)) {
		Stone* newKing;
		try {
			newKing = new CheckersKing(move(static_cast<chessAndCheckers_Stone&>(*stone)));
		}
		catch (bad_alloc& err) {
			clearGame();
			throw err;
		}
		int index = findStoneIndex(stone, _turn);
		delete _players[static_cast<int>(_turn)].getStones()[index];
		_players[static_cast<int>(_turn)].getStones()[index] = newKing;
		_board.getCellAtPos(dest)->setStone(stone);
	}
	_turn = _turn == Color::WHITE ? Color::BLACK : Color::WHITE;

	resetValidMovesAndDangers();
	calcDangersAndValidMoves();
}

bool CheckersGame::areMovesLeft(Player& p)
{
	int sum = 0;
	for (int i = 0; i < p.getStonesLeft(); i++) {
		sum += static_cast<chessAndCheckers_Stone*>(p.getStones()[i])->getValidMovesAmount();
	}
	if (sum == 0)
		return false;
	else
		return true;
}

void CheckersGame::eatStone(const Position& toRemove, Color op)
{
	int playerIndex = static_cast<int>(op);
	Stone* stoneToRemove = _board.getCellAtPos(toRemove)->getStone();
	Stone* lastStone = _players[playerIndex].getStones()[_players[playerIndex].getStonesLeft() - 1];
	mySwap(stoneToRemove, lastStone);
	delete lastStone;
	_board.getCellAtPos(toRemove)->setHasStone(false);
	_board.getCellAtPos(toRemove)->setStone(nullptr);


	_players[playerIndex].getStones().pop_back();

	for (int i = 0; i < _players[playerIndex].getStonesLeft(); i++) {
		_board.getCellAtPos(_players[playerIndex].getStones()[i]->getPos())->setStone(_players[playerIndex].getStones()[i]);
	}
}
