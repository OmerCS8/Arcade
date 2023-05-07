#include "Arcade.h"

Arcade::~Arcade()
{
	clearList();
}

void Arcade::handleTurn(bool& continueGame)
{
	printMenu();
	try {
		MenuOptions gameChoice;
		MenuOptions choice = static_cast<MenuOptions>(getMenuChoiceFromUser() - 1);
		Position pos;
		switch (choice) {
		case MenuOptions::ONE:
			gameChoice = static_cast<MenuOptions>(getGameChoiceFromUser() - 1);
			addGame(gameChoice);
			break;
		case MenuOptions::TWO: setNext();
			break;
		case MenuOptions::THREE: deleteCur();
			break;
		case MenuOptions::FOUR: printCurGameInfo();
			break;
		case MenuOptions::FIVE:
			pos = getPosFromUser(-1);
			printValidMoves(pos);
			break;
		case MenuOptions::SIX:
			pos = getPosFromUser(-1);
			printDangers(pos);
			break;
		case MenuOptions::SEVEN:
			makeMove();
			break;
		case MenuOptions::EIGHT:
			cout << "Bye Bye!" << endl;
			continueGame = false;
			break;
		case MenuOptions::NINE:
			saveGameToFile(getFileNameFromUser());
			break;
		case MenuOptions::TEN:
			LoadGameFromFile(getFileNameFromUser());
			break;
		}
	}
	catch (bad_alloc& error) {
		cout << error.what() << endl;
		clearList();
		exit(1);
	}
	catch (exception& error) {
		cout << error.what() << endl;
	}
	catch (runtime_error& Error)
	{
		cout << Error.what() << endl;
	}
}

void Arcade::printMenu()
{
	cout << "**********************************************" << endl <<
			"*  Please choose option from below:          *" << endl <<
			"*  1) Add a game                             *" << endl <<
			"*  2) Move to the next game                  *" << endl <<
			"*  3) Delete the current game                *" << endl <<
			"*  4) Show information of the current game   *" << endl <<
			"*  5) Show valid moves of a Stone            *" << endl <<
			"*  6) Show dangers of a cell                 *" << endl <<
			"*  7) Do move                                *" << endl <<
			"*  8) Exit the program                       *" << endl <<
			"*  9) Save current game to file              *" << endl <<
			"* 10) Load a game from file                  *" << endl <<
			"**********************************************" << endl;
}

void Arcade::startGame()
{
	bool continueGame = true;
	while (continueGame) {
		handleTurn(continueGame);
	}
}

void Arcade::printCurGameInfo() const
{
	cout << getCur()->getBoard();
	cout << "Is game over: " << (getCur()->getGameOver() ? "YES" : "No") << endl;
	if (getCur()->getGameOver()) {
		cout << "The Winner is " << ColorStr[static_cast<int>(getCur()->getWinner())] << endl;
	}
	else {
		cout << "This is " << ColorStr[static_cast<int>(getCur()->getTurn())] << "'s turn" << endl;
	}
}

void Arcade::setNext()
{
	++_it;
	if (_it == _games.end())
		_it = _games.begin();
}

void Arcade::deleteCur()
{
	_it = _games.erase(_it);
	if (_it == _games.end())
		_it = _games.begin();
}

void Arcade::addGame(MenuOptions gameChoice)
{
	Game* newGame = nullptr;
	switch (gameChoice) {
	case MenuOptions::ONE:
		newGame = new CheckersGame();
		break;
	case MenuOptions::TWO:
		newGame = new AmazonGame();
		break;
	case MenuOptions::THREE:
		newGame = new ChessGame();
		break;
	}
	if (_games.empty()) {
		_games.push_back(newGame);
		_it = _games.begin();
	}
	else {
		_games.push_back(newGame);
		setNext();
	}
}

