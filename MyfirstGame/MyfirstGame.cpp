// MyfirstGame.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "MyfirstGame.h"
#include "Direct3D.h"
#include "Quad.h"

#define MAX_LOADSTRING 100

// グローバル変数:
const wchar_t* WIN_CLASS_NAME = L"SAMPLE GAME WINDOW";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

HWND hWnd = nullptr;

HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//↓のページはwWinMainに関してのページ
//https://learn.microsoft.com/ja-jp/windows/win32/learnwin32/winmain--the-application-entry-point
//hInstance は、 インスタンスへのハンドル またはモジュールへのハンドルです。 オペレーティング システムでは、この値を使用して、メモリに読み込まれるときに実行可能ファイルまたは EXE を識別します。 特定の Windows 関数では、アイコンやビットマップを読み込むなど、インスタンス ハンドルが必要です。
//hPrevInstance には意味がありません。 16 ビット Windows で使用されましたが、現在は常に 0 です。
//pCmdLine には、コマンド ライン引数が Unicode 文字列として含まれています。
//nCmdShow は、メイン アプリケーション ウィンドウが最小化、最大化、または正常に表示されるかどうかを示すフラグです。

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,//意味がない
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //UNREFERENCED_PARAMETERについて by AI
    //「UNREFERENCED_PARAMETER」は、C/C++などのプログラミング言語において、関数内で定義されているものの、実際にはその関数内で使用されていない関数の引数を指します。
    //つまり、宣言されているだけで、コード内で値が読み込まれたり、計算に使われたり、他の変数に代入されたりしていない引数のことです
    
    //ここではhPrevInstanceとlpCmdLineを使用しないことを明示
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;
    int winH = winRect.bottom - winRect.top;

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //先生ここに書いてるけど、hWnd設定どこでしてるのかわからないからInitInstanceの部分に書いてる
    //Direct3D初期化
    HRESULT hr;
    hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    if (FALSE(hr))
    {
        return 0;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

    MSG msg = {};

    Quad* quad = new Quad();
    hr = quad->Initialize();
    if (FALSE(hr))
    {
        return 0;
    }

    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        //メッセージあり
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //ゲームの処理

        Direct3D::BeginDraw();

        //描画処理
        quad->Draw();

        Direct3D::EndDraw();

    }

    SAFE_RELEASE(quad);
    SAFE_DELETE(quad);
    Direct3D::Release();

    return 0;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //↓このページによるとこの先に書かれてる
    //https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-wndclassexw
    //typedef struct tagWNDCLASSEXW {
    //    UINT      cbSize;//この構造体のサイズ (バイト単位)。 このメンバーをsizeof(WNDCLASSEX)に設定するGetClassInfoEx関数を呼び出す前にこのメンバーを必ず設定する
    //    UINT      style;//クラスのスタイル。このメンバーはクラススタイルの任意の組み合わせにすることができる
    //    WNDPROC   lpfnWndProc;//ウィンドウ プロシージャへのポインター。 ウィンドウ プロシージャを呼び出すにはCallWindowProc関数を使用する必要がある
    //    int       cbClsExtra;//ウィンドウクラス構造体の後に割り当てる余分なバイト数。システムはバイトをゼロに初期化する
    //    int       cbWndExtra;//ウィンドウ インスタンスの後に割り当てる余分なバイト数。 システムはバイトをゼロに初期化します。 アプリケーションで WNDCLASSEX を使用して、CLASS ディレクティブを使用して作成されたダイアログ ボックスをリソース ファイルに登録する場合は、このメンバーを DLGWINDOWEXTRAに設定する必要があります。
    //    HINSTANCE hInstance;//クラスのウィンドウプロシージャを含むインスタンスへのハンドル
    //    HICON     hIcon;//クラス アイコンへのハンドル。 このメンバーは、アイコン リソースのハンドルである必要があります。 このメンバーが NULL場合、システムは既定のアイコンを提供します。
    //    HCURSOR   hCursor;//クラス カーソルへのハンドル。 このメンバーは、カーソル リソースへのハンドルである必要があります。 このメンバーが NULL場合、アプリケーションは、マウスがアプリケーションのウィンドウに移動するたびにカーソルの形状を明示的に設定する必要があります。
    //    HBRUSH    hbrBackground;
    //    LPCWSTR   lpszMenuName;
    //    LPCWSTR   lpszClassName;
    //    HICON     hIconSm;
    //} WNDCLASSEXW, * PWNDCLASSEXW, * NPWNDCLASSEXW, * LPWNDCLASSEXW;

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    
    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する


   //CreateWindowExについて　by AI
   //CreateWindowEx関数は、Windows APIで新しいウィンドウを作成するために使用される関数です。
   //拡張スタイル、クラス名、ウィンドウ名、スタイル、位置、サイズ、親ウィンドウ、メニュー、インスタンスハンドル、および作成データなど、
   //さまざまなパラメータを指定してウィンドウをカスタマイズできます
   /*HWND CreateWindowEx(
       _In_     DWORD     dwExStyle,    //ウィンドウの拡張スタイルを指定します。例えば、WS_EX_TOPMOST（常に最前面に表示）、WS_EX_CLIENTEDGE（クライアント領域に3D効果を追加）などがあります。﻿
       _In_opt_ LPCTSTR   lpClassName,  //ウィンドウクラスの名前を指定します。事前にRegisterClassEx関数で登録されたクラス名、または定義済みのコントロールクラス名（例: "EDIT"、"BUTTON"）を使用します。﻿
       _In_opt_ LPCTSTR   lpWindowName, //ウィンドウのタイトルバーに表示される文字列を指定します。﻿
       _In_     DWORD     dwStyle,      //ウィンドウのスタイルを指定します。例えば、WS_OVERLAPPEDWINDOW（標準的なウィンドウ）、WS_CHILD（子ウィンドウ）、WS_VISIBLE（作成時に表示）などがあります。﻿
       _In_     int       x,            //ウィンドウの初期位置とサイズを指定します。CW_USEDEFAULTを指定すると、システムが適切な値を設定します。﻿
       _In_     int       y,            // ・
       _In_     int       nWidth,       // ・
       _In_     int       nHeight,      // ・
       _In_opt_ HWND      hWndParent,   //親ウィンドウのハンドルを指定します。子ウィンドウを作成する場合に指定します。デスクトップを親ウィンドウにする場合は、NULLを指定します。﻿
       _In_opt_ HMENU     hMenu,        //メニューハンドルを指定します。ポップアップウィンドウや子ウィンドウの場合に指定します。﻿
       _In_opt_ HINSTANCE hInstance,    //ウィンドウに関連付けるモジュールのインスタンスハンドルを指定します。通常は`GetModuleHandle(NULL)`で取得した値を使用します。﻿
       _In_opt_ LPVOID    lpParam       //ウィンドウプロシージャに渡されるデータへのポインターを指定します。WM\_CREATEメッセージのlParamに渡されます。﻿
   );*/

   //修正後
   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//メッセージとコールバックについてのAIの回答は下に記述

