#include <windows.h>
#include <string>
#include <iostream>
#include <wininet.h>

#pragma comment(lib, "wininet.lib")

#define ID_INPUT 101
#define ID_BUTTON 102
#define ID_OUTPUT 103

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string SendAPIRequest(const std::string& input);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "FTHAPICaller";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, "FTH AI API Caller", WS_OVERLAPPED | WS_SYSMENU,
                               CW_USEDEFAULT, CW_USEDEFAULT, 400, 200, NULL, NULL, hInstance, NULL);

    if (!hwnd) return 0;

    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hInput, hButton, hOutput;

    switch (uMsg) {
        case WM_CREATE:
            hInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE,
                                  20, 20, 340, 20, hwnd, (HMENU) ID_INPUT, NULL, NULL);
            hButton = CreateWindow("BUTTON", "Send", WS_CHILD | WS_VISIBLE,
                                   150, 50, 100, 30, hwnd, (HMENU) ID_BUTTON, NULL, NULL);
            hOutput = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE,
                                   20, 90, 340, 50, hwnd, (HMENU) ID_OUTPUT, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON) {
                char inputText[256];
                GetWindowText(hInput, inputText, sizeof(inputText));
                std::string response = SendAPIRequest(inputText);
                SetWindowText(hOutput, response.c_str());
            }
            break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

std::string SendAPIRequest(const std::string& input) {
    HINTERNET hInternet = InternetOpen("HTTPAPI", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "Internet Open Failed";
    
    HINTERNET hConnect = InternetOpenUrl(hInternet, "https://fth-ai-api.com/query", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "Connection Failed";
    }
    
    char buffer[1024];
    DWORD bytesRead;
    std::string response;
    while (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = 0;
        response += buffer;
    }
    
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return response.empty() ? "No Response" : response;
}
