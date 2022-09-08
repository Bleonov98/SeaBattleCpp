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
    wData->vBuf[_y][_x] = u'*' | (_color << 8);
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

int Player::GetShipType()
{
    return _shipType;
}

void Player::ChangeShipType()
{
    if (_shipType <= 2) {
        _shipType++;
    }
    else _shipType = 0;
}

void Player::RotateShip()
{
    if (_position == 0) {
        _position++;
    }
    else _position = 0;
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

