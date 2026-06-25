#include <windows.h>

LPSTR class_name = "Test Shit";
MSG message;

HWND button1;
HWND button2;
HWND button3;
HWND button4;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, const int nShowCmd )
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( nullptr, IDI_APPLICATION );
    wc.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = class_name;
    wc.hIconSm = LoadIcon( nullptr, IDI_APPLICATION );

    if ( !RegisterClassEx( & wc ) )
    {
        MessageBox( nullptr, "u dumb and ur code is not working", "womp womp",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

    const HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, class_name, "Window", WS_OVERLAPPEDWINDOW,
                                     CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, nullptr, nullptr, hInstance, nullptr);

    button1 = CreateWindowEx( 0, "BUTTON1", "Standart button", WS_CHILD | WS_VISIBLE,
                            100, 100, 150, 30, hwnd, NULL, hInstance, NULL );

    button2 = CreateWindowEx( 0, "BUTTON2", "Checkbox button", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                            100, 200, 150, 30, hwnd, NULL, hInstance, NULL );

    button3 = CreateWindowEx( 0, "BUTTON3", "Radio button", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
                            100, 300, 150, 30, hwnd, NULL, hInstance, NULL );

    button4 = CreateWindowEx( 0, "BUTTON4", "Groupbox button", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                            100, 400, 150, 30, hwnd, NULL, hInstance, NULL );

    if ( hwnd == nullptr )
    {
        MessageBox( nullptr, "window is nor working", "lol", MB_ICONEXCLAMATION );
        return 1;
    }

    ShowWindow( hwnd, nShowCmd );
    UpdateWindow( hwnd );

    while ( GetMessage( & message, nullptr, 0, 0 ) )
    {
        TranslateMessage( & message );
        DispatchMessage( & message );
    }
    return message.wParam;
}

LRESULT CALLBACK WndProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam )
{
    switch ( msg )
    {
        case WM_CLOSE:
            DestroyWindow( hwnd );
        break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
        break;

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}