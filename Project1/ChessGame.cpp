#include "ChessGame.h"

ChessGame::ChessGame(int rowSize, int colSize) :Game(rowSize, colSize)
{
	try {
		for (int i = 0; i < rowSize; ++i) {
			for (int j = 0; j < colSize; ++j) {
				_board.getBoard()[i].push_back(new Cell(Position(i, j)));
			}
		}
		for (int i = 0; i < 8; ++i) {
			_players[0].getStones().push_back(new ChessPawn(Position(6, i), Color::WHITE));
			_players[1].getStones().push_back(new ChessPawn(Position(1, i), Color::BLACK));
		}

		_players[0].getStones().push_back(new ChessRook(Position(7, 0), Color::WHITE));
		_players[1].getStones().push_back(new ChessRook(Position(0, 0), Color::BLACK));

		_players[0].getStones().push_back(new ChessRook(Position(7, 7), Color::WHITE));
		_players[1].getStones().push_back(new ChessRook(Position(0, 7), Color::BLACK));

		_players[0].getStones().push_back(new ChessKnight(Position(7, 1), Color::WHITE));
		_players[1].getStones().push_back(new ChessKnight(Position(0, 1), Color::BLACK));

		_players[0].getStones().push_back(new ChessKnight(Position(7, 6), Color::WHITE));
		_players[1].getStones().push_back(new ChessKnight(Position(0, 6), Color::BLACK));

		_players[0].getStones().push_back(new ChessBishop(Position(7, 2), Color::WHITE));
		_players[1].getStones().push_back(new ChessBishop(Position(0, 2), Color::BLACK));

		_players[0].getStones().push_back(new ChessBishop(Position(7, 5), Color::WHITE));
		_players[1].getStones().push_back(new ChessBishop(Position(0, 5), Color::BLACK));

		_players[0].getStones().push_back(new ChessQueen(Position(7, 3), Color::WHITE));
		_players[1].getStones().push_back(new ChessQueen(Position(0, 3), Color::BLACK));

		_players[0].getStones().push_back(new ChessKing(Position(7, 4), Color::WHITE));
		_players[1].getStones().push_back(new ChessKing(Position(0, 4), Color::BLACK));
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

ChessGame::ChessGame(const ChessGame& other) :Game(other)
{
}

ChessGame::ChessGame(ChessGame&& other)
{
	*this = move(other);
}

ChessGame::ChessGame(istream& in): Game(in)
{
}

const ChessGame& ChessGame::operator=(ChessGame&& other)
{
	if (this != &other) {
		Game::operator=(move(*this));
	}
	return *this;
}

void ChessGame::isGameOver()
{
	int playerIndex = static_cast<int>(_turn);
	int sum = 0;
	for (int i = 0; i < _players[playerIndex].getStonesLeft(); ++i) {
		sum += static_cast<chessAndCheckers_Stone*>(_players[playerIndex].getStones()[i])->getValidMovesAmount();
	}
	if (sum == 0) {
		_isGameOver = true;
		_winner = playerIndex ? Color::WHITE : Color::BLACK;
	}
}

void ChessGame::makeMove(const vector<Position>& posArr)
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
			if (_board.getCellAtPos(dest)->getHasStone() && _board.getCellAtPos(dest)->getColor() != _turn) {
				eatStone(dest, _board.getCellAtPos(dest)->getColor());
			}
			stone = _board.getCellAtPos(src)->getStone();
			moveStone(stone, dest);
		}
	}
	isGameOver();
}

void ChessGame::save(ostream& out) const
{
	gameType gtp = gameType::chess;
	out.write(rCastC_c(&gtp), sizeof(gtp));
	Game::save(out);
}

void ChessGame::load(istream& in)
{
	Game::load(in);
}

void ChessGame::eatStone(const Position& toRemove, Color op)
{
	int playerIndex = static_cast<int>(op);
	Stone* stoneToRemove = _board.getCellAtPos(toRemove)->getStone();
	Stone* lastStone = _players[playerIndex].getStones()[_players[playerIndex].getStonesLeft() - 1];
	int index = findStoneIndex(stoneToRemove, op);
	_players[playerIndex].getStones()[index] = lastStone;
	delete stoneToRemove;
	_board.getCellAtPos(toRemove)->setHasStone(false);
	_board.getCellAtPos(toRemove)->setStone(nullptr);

	_players[playerIndex].getStones().pop_back();

	for (int i = 0; i < _players[playerIndex].getStonesLeft(); i++) {
		_board.getCellAtPos(_players[playerIndex].getStones()[i]->getPos())->setStone(_players[playerIndex].getStones()[i]);
	}
}

void ChessGame::moveStone(Stone* stone, const Position& dest)
{
	_board.getCellAtPos(stone->getPos())->setHasStone(false);
	_board.getCellAtPos(stone->getPos())->setStone(nullptr);

	_board.getCellAtPos(dest)->setHasStone(true);
	_board.getCellAtPos(dest)->setStone(stone);
	_board.getCellAtPos(dest)->setColor(stone->getColor());

	stone->setPos(dest);

	if ((_turn == Color::WHITE && stone->getMark() == 'p' && dest.getRow() == 0) || (_turn == Color::BLACK && stone->getMark() == 'P' && dest.getRow() == _board.getRowSize() - 1)) {
		Stone* newQueen;
		try {
			newQueen = new ChessQueen(move(static_cast<chessAndCheckers_Stone&>(*stone)));
		}
		catch (bad_alloc& err) {
			clearGame();
			throw err;
		}
		int index = findStoneIndex(stone, _turn);
		delete _players[static_cast<int>(_turn)].getStones()[index];
		_players[static_cast<int>(_turn)].getStones()[index] = newQueen;
		_board.getCellAtPos(dest)->setStone(newQueen);
	}
	_turn = _turn == Color::WHITE ? Color::BLACK : Color::WHITE;

	resetValidMovesAndDangers();
	calcDangersAndValidMoves();
}



