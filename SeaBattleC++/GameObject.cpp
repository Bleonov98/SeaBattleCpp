#include "GameObject.h"

int GameObject::GetX()
{
    return _x;
}

int GameObject::GetY()
{
    return _y;
}

void GameObject::SetX(int x)
{
    _x = x;
}

void GameObject::SetY(int y)
{
    _y = y;
}

void GameObject::DeleteObject()
{
    _deleteObject = true;
}

bool GameObject::IsObjectDelete()
{
    return _deleteObject;
}

void GameObject::DrawCursor()
{
    wData->vBuf[_y][_x] = u'#' | (Red << 8);
}

void GameObject::EraseCursor()
{
    wData->vBuf[_y][_x] = u' ';
}

void Player::MoveCursor()
{
    ShowShips();
    if (_prepare) {
        EraseShip();

        if (_shipType == SINGLE) {
            if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
            else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
            else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
            else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
        }
        else if (_shipType == DBL) {
            if (_position == VERTICAL) {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 9) _y++;
            }
            else {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 10) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
            }
        }
        else if (_shipType == TRPL) {
            if (_position == VERTICAL) {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 8) _y++;
            }
            else {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 9) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
            }
        }
        else if (_shipType == BIG) {
            if (_position == VERTICAL) {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 7) _y++;
            }
            else {
                if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 8) _x++;
                else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
                else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
                else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
            }
        }


        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            Sleep(200);
            SetShip();
        }
        if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
            RotateShip();
        }

        DrawShip();
    }
    else {
        EraseCursor();

        if (!_player) {
            Computer();
        }
        else {
            if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 26) _x++;
            else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x > 18) _x--;
            else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
            else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;

            else if (GetAsyncKeyState(VK_RETURN) & 0x8000) Shot();
        }
    }
}

void Player::DrawShip()
{
    if (_shipType == SINGLE) {
        wData->vBuf[_y][_x] = u'#' | (_color << 8);
    }
    else if (_shipType == DBL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 2; height++)
            {
                wData->vBuf[_y + height][_x] = dblShipVert[height][0] | (_color << 8);
            }
        }
        else {
            for (int width = 0; width < 2; width++)
            {
                wData->vBuf[_y][_x + width] = dblShipHor[0][width] | (_color << 8);
            }
        }
    }
    else if (_shipType == TRPL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 3; height++)
            {
                wData->vBuf[_y + height][_x] = trplShipVert[height][0] | (_color << 8);
            }
        }
        else {
            for (int width = 0; width < 3; width++)
            {
                wData->vBuf[_y][_x + width] = trplShipHor[0][width] | (_color << 8);
            }
        }
    }
    else if (_shipType == BIG) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 4; height++)
            {
                wData->vBuf[_y + height][_x] = bigShipVert[height][0] | (_color << 8);
            }
        }
        else {
            for (int width = 0; width < 4; width++)
            {
                wData->vBuf[_y][_x + width] = bigShipHor[0][width] | (_color << 8);
            }
        }
    }

}

void Player::EraseShip()
{
    if (_shipType == SINGLE) {
        wData->vBuf[_y][_x] = u' ';
    }
    else if (_shipType == DBL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 2; height++)
            {
                wData->vBuf[_y + height][_x] = u' ';
            }
        }
        else {
            for (int width = 0; width < 2; width++)
            {
                wData->vBuf[_y][_x + width] = u' ';
            }
        }
    }
    else if (_shipType == TRPL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 3; height++)
            {
                wData->vBuf[_y + height][_x] = u' ';
            }
        }
        else {
            for (int width = 0; width < 3; width++)
            {
                wData->vBuf[_y][_x + width] = u' ';
            }
        }
    }
    else if (_shipType == BIG) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 4; height++)
            {
                wData->vBuf[_y + height][_x] = u' ';
            }
        }
        else {
            for (int width = 0; width < 4; width++)
            {
                wData->vBuf[_y][_x + width] = u' ';
            }
        }
    }
}

