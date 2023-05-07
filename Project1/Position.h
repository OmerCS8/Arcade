#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define rCastC_c reinterpret_cast<const char*>
#define rCastC reinterpret_cast<char*>
using namespace std;
class Position
{
public:
	// Ctor
	Position(int row = -1, int col = -1);
	Position(const Position& pos);
	Position(istream& in);

	// GET
	inline int getRow() const { return _row; }
	inline int getCol() const { return _col; }

	// SET
	inline void setRow(int row) { _row = row; }
	inline void setCol(int col) { _col = col; }

	// Print Opertators
	friend ostream& operator<<(ostream& os, const Position& pos);
	friend istream& operator>>(istream& is, Position& pos);

	// Boolean Operators
	bool operator==(const Position& other) const;
	bool operator!=(const Position& other) const;

	// load and save to file
	void save(ostream& out) const;
	void load(istream& in);

private:
	int _row;
	int _col;
};

