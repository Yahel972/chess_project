#include "King.h"

King::King(char type, std::string _currPlace): Piece(type, _currPlace) {}

King::~King() {}

gameCodes King::checkMove(const std::string& newPlace, const Board& board) const
{
	return gameCodes::validMove;
}

bool King::isKingThreatened(char type /* k to check for black king, K for the white */)
{
	//TODO: check if king is being threatened by any piece. return true if the king is threatened, else return false.
	return false;
}

bool King::isCheckMate(char type /* k to check for black king, K for the white */)
{
	//TODO(optinal): check if the king cant move anywhere. return true if the king is threatened, else return false.
	//implementation suggestion: change the king location to any valid location,
	//and call isKingThreatened() every time to check if there is any move possible.
	return false;
}