void Arcade::printValidMoves(const Position& pos) const
{
	const vector<Position>& validMoves = getCur()->getBoard().getCellAtPos(pos)->getValidMoves();
	int validMovesAmount = getCur()->getBoard().getCellAtPos(pos)->getValidMovesAmount();
	if (validMovesAmount == 0)
		throw invalid_argument("No Valid Moves for this Stone");
	for (int i = 0; i < validMovesAmount; ++i) {
		cout << validMoves[i] << endl;
	}
}

void Arcade::printDangers(const Position& pos) const
{
	const vector<Position>& dangers = getCur()->getBoard().getCellAtPos(pos)->getDangers();
	int dangersAmount = getCur()->getBoard().getCellAtPos(pos)->getDangersAmount();
	if (dangersAmount == 0)
		throw invalid_argument("No Dangers for this Stone");
	for (int i = 0; i < dangersAmount; ++i) {
		cout << dangers[i] << endl;
	}
}

int Arcade::getMenuChoiceFromUser() const
{
	int num;
	cin >> num;

	if (!(num >= 1 && num <= 10)) {
		throw invalid_argument("this is not a VALID option");
	}
	else {
		if (num == 1 || num == 8 || num == 10) {
			return num;
		}
		else if (num >= 2 && num <= 9 && !_games.empty()) {
			return num;
		}
		else
			throw invalid_argument("No active game");
	}
}

int Arcade::getGameChoiceFromUser() const
{
	cout << "Enter game number (1 - Checkers, 2 - Amazon, 3 - Chess):" << endl;
	int num;
	cin >> num;
	if (!(num >= 1 && num <= 3)) {
		throw invalid_argument("this is not a VALID option");
	}
	return num;
}

string Arcade::getFileNameFromUser() const
{
	string name;
	cout << "Please Enter file name: ";
	cin >> name;
	return name;
}

void Arcade::saveGameToFile(string FileName) const
{
	ofstream outFile(FileName, ios::binary);
	if (!outFile)
		throw runtime_error("Can't open file!");
	getCur()->save(outFile);
}

void Arcade::LoadGameFromFile(string FileName)
{
	ifstream inFile(FileName, ios::binary);
	if (!inFile)
		throw runtime_error("File not found!");
    gameType gtp;
	inFile.read(rCastC(&gtp), sizeof(int));

	Game* newGame = nullptr;
	switch (gtp) {
	case gameType::checkers:
		newGame = new CheckersGame(inFile);
		break;
	case gameType::amazon:
		newGame = new AmazonGame(inFile);
		break;
	case gameType::chess:
		newGame = new ChessGame(inFile);
		break;
	}
	if (_games.empty()) {
		_games.push_back(newGame);
		_it = _games.begin();
	}
	else {
		_games.push_back(newGame);
		setNext();
	}
}

void Arcade::makeMove()
{
	vector<Position> posArr;
	int amount = getCur()->getMovePosAmount();
	posArr = getPosArray(amount);
	getCur()->makeMove(posArr);
}

Position Arcade::getPosFromUser(int index) const
{
	if (index == -1)
		cout << "Enter position (row col): ";
	else
		cout << "Enter #" << index + 1 << " position (row col): ";
	Position pos;
	cin >> pos;
	bool flag = true;
	while (flag) {
		try {
			if (pos.getRow() < 1 || pos.getRow() > getCur()->getBoard().getRowSize()
				|| pos.getCol() < 1 || pos.getCol() > getCur()->getBoard().getColSize())
				throw invalid_argument("Invalid position, please enter a valid position: ");
			else
				flag = false;
		}
		catch (invalid_argument& error) {
			cout << error.what() << endl;
			cin >> pos;
		}
	}
	return Position(pos.getRow() - 1, pos.getCol() - 1);
}

void Arcade::clearList()
{
	while (!_games.empty()) {
		delete _games.front();
		_games.pop_front();
	}
	_games.clear();
}

vector<Position> Arcade::getPosArray(int size) const
{
	vector<Position> arr;
	for (int i = 0; i < size; ++i) {
		arr.push_back(getPosFromUser(i));
	}
	return arr;
}


