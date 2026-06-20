#include <iostream>
#include <windows.h>

int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    auto responce = MessageBox( NULL, "This is message", "Message", MB_ICONEXCLAMATION | MB_YESNOCANCEL | MB_APPLMODAL );
    std::cout << responce;
    return 0;
}