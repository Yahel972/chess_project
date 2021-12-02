#pragma once
#include <string>
#include "Board.h"
#pragma warning(disable:26812) //recommends to use 'enum class' instead of 'enum'
class Board;

enum gameCodes { validMove, checkOnEnemy, srcInvalid, dstInvalid, invalidCheckOnSelf, invalidIndex, invalidMove, invalidSrcIsDst, checkMate };

class Piece
{
public:

	Piece(char type);
	virtual ~Piece();
	virtual gameCodes checkMove(const std::string& newPlace, const Board& board) const = 0;
	char getType() const;
protected:
	char _type;
};