int Player::GetShipType()
{
    return _shipType;
}

void Player::ChangeShipType()
{
    if (_shipType == SINGLE && _shipCnt == 2) {
        _shipType = DBL;
    }
    else if (_shipType == DBL && _shipCnt == 4) {
        _shipType = TRPL;
    }
    else if (_shipType == TRPL && _shipCnt == 6) {
        _shipType = BIG;
    }
    else if (_shipCnt == 7) {
        _shipType = 0;
        _prepare = false;
        _x = 20, _y = 7;
    }
}

void Player::ShowShips()
{
    for (int i = 0; i < shipsCoord.size(); i++)
    {
        wData->vBuf[shipsCoord[i].second][shipsCoord[i].first] = u'#' | (_color << 8);
    }

    for (int i = 0; i < damagePlShips.size(); i++)
    {
        wData->vBuf[damagePlShips[i].second][damagePlShips[i].first] = u'X' | (Green << 8);
    }

    for (int i = 0; i < damageCmShips.size(); i++)
    {
        wData->vBuf[damageCmShips[i].second][damageCmShips[i].first] = u'X' | (Green << 8);
    }

    for (int i = 0; i < missPlShips.size(); i++)
    {
        wData->vBuf[missPlShips[i].second][missPlShips[i].first] = u'X' | (Red << 8);
    }

    for (int i = 0; i < missCmShips.size(); i++)
    {
        wData->vBuf[missCmShips[i].second][missCmShips[i].first] = u'X' | (Red << 8);
    }

    /*for (int i = 0; i < cmShipsCoord.size(); i++)
    {
        wData->vBuf[cmShipsCoord[i].second][cmShipsCoord[i].first] = u'#' | (_color << 8);
    }*/
}

void Player::RotateShip()
{
    if (_position == 0) {
        _position++;
    }
    else _position = 0;
}

void Player::SetShip()
{   

    for (int i = 0; i < shipsCoord.size(); i++)
    {
        if (_shipType == SINGLE) {
            if ((_x == shipsCoord[i].first && _y == shipsCoord[i].second) ||
                (_x == shipsCoord[i].first + 1 && _y == shipsCoord[i].second) ||
                (_x == shipsCoord[i].first - 1 && _y == shipsCoord[i].second) ||
                (_x == shipsCoord[i].first && _y == shipsCoord[i].second + 1) ||
                (_x == shipsCoord[i].first && _y == shipsCoord[i].second - 1) ||
                (_x == shipsCoord[i].first + 1 && _y == shipsCoord[i].second + 1) ||
                (_x == shipsCoord[i].first - 1 && _y == shipsCoord[i].second - 1) ||
                (_x == shipsCoord[i].first + 1 && _y == shipsCoord[i].second - 1) ||
                (_x == shipsCoord[i].first - 1 && _y == shipsCoord[i].second + 1)) return;
        }
        else if (_shipType == DBL) {
            if (_position == VERTICAL) {
                for (int j = 0; j < 2; j++)
                {
                    if ((_x == shipsCoord[i].first && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second + 1)) return;
                } 
            }
            else {
                for (int j = 0; j < 2; j++)
                {
                    if ((_x + j == shipsCoord[i].first && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second + 1)) return;
                }
            }
        }
        else if (_shipType == TRPL) {
            if (_position == VERTICAL) {
                for (int j = 0; j < 3; j++)
                {
                    if ((_x == shipsCoord[i].first && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second + 1)) return;
                }
            }
            else {
                for (int j = 0; j < 3; j++)
                {
                    if ((_x + j == shipsCoord[i].first && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second + 1)) return;
                }
            }
        }
        else if (_shipType == BIG) {
            if (_position == VERTICAL) {
                for (int j = 0; j < 4; j++)
                {
                    if ((_x == shipsCoord[i].first && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second + 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first + 1 && _y + j == shipsCoord[i].second - 1) ||
                        (_x == shipsCoord[i].first - 1 && _y + j == shipsCoord[i].second + 1)) return;
                }
            }
            else {
                for (int j = 0; j < 4; j++)
                {
                    if ((_x + j == shipsCoord[i].first && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second + 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first + 1 && _y == shipsCoord[i].second - 1) ||
                        (_x + j == shipsCoord[i].first - 1 && _y == shipsCoord[i].second + 1)) return;
                }
            }
        }
    }

    _shipCnt++;

    if (_shipType == SINGLE) {
        shipsCoord.push_back(make_pair(_x, _y));
        plShips[_shipCnt - 1].push_back(make_pair(_x, _y));
    }
    else if (_shipType == DBL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 2; height++)
            {
                shipsCoord.push_back(make_pair(_x, _y + height));
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 2; width++)
            {
                shipsCoord.push_back(make_pair(_x + width, _y));
                plShips[_shipCnt - 1].push_back(make_pair(_x + width, _y));
            }
        }
    } 
    else if (_shipType == TRPL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 3; height++)
            {
                shipsCoord.push_back(make_pair(_x, _y + height));
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 3; width++)
            {
                shipsCoord.push_back(make_pair(_x + width, _y));
                plShips[_shipCnt - 1].push_back(make_pair(_x + width, _y));
            }
        }
    }
    else if (_shipType == BIG) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 4; height++)
            {
                shipsCoord.push_back(make_pair(_x, _y + height));
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 4; width++)
            {
                shipsCoord.push_back(make_pair(_x + width, _y));
                plShips[_shipCnt - 1].push_back(make_pair(_x + width, _y));
            }
        }
    }

    _x = 7, _y = 7;

    ChangeShipType();
}

