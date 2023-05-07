#pragma once
#include "Player.h"
#include "chessAndCheckers_Stone.h"
#include <array>
enum class gameType {checkers, amazon, chess};

class Game
{
public:

	// Ctors
	Game();
	Game(int rowSize, int colSize);
	Game(const Game& other);
	Game(Game&& other);
	Game(istream& in);
	// Dtor
	virtual ~Game();

	const Game& operator=(Game&& other);
	const Game& operator=(const Game& other);

	// GET
	bool getGameOver() const { return _isGameOver; }
	Color getWinner() const { return _winner; }
	Color getTurn() const { return _turn; }
	const Board& getBoard() const { return _board; }
	const array<Player, 2>& getPlayers() const { return _players; }
	array<Player, 2>& getPlayers() { return _players; }
	virtual int getMovePosAmount() const = 0;
	virtual int getMaxStoneAmount() const = 0;

	// SET
	void setWinner(Color winner) { _winner = winner; }
	void setGameOver(bool isGameOver) { _isGameOver = isGameOver; }
	void setTurn(Color turn) { _turn = turn; }

	// iterates over all the cells and calculates the valid moves or dangers from each cell
	virtual void calcDangersAndValidMoves();

	// iterates over all the cells and resets the valid moves or dangers array
	virtual void resetValidMovesAndDangers();

	// checks if someone won
	virtual void isGameOver() = 0;

	virtual void makeMove(const vector<Position>& posArray) = 0;

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

protected:
	bool _isGameOver;
	Color _winner;
	Color _turn;
	array<Player,2> _players;
	Board _board;

	// recieves a stone address and a player color and returns the index of this stone in the player stones array
	int findStoneIndex(Stone* stone, Color player);

	// clears all game memory in case of an error
	void clearGame();
};

