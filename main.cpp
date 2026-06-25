#include <iostream>
#include <ostream>
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

    button1 = CreateWindowEx( 0, "BUTTON", "Standart button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                            100, 100, 150, 30, hwnd, reinterpret_cast<HMENU>(1001), hInstance, NULL );

    button2 = CreateWindowEx( 0, "BUTTON", "Checkbox button", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                            100, 200, 150, 30, hwnd, reinterpret_cast<HMENU>(1002), hInstance, NULL );

    CheckDlgButton( hwnd, 1002, BST_CHECKED ); //
    // CheckDlgButton( hwnd, ID_CHECKBOX1, BST_UNCHECKED ); //

    button3 = CreateWindowEx( 0, "BUTTON", "Radio button", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
                            100, 300, 150, 30, hwnd, reinterpret_cast<HMENU>(1003), hInstance, NULL );

    button4 = CreateWindowEx( 0, "BUTTON", "Groupbox button", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                            100, 400, 150, 30, hwnd, reinterpret_cast<HMENU>(1004), hInstance, NULL );

    int ID_CHECKBOX1 = GetDlgCtrlID( button4 );
    std::cout << ID_CHECKBOX1 << std::endl;

    bool bChecked = ( IsDlgButtonChecked( hwnd, 1002 ) == BST_CHECKED );
    std::cout << bChecked << std::endl;

    HWND hText = CreateWindowEx( 0, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 500, 500, 150, 20,
                            hwnd, NULL, hInstance, NULL );

    HWND hText1 = CreateWindowEx( WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL, 300, 5, 150, 150, hwnd, NULL, hInstance, NULL );

    HWND hListBox = CreateWindowEx( WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
600, 5, 150, 200, hwnd, NULL, hInstance, NULL );

    SendMessage( hListBox, LB_ADDSTRING, 0,( LPARAM ) "Element 1" );
    SendMessage( hListBox, LB_ADDSTRING, 0,( LPARAM ) "Element 2" );

    HWND hCombo = CreateWindowEx( WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN,
300, 200, 150, 200, hwnd, NULL, hInstance, NULL );

    SendMessage( hCombo, CB_ADDSTRING, 0,( LPARAM ) "Element 1" );
    SendMessage( hCombo, CB_ADDSTRING, 0,( LPARAM ) "Element 2" );

    HWND hStatic = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
SS_LEFT, 700, 250, 150, 200, hwnd, NULL, hInstance, NULL );

    SetWindowText( hStatic, "Text" );

    HWND hStaticIcon = CreateWindowEx( 0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
SS_ICON, 50, 50, 48, 48, hwnd, NULL, hInstance, NULL );
    SendMessage( hStaticIcon, STM_SETICON,( WPARAM ) LoadIcon( NULL, IDI_APPLICATION ), 0 );

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

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case 1001:
                    MessageBox(hwnd, "Button1 clicked!", "Info", MB_OK);
                break;
                case 1002:
                    MessageBox(hwnd, "Button2 clicked!", "Info", MB_OK);
                break;
                case 1003:
                    MessageBox(hwnd, "Button3 clicked!", "Info", MB_OK);
                break;
                case 1004:
                    MessageBox(hwnd, "Button4 clicked!", "Info", MB_OK);
                break;
                default: ;
            }
            break;
        }

        default:
            return DefWindowProc( hwnd, msg, wParam, lParam );
    }

    return 0;
}