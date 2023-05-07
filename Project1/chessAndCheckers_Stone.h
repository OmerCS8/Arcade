#pragma once
#include <cctype>
#include "Stone.h"
#include "Board.h"


class chessAndCheckers_Stone :
	public Stone
{
public:
	// Ctors
	chessAndCheckers_Stone(const Position& pos, Color color, char mark);
	chessAndCheckers_Stone(const chessAndCheckers_Stone& other);
	chessAndCheckers_Stone(chessAndCheckers_Stone&& other);
	chessAndCheckers_Stone(istream& in);

	//Dtor
	virtual ~chessAndCheckers_Stone();

	const chessAndCheckers_Stone& operator=(const chessAndCheckers_Stone& other);
	const chessAndCheckers_Stone& operator=(chessAndCheckers_Stone&& other);

	// Get
	virtual inline vector<Position>& getValidMoves() { return _validMoves; }
	virtual inline vector<Position>& getDangers() { return _dangers; }
	virtual inline const vector<Position>& getValidMoves() const { return _validMoves; }
	virtual inline const vector<Position>& getDangers() const { return _dangers; }
	virtual int getValidMovesAmount() const { return _validMoves.size(); }
	virtual int getDangersAmount() const { return _dangers.size(); }

	// Set
	void setValidMoves(const vector<Position>& validMoves) { _validMoves = validMoves; }
	void setDangers(const vector<Position>& dangers) { _dangers = dangers; }

	// adds the recieved position to the stone's dangers array
	void addDanger(Position& pos);
	// adds the recieved position to the stone's validMoves array
	void addValidMove(Position& pos);
	// checks if the recieved position is in the stone's valid moves array
	bool isInValidPos(const Position& pos);

	virtual void resetValidMovesAndDangers();
	virtual void calcDangersAndValidMoves(Board& board) = 0;

	// checks if the chess king is threatened
	bool isKingThreatened(Color player, Board& board);

	// load and save to file
	virtual void save(ostream& out) const;
	void load(istream& in);

protected:
	vector<Position> _validMoves;
	vector<Position> _dangers;

	// checks an offset line from the stone position for valid moves
	virtual void checkDiagonals(int i, int j, Board& board);
	// checks offset from stone position for valid moves
	virtual void checkSimpleDiagonals(int i, int j, Board& board);
	// checks an offset line from the stone position for king threats
	bool searchOffestLine(int i, int j, string dangeringPieces, int dangeringPiecesAmount, Color player, const Position& kingPos, Board& board);
	// checks offset from stone position for king threats
	bool searchOffset(int i, int j, char dangerPiece, Color player, const Position& kingPos, Board& board);
	// checks if the move is not threatening the king
	bool isValidMove(const Position& src, const Position& dest, Board& board);
	// load and save valid moves to file
	void saveValidMoves(ostream& out) const;
	void loadValidMoves(istream& in);
	// load and save dangers to file
	void saveDangers(ostream& out) const;
	void loadDangers(istream& in);

};