int Player::GetShipCounter()
{
    return _shipCnt;
}

bool Player::Prepare()
{
    return _prepare;
}

void Player::NextPlayer()
{
    _player = !_player;
    EraseCursor();
    if (!_player) {
        _x = 4;
        _y = 3;
    }
    else {
        _x = 18;
        _y = 3;
    }
}

bool Player::PlayerW()
{
    return _player;
}

void Player::Shot()
{
    bool kill = false;
    if (_player) {
        for (int i = 0; i < damageCmShips.size(); i++)
        {
            if (_x == damageCmShips[i].first && _y == damageCmShips[i].second) {
                return;
            }
        }
        for (int i = 0; i < missCmShips.size(); i++)
        {
            if (_x == missCmShips[i].first && _y == missCmShips[i].second) {
                return;
            }
        }
        for (int i = 0; i < cmShipsCoord.size(); i++)
        {
            if (_x == cmShipsCoord[i].first && _y == cmShipsCoord[i].second) {
                damageCmShips.push_back(make_pair(cmShipsCoord[i].first, cmShipsCoord[i].second));
                wData->vBuf[cmShipsCoord[i].second][cmShipsCoord[i].first] = u'X' | (Green << 8);
                cmShipsCoord.erase(cmShipsCoord.begin() + i);
                kill = true;
                break;
            }
        }
    }
    else {
        for (int i = 0; i < damagePlShips.size(); i++)
        {
            if (_x == damagePlShips[i].first && _y == damagePlShips[i].second) {
                return;
            }
        }
        for (int i = 0; i < missPlShips.size(); i++)
        {
            if (_x == missPlShips[i].first && _y == missPlShips[i].second) {
                return;
            }
        }
        for (int i = 0; i < shipsCoord.size(); i++)
        {
            if (_x == shipsCoord[i].first && _y == shipsCoord[i].second) {
                damagePlShips.push_back(make_pair(shipsCoord[i].first, shipsCoord[i].second));
                wData->vBuf[shipsCoord[i].second][shipsCoord[i].first] = u'X' | (Green << 8);
                shipsCoord.erase(shipsCoord.begin() + i);
                kill = true;
                algKill = true;
                checkAroudCrd.clear();
                checkAroudCrd.push_back(make_pair(_x, _y));
                break;
            }
        }
    }
    if (!kill) {
        if (_player) missCmShips.push_back(make_pair(_x, _y));
        else missPlShips.push_back(make_pair(_x, _y));
        NextPlayer();
    }

    Sleep(200);
}

