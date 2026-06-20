#include <iostream>
#include <windows.h>

int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    auto responce = MessageBox( NULL, "This is message", "Message", MB_ICONINFORMATION | MB_ABORTRETRYIGNORE );
    std::cout << responce;
    return 0;
}