#pragma once
#include "AmazonGame.h"
#include "CheckersGame.h"
#include "ChessGame.h"
class GameList
{
public:
	// Ctor
	GameList();
	// Dtor 
	~GameList();

	// GET
	bool getIsEmpty() const { return _isEmpty; }
	inline Game* getCurGame() const { return _cur->val; }

	// SET
	void setNextGame() { _cur = _cur->next; }

	// adds a game to the end of the game list
	void addGameToEndList(int gameChoice);

	// deletes the current game
	void deleteCurGame();

private:
	class GameItem {
	public:
		GameItem(Game* newGame);
		Game* val;
		GameItem* next;
		GameItem* prev;
	};
	GameItem* _head;
	GameItem* _tail;
	GameItem* _cur;
	bool _isEmpty;
};
