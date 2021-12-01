#pragma once

enum colors { white, black };;

class Player
{
public:
	Player(bool color);
	~Player();
	bool getColor() const;
private:
	bool _color;
};