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
    ShowDstrShips();
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
    for (int i = 0; i < plShips.size(); i++)
    {
        for (int j = 0; j < plShips[i].size(); j++)
        {
            wData->vBuf[plShips[i][j].second][plShips[i][j].first] = u'#' | (_color << 8);
            wData->grid[plShips[i][j].second][plShips[i][j].first] = 1;
        }
    }

    for (int i = 0; i < cmShips.size(); i++)
    {
        for (int j = 0; j < cmShips[i].size(); j++)
        {
            wData->vBuf[cmShips[i][j].second][cmShips[i][j].first] = u'#' | (_color << 8);
            wData->grid[cmShips[i][j].second][cmShips[i][j].first] = 1;
        }
    }


    for (int i = 0; i < missPlShips.size(); i++)
    {
        wData->vBuf[missPlShips[i].second][missPlShips[i].first] = u'X' | (Red << 8);
        wData->grid[missPlShips[i].second][missPlShips[i].first] = 2;
    }

    for (int i = 0; i < missCmShips.size(); i++)
    {
        wData->vBuf[missCmShips[i].second][missCmShips[i].first] = u'X' | (Red << 8);
        wData->grid[missCmShips[i].second][missCmShips[i].first] = 2;
    }

    for (int i = 0; i < damagePlShips.size(); i++)
    {
        wData->vBuf[damagePlShips[i].second][damagePlShips[i].first] = u'X' | (Green << 8);
        wData->grid[damagePlShips[i].second][damagePlShips[i].first] = 3;
    }

    for (int i = 0; i < damageCmShips.size(); i++)
    {
        wData->vBuf[damageCmShips[i].second][damageCmShips[i].first] = u'X' | (Green << 8);
        wData->grid[damageCmShips[i].second][damageCmShips[i].first] = 3;
    }

    /*for (int i = 0; i < cmShipsCoord.size(); i++)
    {
        wData->vBuf[cmShipsCoord[i].second][cmShipsCoord[i].first] = u'#' | (_color << 8);
    }*/
}

void Player::ShowDstrShips()
{
    // playerShips
    for (int k = 0; k < destroyedShips.size(); k++)
    {
        for (int i = 0; i < plShips[destroyedShips[k]].size(); i++)
        {
             if (wData->grid[plShips[destroyedShips[k]][i].second][plShips[destroyedShips[k]][i].first + 1] == 0) {
                  missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first + 1, plShips[destroyedShips[k]][i].second));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second][plShips[destroyedShips[k]][i].first - 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first - 1, plShips[destroyedShips[k]][i].second));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second + 1][plShips[destroyedShips[k]][i].first + 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first, plShips[destroyedShips[k]][i].second + 1));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second - 1][plShips[destroyedShips[k]][i].first] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first, plShips[destroyedShips[k]][i].second - 1));
             }


             if (wData->grid[plShips[destroyedShips[k]][i].second + 1][plShips[destroyedShips[k]][i].first + 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first + 1, plShips[destroyedShips[k]][i].second + 1));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second - 1][plShips[destroyedShips[k]][i].first - 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first - 1, plShips[destroyedShips[k]][i].second - 1));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second - 1][plShips[destroyedShips[k]][i].first + 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first + 1, plShips[destroyedShips[k]][i].second - 1));
             }
             if (wData->grid[plShips[destroyedShips[k]][i].second + 1][plShips[destroyedShips[k]][i].first - 1] == 0) {
                 missPlShips.push_back(make_pair(plShips[destroyedShips[k]][i].first - 1, plShips[destroyedShips[k]][i].second + 1));
             }
        } 
    }

    // compShips
    for (int k = 0; k < destroyedCmShips.size(); k++)
    {
        for (int i = 0; i < cmShips[destroyedCmShips[k]].size(); i++)
        {
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second][cmShips[destroyedCmShips[k]][i].first + 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first + 1, cmShips[destroyedCmShips[k]][i].second));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second][plShips[destroyedCmShips[k]][i].first - 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first - 1, cmShips[destroyedCmShips[k]][i].second));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second + 1][plShips[destroyedCmShips[k]][i].first + 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first, cmShips[destroyedCmShips[k]][i].second + 1));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second - 1][plShips[destroyedCmShips[k]][i].first] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first, cmShips[destroyedCmShips[k]][i].second - 1));
            }


            if (wData->grid[cmShips[destroyedCmShips[k]][i].second + 1][cmShips[destroyedCmShips[k]][i].first + 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first + 1, cmShips[destroyedCmShips[k]][i].second + 1));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second - 1][cmShips[destroyedCmShips[k]][i].first - 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first - 1, cmShips[destroyedCmShips[k]][i].second - 1));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second - 1][cmShips[destroyedCmShips[k]][i].first + 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first + 1, cmShips[destroyedCmShips[k]][i].second - 1));
            }
            if (wData->grid[cmShips[destroyedCmShips[k]][i].second + 1][cmShips[destroyedCmShips[k]][i].first - 1] == 0) {
                missCmShips.push_back(make_pair(cmShips[destroyedCmShips[k]][i].first - 1, cmShips[destroyedCmShips[k]][i].second + 1));
            }
        }
    }
}

