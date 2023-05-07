#include "Game.h"

Game::Game() :Game(0, 0)
{
}

Game::Game(int rowSize, int colSize) :
	_isGameOver(false), _turn(Color::WHITE), _winner(Color::WHITE),
	_players(array<Player, 2>{ Color::WHITE,  Color::BLACK }),
	 _board(Board(rowSize, colSize))
{
}

Game::Game(const Game& other) : Game(other._board.getRowSize(), other._board.getColSize())
{
	*this = other;
}

Game::Game(Game&& other) : Game(0, 0)
{
	*this = move(other);
}

Game::Game(istream& in):Game()
{
	load(in);

	int size1 = _players[0].getStones().size();
	int size2 = _players[1].getStones().size();
	for (int j = 0; j < size1; j++) {
		Position whitePos = _players[0].getStones()[j]->getPos();
		_board.getCellAtPos(whitePos)->setStone(_players[0].getStones()[j]);
		_board.getCellAtPos(whitePos)->setHasStone(true);
	}
	for (int j = 0; j < size2; j++) {
		Position blackPos = _players[1].getStones()[j]->getPos();
		_board.getCellAtPos(blackPos)->setStone(_players[1].getStones()[j]);
		_board.getCellAtPos(blackPos)->setHasStone(true);
	}
}

Game::~Game()
{
}

const Game & Game::operator=(Game && other)
{
	if (this != &other) {
		_isGameOver = other._isGameOver;
		_winner = other._winner;
		_turn = other._turn;
		_players = other._players;
		_board = move(other._board);
	}
	return *this;
}

const Game& Game::operator=(const Game& other)
{
	if (this != &other) {
		_isGameOver = other._isGameOver;
		_winner = other._winner;
		_turn = other._turn;
		_board = other._board;
		_players[0] = other._players[0];
		_players[1] = other._players[1];
	}
	return *this;
}

void Game::calcDangersAndValidMoves()
{
	for (int i = 0; i < _players[0].getStonesLeft(); ++i) {
		static_cast<chessAndCheckers_Stone*>(_players[0].getStones()[i])->calcDangersAndValidMoves(_board);
	}
	for (int i = 0; i < _players[1].getStonesLeft(); ++i) {
		static_cast<chessAndCheckers_Stone*>(_players[1].getStones()[i])->calcDangersAndValidMoves(_board);
	}
}

void Game::resetValidMovesAndDangers()
{
	_board.resetValidMovesAndDangers();
}

void Game::save(ostream& out) const
{
	out.write(rCastC_c(&_isGameOver), sizeof(_isGameOver));
	out.write(rCastC_c(&_winner), sizeof(_winner));
	out.write(rCastC_c(&_turn), sizeof(_turn));
	_players[0].save(out);
	_players[1].save(out);
	_board.save(out);
}

void Game::load(istream& in)
{
	in.read(rCastC(&_isGameOver), sizeof(_isGameOver));
	in.read(rCastC(&_winner), sizeof(_winner));
	in.read(rCastC(&_turn), sizeof(_turn));
	_players[0].load(in);
	_players[1].load(in);
	_board.load(in);
}

int Game::findStoneIndex(Stone * stone, Color player)
{
	int playerIndex = static_cast<int>(player);
	for (int i = 0; i < _players[playerIndex].getStonesLeft(); ++i) {
		if (stone == _players[playerIndex].getStones()[i])
			return i;
	}
}

void Game::clearGame()
{
	for (int i = _board.getBoard().size(); i >= 0; --i) {
		for (int j = _board.getBoard()[i].size(); j >= 0; --j) {
			delete _board.getBoard()[i][j];
		}
		_board.getBoard()[i].clear();
	}
	_board.getBoard().clear();
	for (int j = _players[0].getStones().size(); j >= 0; --j) {
		delete _players[0].getStones()[j];
	}
	_players[0].getStones().clear();
	for (int j = _players[1].getStones().size(); j >= 0; --j) {
		delete _players[1].getStones()[j];
	}
	_players[1].getStones().clear();
}
