#pragma once
#include <string>
#include "Board.h"
#pragma warning(disable:26812) //recommends to use 'enum class' instead of 'enum'
class Board;

enum gameCodes { validMove, checkOnEnemy, invalidCheckOnSelf, invalidIndex, invalidMove, invalidSrcIsDst, checkMate };

class Piece
{
public:
	Piece(char type, std::string _currPlace);
	virtual ~Piece();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board, bool dontRecurse = false) const = 0;
	char getType() const;
	std::string getCurrPlace() const;
	void setCurrPlace(std::string newVal);
	static bool isIndexValid(std::string index);
protected:
	char _type;
	std::string _currPlace;
};