void Player::RotateShip()
{
    if (_position == 0 && _x <= 9) {
        _position++;
    }
    else if (_position == 1 && _y < 9) _position = 0;
}

void Player::SetShip()
{   

    for (int i = 0; i < plShips.size(); i++)
    {
        for (int k = 0; k < plShips[i].size(); k++)
        {
            if (_shipType == SINGLE) {
                if ((_x == plShips[i][k].first && _y == plShips[i][k].second) ||
                    (_x == plShips[i][k].first + 1 && _y == plShips[i][k].second) ||
                    (_x == plShips[i][k].first - 1 && _y == plShips[i][k].second) ||
                    (_x == plShips[i][k].first && _y == plShips[i][k].second + 1) ||
                    (_x == plShips[i][k].first && _y == plShips[i][k].second - 1) ||
                    (_x == plShips[i][k].first + 1 && _y == plShips[i][k].second + 1) ||
                    (_x == plShips[i][k].first - 1 && _y == plShips[i][k].second - 1) ||
                    (_x == plShips[i][k].first + 1 && _y == plShips[i][k].second - 1) ||
                    (_x == plShips[i][k].first - 1 && _y == plShips[i][k].second + 1)) return;
            }
            else if (_shipType == DBL) {
                if (_position == VERTICAL) {
                    for (int j = 0; j < 2; j++)
                    {
                        if ((_x == plShips[i][k].first && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second + 1)) return;
                    }
                }
                else {
                    for (int j = 0; j < 2; j++)
                    {
                        if ((_x + j == plShips[i][k].first && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second + 1)) return;
                    }
                }
            }
            else if (_shipType == TRPL) {
                if (_position == VERTICAL) {
                    for (int j = 0; j < 3; j++)
                    {
                        if ((_x == plShips[i][k].first && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second + 1)) return;
                    }
                }
                else {
                    for (int j = 0; j < 3; j++)
                    {
                        if ((_x + j == plShips[i][k].first && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second + 1)) return;
                    }
                }
            }
            else if (_shipType == BIG) {
                if (_position == VERTICAL) {
                    for (int j = 0; j < 4; j++)
                    {
                        if ((_x == plShips[i][k].first && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second + 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first + 1 && _y + j == plShips[i][k].second - 1) ||
                            (_x == plShips[i][k].first - 1 && _y + j == plShips[i][k].second + 1)) return;
                    }
                }
                else {
                    for (int j = 0; j < 4; j++)
                    {
                        if ((_x + j == plShips[i][k].first && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second + 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first + 1 && _y == plShips[i][k].second - 1) ||
                            (_x + j == plShips[i][k].first - 1 && _y == plShips[i][k].second + 1)) return;
                    }
                }
            }
        }
    }

    _shipCnt++;

    if (_shipType == SINGLE) {
        plShips[_shipCnt - 1].push_back(make_pair(_x, _y));
    }
    else if (_shipType == DBL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 2; height++)
            {
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 2; width++)
            {
                plShips[_shipCnt - 1].push_back(make_pair(_x + width, _y));
            }
        }
    } 
    else if (_shipType == TRPL) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 3; height++)
            {
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 3; width++)
            {
                plShips[_shipCnt - 1].push_back(make_pair(_x + width, _y));
            }
        }
    }
    else if (_shipType == BIG) {
        if (_position == VERTICAL) {
            for (int height = 0; height < 4; height++)
            {
                plShips[_shipCnt - 1].push_back(make_pair(_x, _y + height));
            }
        }
        else {
            for (int width = 0; width < 4; width++)
            {
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
        for (int i = 0; i < cmShips.size(); i++)
        {
            for (int j = 0; j < cmShips[i].size(); j++)
            {
                if (_x == cmShips[i][j].first && _y == cmShips[i][j].second) {
                    damageCmShips.push_back(make_pair(cmShips[i][j].first, cmShips[i][j].second));
                    kill = true;
                    break;
                }
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
        for (int i = 0; i < plShips.size(); i++)
        {
            bool brk = false;
            for (int j = 0; j < plShips[i].size(); j++)
            {
                if (_x == plShips[i][j].first && _y == plShips[i][j].second) {
                    damagePlShips.push_back(make_pair(plShips[i][j].first, plShips[i][j].second));
                    kill = true;
                    algKill = true;
                    checkAroudCrd.clear();
                    checkAroudCrd.push_back(make_pair(_x, _y));
                    brk = true;
                }
                if (brk) break;
            }
            if (brk) break;
        }
    }
    if (!kill) {
        if (_player) missCmShips.push_back(make_pair(_x, _y));
        else missPlShips.push_back(make_pair(_x, _y));
        NextPlayer();
    }

    int Cnt = 0;
    for (int i = 0; i < plShips.size(); i++)
    {
        bool next = false;
        for (int dst = 0; dst < destroyedShips.size(); dst++)
        {
            if (i == destroyedShips[dst]) {
                next = true;
            }
        }
        if (next) continue;
        
        for (int j = 0; j < plShips[i].size(); j++)
        {
            for (int k = 0; k < damagePlShips.size(); k++)
            {
                
                if (damagePlShips[k].first == plShips[i][j].first && damagePlShips[k].second == plShips[i][j].second) {
                    Cnt++;

                    if (Cnt == plShips[i].size()) {
                        destroyedShips.push_back(i);
                    }

                }

            }
        }
        Cnt = 0;
    }

    int cmCnt = 0;
    for (int i = 0; i < cmShips.size(); i++)
    {
        bool next = false;
        for (int dst = 0; dst < destroyedCmShips.size(); dst++)
        {
            if (i == destroyedCmShips[dst]) {
                next = true;
            }
        }
        if (next) continue;

        for (int j = 0; j < cmShips[i].size(); j++)
        {
            for (int k = 0; k < damageCmShips.size(); k++)
            {

                if (damageCmShips[k].first == cmShips[i][j].first && damageCmShips[k].second == cmShips[i][j].second) {
                    cmCnt++;

                    if (cmCnt == cmShips[i].size()) {
                        destroyedCmShips.push_back(i);
                    }

                }

            }
        }
        Cnt = 0;
    }

    Sleep(200);
}

bool Player::GetEndSet(bool &win)
{
    if (damagePlShips.size() >= 16) {
        _plWin = false;
        _cmWin = true;
        win = false;
        return _cmWin;
    }
    else if (damageCmShips.size() >= 16) {
        _plWin = true;
        _cmWin = true;
        win = true;
        return _plWin;
    }
    else return false;
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

        for (int k = 0; k < cmShips.size(); k++)
        {
            for (int j = 0; j < cmShips[k].size(); j++)
            {
                if (cX == cmShips[k][j].first && cY == cmShips[k][j].second) {
                    cX = 18 + rand() % 8;
                    cY = 3 + rand() % 8;
                    k = -1;
                    break;
                }
            }
        }
        

        
        newCoord = false;
        check = 0;
        
        for (int k = 0; k < cmShips.size(); k++)
        {
            for (int j = 0; j < cmShips[k].size(); j++)
            {
                bool brk = false;
                if (_cmShipType == SINGLE) {
                    if ((cX == cmShips[k][j].first && cY == cmShips[k][j].second) ||
                        (cX == cmShips[k][j].first + 1 && cY == cmShips[k][j].second) ||
                        (cX == cmShips[k][j].first - 1 && cY == cmShips[k][j].second) ||
                        (cX == cmShips[k][j].first && cY == cmShips[k][j].second + 1) ||
                        (cX == cmShips[k][j].first && cY == cmShips[k][j].second - 1) ||
                        (cX == cmShips[k][j].first + 1 && cY == cmShips[k][j].second + 1) ||
                        (cX == cmShips[k][j].first - 1 && cY == cmShips[k][j].second - 1) ||
                        (cX == cmShips[k][j].first + 1 && cY == cmShips[k][j].second - 1) ||
                        (cX == cmShips[k][j].first - 1 && cY == cmShips[k][j].second + 1)) {
                        cX = 18 + rand() % 8;
                        cY = 3 + rand() % 8;

                        k = -1;
                        break;
                    }
                }
                else if (_cmShipType == DBL) {      
                    if (_cmPos == VERTICAL) {
                        for (int s = 0; s < 2; s++)
                        {
                            if ((cX == cmShips[k][j].first && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cY + s >= 11) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;
                        }
                        if (brk) break;
                    }
                    else {
                        for (int s = 0; s < 2; s++)
                        {
                            if ((cX + s == cmShips[k][j].first && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cX + s >= 27) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;
                        }
                        if (brk) break;
                    }
                }
                else if (_cmShipType == TRPL) {
                    if (_cmPos == VERTICAL) {
                        for (int s = 0; s < 3; s++)
                        {
                            if ((cX == cmShips[k][j].first && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cY + s >= 11) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;

                        }
                        if (brk) break;
                    }
                    else {
                        for (int s = 0; s < 3; s++)
                        {
                            if ((cX + s == cmShips[k][j].first && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cX + s >= 27) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;
                        }
                        if (brk) break;
                    }
                }
                else if (_cmShipType == BIG) {
                    if (_cmPos == VERTICAL) {
                        for (int s = 0; s < 4; s++)
                        {
                            if ((cX == cmShips[k][j].first && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second + 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first + 1 && cY + s == cmShips[k][j].second - 1) ||
                                (cX == cmShips[k][j].first - 1 && cY + s == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cY + s >= 11) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;

                        }
                        if (brk) break;
                    }
                    else {
                        for (int s = 0; s < 4; s++)
                        {
                            if ((cX + s == cmShips[k][j].first && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second + 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first + 1 && cY == cmShips[k][j].second - 1) ||
                                (cX + s == cmShips[k][j].first - 1 && cY == cmShips[k][j].second + 1))
                            {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (cX + s >= 27) {
                                cX = 18 + rand() % 8;
                                cY = 3 + rand() % 8;
                                _cmPos = rand() % 2;
                                k = -1;
                                brk = true;
                            }
                            if (brk) break;
                        }
                        if (brk) break;
                    }
                }

                check++;
                if (check >= 200) {
                    _cmShipType = 0;
                    cmShips[k].clear();
                    i = -1;
                    check = 0;
                    newCoord = true;
                    break;
                }
            }
            
            if (newCoord) break;
            
        }
        if (newCoord) {
            continue;
        }

        _cmShipCnt++;

        if (_cmShipType == SINGLE) {
            cmShips[_cmShipCnt - 1].push_back(make_pair(cX, cY));
        }
        else if (_cmShipType == DBL) {
            if (_cmPos == VERTICAL) {
                for (int height = 0; height < 2; height++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX, cY + height));
                }
            }
            else {
                for (int width = 0; width < 2; width++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX + width, cY));
                }
            }
        }
        else if (_cmShipType == TRPL) {
            if (_cmPos == VERTICAL) {
                for (int height = 0; height < 3; height++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX, cY + height));
                }
            }
            else {
                for (int width = 0; width < 3; width++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX + width, cY));
                }
            }
        }
        else if (_cmShipType == BIG) {
            if (_cmPos == VERTICAL) {
                for (int height = 0; height < 4; height++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX, cY + height));
                }
            }
            else {
                for (int width = 0; width < 4; width++)
                {
                    cmShips[_cmShipCnt - 1].push_back(make_pair(cX + width, cY));
                }
            }
        }
    }
}