bool Player::GetEndSet(bool &win)
{
    if (shipsCoord.empty() && damagePlShips.size() > 0) {
        _plWin = false;
        _cmWin = true;
        win = false;
        return _cmWin;
    }
    else if (cmShipsCoord.empty() && damageCmShips.size() > 0) {
        _plWin = true;
        _cmWin = true;
        win = true;
        return _plWin;
    }
}

void Player::Computer()
{
    if (checkAroudCrd.empty()) {
        algKill = false;
    }

    if (!algKill) {
        _x = 3 + rand() % 10;
        _y = 3 + rand() % 9;
    }
    else if (algKill && checkAroudCrd.size() == 1) {
        if (checkAroudCrd[0].first + 1 <= 12) checkAroudCrd.push_back(make_pair(checkAroudCrd[0].first + 1, checkAroudCrd[0].second));
        if (checkAroudCrd[0].first - 1 > 3) checkAroudCrd.push_back(make_pair(checkAroudCrd[0].first - 1, checkAroudCrd[0].second));
        if (checkAroudCrd[0].second - 1 >= 3) checkAroudCrd.push_back(make_pair(checkAroudCrd[0].first, checkAroudCrd[0].second - 1));
        if (checkAroudCrd[0].second + 1 <= 10) checkAroudCrd.push_back(make_pair(checkAroudCrd[0].first, checkAroudCrd[0].second + 1));

        checkAroudCrd.erase(checkAroudCrd.begin());
    }

    for (int i = 0; i < missPlShips.size(); i++)
    {
        if (_x == missPlShips[i].first && _y == missPlShips[i].second && !algKill) {
            _x = 3 + rand() % 10;
            _y = 3 + rand() % 9;
            i = -1;
        }  
        else if (algKill && !checkAroudCrd.empty()) {
            for (int j = 0; j < checkAroudCrd.size(); j++)
            {
                if (checkAroudCrd[j].first == missPlShips[i].first && checkAroudCrd[j].second == missPlShips[i].second && algKill) {
                    checkAroudCrd.erase(checkAroudCrd.begin() + j);
                    i = -1;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < damagePlShips.size(); i++)
    {
        if (_x == damagePlShips[i].first && _y == damagePlShips[i].second && !algKill) {
            _x = 3 + rand() % 10;
            _y = 3 + rand() % 9;
            i = -1;
        }
        else if (algKill && !checkAroudCrd.empty()) {
            for (int j = 0; j < checkAroudCrd.size(); j++)
            {
                if (checkAroudCrd[j].first == damagePlShips[i].first && checkAroudCrd[j].second == damagePlShips[i].second && algKill) {
                    checkAroudCrd.erase(checkAroudCrd.begin() + j);
                    i = -1;
                    break;
                }
            }  
        }    
    }

    //if (!checkAroudCrd.empty()) {
    //    for (int i = 0; i < checkAroudCrd.size(); i++)
    //    {
    //        for (int j = 0; j < damagePlShips.size(); j++)
    //        {
    //            if (checkAroudCrd[i].first == damagePlShips[j].first) {

    //            }
    //        }
    //    }
    //}

    if (algKill && !checkAroudCrd.empty()) {
        _x = checkAroudCrd.back().first;
        _y = checkAroudCrd.back().second;
        checkAroudCrd.pop_back();
    }

    Shot();
}

void Player::SetCompShips()
{
    srand(time(NULL));

    int cX, cY;

    int check = 0;
    bool newCoord = false;

    for (int i = 0; i < 7; i++)
    {
        if (i % 2 == 0 && i > 0) {
            _cmShipType++;
        }

        _cmPos = rand() % 2;

        cX = 18 + rand() % 8;
        cY = 3 + rand() % 8;

        for (int j = 0; j < cmShipsCoord.size(); j++)
        {
            if (cX == cmShipsCoord[j].first && cY == cmShipsCoord[j].second) {
                cX = 18 + rand() % 8;
                cY = 3 + rand() % 8;
                j = -1;
            }
        }

        
        newCoord = false;
        check = 0;

        for (int j = 0; j < cmShipsCoord.size(); j++)
        {
            if (_cmShipType == SINGLE) {
                if ((cX == cmShipsCoord[j].first && cY == cmShipsCoord[j].second) ||
                    (cX == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second) ||
                    (cX == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second) ||
                    (cX == cmShipsCoord[j].first && cY == cmShipsCoord[j].second + 1) ||
                    (cX == cmShipsCoord[j].first && cY == cmShipsCoord[j].second - 1) ||
                    (cX == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second + 1) ||
                    (cX == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second - 1) ||
                    (cX == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second - 1) ||
                    (cX == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second + 1)) {
                    cX = 18 + rand() % 8;
                    cY = 3 + rand() % 8;

                    j = -1;
                }
            }
            else if (_cmShipType == DBL) {
                if (_cmPos == VERTICAL) {
                    for (int k = 0; k < 2; k++)
                    {
                        if ((cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cY + k >= 11) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }

                    }
                }
                else {
                    for (int k = 0; k < 2; k++)
                    {
                        if ((cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cX + k >= 27) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            else if (_cmShipType == TRPL) {
                if (_cmPos == VERTICAL) {
                    for (int k = 0; k < 3; k++)
                    {
                        if ((cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cY + k >= 11) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }

                    }
                }
                else {
                    for (int k = 0; k < 3; k++)
                    {
                        if ((cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cX + k >= 27) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            else if (_cmShipType == BIG) {
                if (_cmPos == VERTICAL) {
                    for (int k = 0; k < 4; k++)
                    {
                        if ((cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second + 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first + 1 && cY + k == cmShipsCoord[j].second - 1) ||
                            (cX == cmShipsCoord[j].first - 1 && cY + k == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cY + k >= 11) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }

                    }
                }
                else {
                    for (int k = 0; k < 4; k++)
                    {
                        if ((cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second + 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first + 1 && cY == cmShipsCoord[j].second - 1) ||
                            (cX + k == cmShipsCoord[j].first - 1 && cY == cmShipsCoord[j].second + 1))
                        {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                        if (cX + k >= 27) {
                            cX = 18 + rand() % 8;
                            cY = 3 + rand() % 8;
                            _cmPos = rand() % 2;
                            j = -1;
                            break;
                        }
                    }
                }
            }

            check++;
            if (check >= 200) {
                _cmShipType = 0;
                cmShipsCoord.clear();
                i = -1;
                check = 0;
                newCoord = true;
                break;
            }
        }
        if (newCoord) {
            continue;
        }

        if (_cmShipType == SINGLE) {
            cmShipsCoord.push_back(make_pair(cX, cY));
        }
        else if (_cmShipType == DBL) {
            if (_cmPos == VERTICAL) {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX, cY + 1));
            }
            else {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX + 1, cY));
            }
        }
        else if (_cmShipType == TRPL) {
            if (_cmPos == VERTICAL) {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX, cY + 1));
                cmShipsCoord.push_back(make_pair(cX, cY + 2));
            }
            else {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX + 1, cY));
                cmShipsCoord.push_back(make_pair(cX + 2, cY));
            }
        }
        else if (_cmShipType == BIG) {
            if (_cmPos == VERTICAL) {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX, cY + 1));
                cmShipsCoord.push_back(make_pair(cX, cY + 2));
                cmShipsCoord.push_back(make_pair(cX, cY + 3));
            }
            else {
                cmShipsCoord.push_back(make_pair(cX, cY));
                cmShipsCoord.push_back(make_pair(cX + 1, cY));
                cmShipsCoord.push_back(make_pair(cX + 2, cY));
                cmShipsCoord.push_back(make_pair(cX + 3, cY));
            }
        }
    }
}