//↓はWNDPROC コールバック関数についてのページ
//https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nc-winuser-wndproc
//WNDPROC Wndproc;
//
//LRESULT Wndproc(
//    HWND unnamedParam1,   //ウィンドウへのハンドル。 通常、このパラメーターの名前は hWnd です。
//    UINT unnamedParam2,   //メッセージ。 通常、このパラメーターの名前は uMsg です。
//    WPARAM unnamedParam3, //追加のメッセージ情報。 このパラメーターは通常、 wParam という名前です。wParam パラメーターの内容は、uMsg パラメーターの値によって異なります。
//    LPARAM unnamedParam4  //追加のメッセージ情報。 通常、このパラメーターの名前は lParam です。Param パラメーターの内容は、uMsg パラメーターの値によって異なります。
//)
//{
//    ...
//}
//戻り値はメッセージ処理の結果であり、送信されたメッセージによって異なります。

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND://アプリケーション メニューの処理
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT://メイン ウィンドウを描画する
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY://中止メッセージを表示して戻る
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//メッセージとコールバック　by AI
//メッセージループとコールバックは、GUIアプリケーションやイベント駆動型プログラミングにおいて、処理を効率的に行うための重要な概念です。
//メッセージループは、アプリケーションが外部からのメッセージ（例えば、ユーザーのクリックやキー入力）を待ち受け、処理するために使用されます。
//コールバックは、特定のイベントが発生した際に、システムやライブラリが自動的に呼び出す関数です。﻿
//
//メッセージループ(Message Loop)﻿
//メッセージループは、アプリケーションがイベントやメッセージを処理するための基本的な仕組みです。
//GUIアプリケーションでは、ユーザーの操作（マウスのクリック、キーボード入力など）やシステムからの通知（ウィンドウの再描画など）は、
//メッセージとしてアプリケーションに送られます。
//これらのメッセージを処理するために、アプリケーションはメッセージループを実行します。﻿
//
//メッセージループは、通常、以下の処理を行います。﻿
//1. メッセージの取得:
//GetMessage 関数などで、メッセージキューからメッセージを取得します。
//2. メッセージの翻訳 :
//TranslateMessage 関数で、メッセージを変換します。例えば、キーボード入力メッセージを文字コードに変換するなどの処理を行います。
//3. メッセージのディスパッチ :
//DispatchMessage 関数で、メッセージを適切なウィンドウプロシージャ（ウィンドウの処理関数）にディスパッチ（転送）します。
//これにより、ウィンドウプロシージャは、メッセージの内容に応じた処理を実行します。﻿
//
//コールバック (Callback)
//コールバックは、特定のイベントが発生した際に、システムやライブラリが自動的に呼び出す関数のことです。
//例えば、ボタンがクリックされたときに、そのボタンに関連付けられたコールバック関数が呼び出されます。
//コールバック関数は、イベントが発生したときに実行されるべき処理を記述します。﻿
//
//コールバック関数は、イベント駆動型プログラミングにおいて非常に重要です。
//アプリケーションは、メッセージループでメッセージを待つだけでなく、コールバック関数を登録することで、イベントが発生したときに自動的に処理を実行できます。
//例:
//例えば、C++のWindows APIでボタンをクリックした時の処理を考えてみましょう。﻿
//ボタンがクリックされると、Windowsはメッセージを生成し、メッセージキューに格納します。
//メッセージループは、メッセージキューからメッセージを取得します。
//DispatchMessage関数は、メッセージを適切なウィンドウプロシージャにディスパッチします。
//ウィンドウプロシージャは、ボタンのクリックメッセージを処理し、事前に登録されたコールバック関数を呼び出します。
//コールバック関数は、ボタンがクリックされたときに実行されるべき処理（例えば、テキストボックスに文字列を追加する処理）を記述します。
//まとめ
//メッセージループは、アプリケーションがメッセージを待ち受け、処理するための基本的な仕組みです。
//コールバックは、特定のイベントが発生したときに、システムやライブラリが自動的に呼び出す関数であり、
//イベント駆動型プログラミングにおいて、イベントに対する処理を記述するために使用されます。
//これら二つの概念は、GUIアプリケーションやイベント駆動型プログラミングにおいて、連携して動作し、効率的な処理を実現します。﻿




