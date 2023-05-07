#include "GameList.h"

GameList::GameList() : _head(nullptr), _cur(nullptr), _tail(nullptr), _isEmpty(true)
{
}

GameList::~GameList()
{
	while (_cur != nullptr) {
		deleteCurGame();
	}
}

void GameList::addGameToEndList(int gameChoice)
{
	Game* newGame = nullptr;
	switch (gameChoice) {
	case 1:
		newGame = new CheckersGame();
		break;
	case 2:
		newGame = new AmazonGame();
		break;
	case 3: 
		newGame = new ChessGame();
		break;
	}
	GameItem* newGameItem = new GameItem(newGame);
	if (_isEmpty) {
		_head = _tail = newGameItem;
		newGameItem->next = newGameItem->prev = newGameItem;
		_isEmpty = false;
	}
	else {
		_head->prev = newGameItem;
		_tail->next = newGameItem;
		newGameItem->prev = _tail;
		newGameItem->next = _head;
		_tail = newGameItem;
	}
	_cur = newGameItem;
}

void GameList::deleteCurGame()
{
	GameItem* tmp;
	if (_head == _tail) {
		_isEmpty = true;
	}
	if (_cur == _head) {
		_head = _cur->next;
	}
	else if (_cur == _tail) {
		_tail = _cur->prev;
	}
	if (!_isEmpty) {
		tmp = _cur->next;
		_cur->prev->next = _cur->next;
		_cur->next->prev = _cur->prev;
		delete _cur->val;
		delete _cur;
		_cur = tmp;
	}
	else {
		delete _cur;
		_cur = _head = _tail = nullptr;
	}
}

GameList::GameItem::GameItem(Game* newGame):val(newGame) ,next(nullptr), prev(nullptr)
{
}
