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
    wData->vBuf[_y][_x] = u'#' | (_color << 8);
}

void GameObject::EraseCursor()
{
    wData->vBuf[_y][_x] = u' ';
}

bool GameObject::Shot()
{
    _shot = true;
    return _shot;
}

void Player::MoveCursor()
{
    if (_prepare) {
        EraseShip();

        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
        else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
        else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
        else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
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

        if (_player) {
            if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && _x <= 11) _x++;
            else if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && _x >= 4) _x--;
            else if ((GetAsyncKeyState(VK_UP) & 0x8000) && _y >= 4) _y--;
            else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && _y <= 10) _y++;
            else if (GetAsyncKeyState(VK_RETURN) & 0x8000) Shot();
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
        _prepare = false;
    }
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
    _shipCnt++;

    ChangeShipType();
}

int Player::ShipCounter()
{
    return _shipCnt;
}

bool Player::Prepare()
{
    return _prepare;
}

void Player::nextPlayer()
{
    _player = !_player;
    EraseCursor();
    if (_player) {
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

