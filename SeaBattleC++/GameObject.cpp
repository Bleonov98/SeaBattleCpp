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
    EraseObject();
    _deleteObject = true;
}

bool GameObject::IsObjectDelete()
{
    return _deleteObject;
}

void Ship::DrawObject()
{
    wData->vBuf[_y][_x] = u'*' | (_color << 8);
}

void Ship::EraseObject()
{
    wData->vBuf[_y][_x] = ' ';
}

void Ship::MoveCursor()
{
    EraseObject();

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) _x++;
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) _x--;
    else if (GetAsyncKeyState(VK_UP) & 0x8000) _y--;
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) _y++;
    else if (GetAsyncKeyState(VK_RETURN) & 0x8000) Shot();
}

bool Ship::Shot()
{
    _shot = true;
    return _shot;
}
