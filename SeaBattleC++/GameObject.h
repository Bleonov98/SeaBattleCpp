#pragma once
#include "Tools.h"

class GameObject
{
public:

	GameObject(wd* wData, int x, int y, int speed, int color) {
		this->wData = wData;
		_x = x, _y = y, _color = color;
	};

	int GetX();

	int GetY();

	void SetX(int x);

	void SetY(int y);

	void DeleteObject();

	bool IsObjectDelete();

	void DrawCursor();

	void EraseCursor();

	void MoveCursor();

	bool Shot();

protected:

	wd* wData;

	int _x, _y, _color;

	bool _deleteObject = false, _shot = false;

	virtual ~GameObject() {
		delete this;
	}

};

class Player : public GameObject 
{
public:

	Player(wd* wData, int x, int y, int speed, int color): GameObject(wData, x, y, speed, color){};



private:

};