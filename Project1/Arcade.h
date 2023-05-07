#pragma once
#include "AmazonGame.h"
#include "CheckersGame.h"
#include "ChessGame.h"
#include <list>
enum class MenuOptions{ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN};
class Arcade
{
public:

	~Arcade();

	// GET
	list<Game*>& getGameList() { return _games; }

	void handleTurn(bool& continueTurn);
	static void printMenu();
	void startGame();
	void printCurGameInfo() const;

	Game* getCur() { return *_it; }
	const Game* getCur() const { return *_it; }
	void setNext();
	void deleteCur();
	void addGame(MenuOptions gameChoice);

	// gets a position and prints the valid move of a stone in this position
	void printValidMoves(const Position& pos) const;

	// gets a position and prints the danger of the cell in this position
	void printDangers(const Position& pos) const;

private:
	list<Game*> _games;
	list<Game*>::iterator _it;

	int getMenuChoiceFromUser() const;
	int getGameChoiceFromUser() const;
	string getFileNameFromUser() const;
	void saveGameToFile(string FileName) const;
	void LoadGameFromFile(string FileName);
	void makeMove();

	// gets a position array from the user according to the size recieved
	vector<Position> getPosArray(int size) const;
	// gets a single position for the array
	Position getPosFromUser(int index) const;
	
	// clears list memory in case of an error
	void clearList();
};

