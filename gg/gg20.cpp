#include <windows.h>
#include <string>
#include <iostream>
#include <wininet.h>
#include <sstream>
#include "json.hpp"

#pragma comment(lib, "wininet.lib")

using json = nlohmann::json;

#define ID_INPUT 101
#define ID_BUTTON 102
#define ID_OUTPUT 103
#define HOTKEY_ID 1

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string SendAPIRequest(const std::string& input);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char CLASS_NAME[] = "GeminiAPICaller";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST,  // Makes window top-most
        CLASS_NAME,
        "Gemini AI API Caller",
        WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        400, 300,
        NULL, NULL, hInstance, NULL
    );

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
            // Register Alt+Shift+V hotkey
            if (!RegisterHotKey(hwnd, HOTKEY_ID, MOD_ALT | MOD_SHIFT, 0x56)) {
                MessageBox(hwnd, "Hotkey registration failed!", "Error", MB_ICONERROR);
            }

            // Create UI elements
            hInput = CreateWindow(
                "EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                20, 20, 340, 20, hwnd, (HMENU)ID_INPUT, NULL, NULL
            );
            hButton = CreateWindow(
                "BUTTON", "Send", WS_CHILD | WS_VISIBLE,
                150, 50, 100, 30, hwnd, (HMENU)ID_BUTTON, NULL, NULL
            );
            hOutput = CreateWindow(
                "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL,
                20, 90, 340, 150, hwnd, (HMENU)ID_OUTPUT, NULL, NULL
            );
            break;

        case WM_HOTKEY:
            if (wParam == HOTKEY_ID) {
                if (IsWindowVisible(hwnd)) {
                    ShowWindow(hwnd, SW_HIDE);
                } else {
                    ShowWindow(hwnd, SW_SHOW);
                    SetForegroundWindow(hwnd);  // Bring to front
                    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // Ensure top-most
                }
            }
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
            UnregisterHotKey(hwnd, HOTKEY_ID);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

std::string SendAPIRequest(const std::string& input) {
    const std::string apiKey = "AIzaSyB0G4NtJlvCr9GRlnvp1McqWrUbXCIQBx4";  // Replace with your API key
    const std::string apiUrl = "/v1beta/models/gemini-pro:generateContent?key=" + apiKey;

    HINTERNET hInternet = InternetOpen("HTTPAPI", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "Internet Open Failed";

    HINTERNET hConnect = InternetConnect(
        hInternet, "generativelanguage.googleapis.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0
    );
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "Connection Failed";
    }

    HINTERNET hRequest = HttpOpenRequest(
        hConnect, "POST", apiUrl.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0
    );
    if (!hRequest) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "Request Open Failed";
    }

    // Prepare JSON payload
    std::string postData = R"({"contents":[{"parts":[{"text":")" + input + R"("}]}]})";

    // Set headers
    std::string headers = "Content-Type: application/json\r\n";

    if (!HttpSendRequest(hRequest, headers.c_str(), headers.length(), (LPVOID)postData.c_str(), postData.length())) {
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "Request Send Failed";
    }

    // Read response
    char buffer[4096];
    DWORD bytesRead;
    std::string response;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = 0;
        response += buffer;
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    // Parse JSON to extract response text
    try {
        json jsonData = json::parse(response);
        if (!jsonData["candidates"].empty() && !jsonData["candidates"][0]["content"]["parts"].empty()) {
            return jsonData["candidates"][0]["content"]["parts"][0]["text"];
        }
    } catch (const std::exception& e) {
        return "JSON Parse Error: " + std::string(e.what());
    }

    return response.empty() ? "No Response" : response;
}