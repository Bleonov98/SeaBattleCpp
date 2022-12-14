#pragma once
#include "Tools.h"

enum algDir {
	TOP,
	RIGHT,
	BOT,
	LEFT
};

class GameObject
{
public:

	GameObject(wd* wData, int x, int y, int color) {
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

	Player(wd* wData, int x, int y, int color): GameObject(wData, x, y, color){
		plShips.resize(7);
		cmShips.resize(7);

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				wData->grid[i][j] = 0;
			}
		}
	};

	
	void MoveCursor();


	int GetShipType();

	int GetShipPos();


	void SetState(bool turn);

	bool IsReady();

	bool isShot();

	bool isSet();

	
	void SetEnemyCoord(int x, int y, int shipPos);

	void SetEnemyShot(int x, int y);


	void SetEnemyState(bool rdy);

	bool GetEnemyState();

	
	void SetPlState(bool multiplayer);

	bool GetEndSet();

	int isWin();


private:


	void DrawShip();

	void EraseShip();

	void RotateShip();

	void SetShip();

	void ChangeShipType();


	void ShowShips();

	void ShowDstrShips();
	

	void Computer();

	void SetCompShips();


	void NextPlayer();

	bool PlayerW();


	void Shot();


	bool _player = true, singlePlayer = true, _winner = false;

	int _shipType = SINGLE, _shipCnt = 0, _position = VERTICAL;
	int _cmShipType = SINGLE, _cmShipCnt = 0, _cmPos = VERTICAL;

	char16_t dblShipVert[2][2]{
		u"#",
		u"#"
	};
	char16_t trplShipVert[3][2]{
		u"#",
		u"#",
		u"#"
	};
	char16_t bigShipVert[4][2]{
		u"#",
		u"#",
		u"#",
		u"#"
	};

	char16_t dblShipHor[1][3]{
		u"##"
	};
	char16_t trplShipHor[1][4]{
		u"###"
	};
	char16_t bigShipHor[1][5]{
		u"####"
	};

	vector<vector<pair<int, int>>> plShips;
	vector<vector<pair<int, int>>> cmShips;

	vector <pair<int, int>> damagePlShips;
	vector <pair<int, int>> damageCmShips;

	vector <int> destroyedShips;
	vector <int> destroyedCmShips;

	vector <pair<int, int>> missPlShips;
	vector <pair<int, int>> missCmShips;

	vector <pair<int, int>> checkAroudCrd;

	pair<int, int> startPosAlg;
	pair<int, int> prevPosAlg;

	bool top, bot, left, right;
	int prevDir, prevX = 20, prevY = 7;

	bool algKill = false, finded = false, algDone = false;

	bool enemyReady = false, plReady = false, _shot = false, _setShip = false;
};


