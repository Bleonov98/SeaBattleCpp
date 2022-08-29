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

	virtual void DrawObject() = 0;

	virtual void EraseObject() = 0;

	void DeleteObject();

	bool IsObjectDelete();

protected:

	wd* wData;

	int _x, _y, _color;

	bool _deleteObject = false;

	virtual ~GameObject() {
		delete this;
	}


};

class Ship : public GameObject 
{
public:

	Ship(wd* wData, int x, int y, int speed, int color): GameObject(wData, x, y, speed, color){};

	void DrawObject() override;

	void EraseObject() override;

	void MoveCursor();

	bool Shot();

private:

	bool _shot = false;

};