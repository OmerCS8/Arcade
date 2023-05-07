#include "AmazonGame.h"

AmazonGame::AmazonGame(int rowSize, int colSize):Game(rowSize, colSize)
{
	try {
		_players[0].getStones().push_back(new Stone(Position(6, 0), Color::WHITE, 'O'));
		_players[0].getStones().push_back(new Stone(Position(6, 9), Color::WHITE, 'O'));
		_players[0].getStones().push_back(new Stone(Position(9, 3), Color::WHITE, 'O'));
		_players[0].getStones().push_back(new Stone(Position(9, 6), Color::WHITE, 'O'));

		_players[1].getStones().push_back(new Stone(Position(0, 3), Color::BLACK, 'X'));
		_players[1].getStones().push_back(new Stone(Position(0, 6), Color::BLACK, 'X'));
		_players[1].getStones().push_back(new Stone(Position(3, 0), Color::BLACK, 'X'));
		_players[1].getStones().push_back(new Stone(Position(3, 9), Color::BLACK, 'X'));


		for (int i = 0; i < rowSize; ++i) {
			for (int j = 0; j < colSize; ++j) {
				_board.getBoard()[i].push_back(new AmazonCell(Position(i, j)));
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

AmazonGame::AmazonGame(const AmazonGame& other) : Game(other)
{
}



AmazonGame::AmazonGame(AmazonGame && other)
{
	*this = move(other);
}

AmazonGame::AmazonGame(istream& in): Game(in)
{
}

const AmazonGame & AmazonGame::operator=(AmazonGame && other)
{
	if (this != &other) {
		Game::operator=(move(other));
	}
	return *this;
	
}

void AmazonGame::calcDangersAndValidMoves()
{
	for (int i = 0; i < _board.getRowSize(); i++) {
		for (int j = 0; j < _board.getRowSize(); j++) {
			calcMovesFromCell(_board.getBoard()[i][j], -1, 0);
			calcMovesFromCell(_board.getBoard()[i][j], -1, 1);
			calcMovesFromCell(_board.getBoard()[i][j], 0, 1);
			calcMovesFromCell(_board.getBoard()[i][j], 1, 1);
			calcMovesFromCell(_board.getBoard()[i][j], 1, 0);
			calcMovesFromCell(_board.getBoard()[i][j], 1, -1);
			calcMovesFromCell(_board.getBoard()[i][j], 0, -1);
			calcMovesFromCell(_board.getBoard()[i][j], -1, -1);
		}
	}
}

bool AmazonGame::isValidMoveWithoutStone(const Position & src, const Position & dest, const Position & arrow)
{
	_board.getCellAtPos(src)->setHasStone(false);

	int iDir = arrow.getRow() - dest.getRow() == 0 ? 0 : (arrow.getRow() - dest.getRow()) / abs(arrow.getRow() - dest.getRow());
	int jDir = arrow.getCol() - dest.getCol() == 0 ? 0 : (arrow.getCol() - dest.getCol()) / abs(arrow.getCol() - dest.getCol());

	AmazonCell tmpCell(dest);
	calcMovesFromCell(&tmpCell, iDir, jDir);
	_board.getCellAtPos(src)->setHasStone(true);

	return tmpCell.isInValidMovesOrDangers(arrow);
}

void AmazonGame::isGameOver()
{
	int amountOfMoves = 0;
	for (int i = 0; i < _players[static_cast<int>(_turn)].getStonesLeft(); ++i) {
		amountOfMoves += static_cast<AmazonCell*>(_board.getCellAtPos(_players[static_cast<int>(_turn)].getStones()[i]->getPos()))->getValidMovesOrDangersAmount();
	}
	if (amountOfMoves == 0) {
		_isGameOver = true;
		_winner = static_cast<int>(_turn) ? Color::WHITE : Color::BLACK;
	}
}

void AmazonGame::makeMove(const vector<Position>& posArr)
{
	const Position& src = posArr[0];
	const Position& dest = posArr[1];
	const Position& arrow = posArr[2];
	if (!_board.getCellAtPos(src)->getHasStone()) {
		throw invalid_argument("No Amazona in this cell!");
	}
	else if (_turn !=_board.getCellAtPos(src)->getStone()->getColor()) {
		throw invalid_argument("You can't move this stone!");
	}
	else if (_board.getCellAtPos(src)->getValidMovesAmount() == 0)
	{
		throw invalid_argument("there are no valid moves for this Amazona");
	}
	else if (!static_cast<AmazonCell*>(_board.getCellAtPos(src))->isInValidMovesOrDangers(dest) || (!static_cast<AmazonCell*>(_board.getCellAtPos(dest))->isInValidMovesOrDangers(arrow) && !isValidMoveWithoutStone(src, dest, arrow))) {
		throw invalid_argument("This is not a valid move!");
	}
	else {
		moveStone(src, dest);
		shootArrow(arrow);
		isGameOver();
	}
}

void AmazonGame::save(ostream& out) const
{
	gameType gtp = gameType::amazon;
	out.write(rCastC_c(&gtp), sizeof(gtp));
	Game::save(out);
}

void AmazonGame::load(istream& in)
{
	Game::load(in);
}

void AmazonGame::moveStone(const Position & src, const Position & dest)
{
	Stone* stone = _board.getCellAtPos(src)->getStone();
	_board.getCellAtPos(src)->setHasStone(false);
	_board.getCellAtPos(src)->setStone(nullptr);

	_board.getCellAtPos(dest)->setHasStone(true);
	_board.getCellAtPos(dest)->setStone(stone);

	stone->setPos(dest);
}

void AmazonGame::shootArrow(const Position & arrow)
{
	static_cast<AmazonCell*>(_board.getCellAtPos(arrow))->setHasArrow(true);
	_turn = static_cast<Color>((static_cast<int>(_turn) + 1) % 2);

	resetValidMovesAndDangers();
	calcDangersAndValidMoves();
}

void AmazonGame::calcMovesFromCell(Cell * cell, int i, int j)
{
	int k = 1;
	vector<vector<Cell*>>& board = _board.getBoard();
	Position pos(cell->getPos().getRow() + k * i, cell->getPos().getCol() + k * j);
	while (_board.isInBoard(pos) && !board[pos.getRow()][pos.getCol()]->getHasStone() &&
		!static_cast<AmazonCell*>(board[pos.getRow()][pos.getCol()])->getHasArrow()) {
		static_cast<AmazonCell*>(cell)->addValidMoveOrDanger(pos);
		++k;
		pos.setRow(cell->getPos().getRow() + k * i);
		pos.setCol(cell->getPos().getCol() + k * j);
	}
}
