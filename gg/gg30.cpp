#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wininet.h>
#include "json.hpp"

#pragma comment(lib, "wininet.lib")

using json = nlohmann::json;

#define ID_INPUT 101
#define HOTKEY_ID 1

bool isValidUser = false;  // Determines if functionalities should be enabled
std::string uniqueID;      // Store the unique hardware ID

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string GetUniqueID();
bool VerifyID(const std::string& id);
std::string SendAPIRequest(const std::string& input);
void DisplayID(HWND hwnd);

// Retrieve BIOS Serial Number
std::string GetUniqueID() {
    char buffer[128];
    std::string result;
    FILE* pipe = _popen("wmic bios get serialnumber", "r");
    if (!pipe) return "UNKNOWN";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    _pclose(pipe);

    // Clean the output
    size_t pos = result.find("\n");
    if (pos != std::string::npos) {
        result = result.substr(pos + 1);
    }
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());

    return result.empty() ? "UNKNOWN" : result;
}

// Check ID from server
bool VerifyID(const std::string& id) {
    std::string url = "/api/checkmac/" + id;
    HINTERNET hInternet = InternetOpen("HTTPAPI", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return false;

    HINTERNET hConnect = InternetConnect(hInternet, "request.vercel.app", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return false;
    }

    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", url.c_str(), NULL, NULL, NULL, 0, 0);
    if (!hRequest) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return false;
    }

    if (!HttpSendRequest(hRequest, NULL, 0, NULL, 0)) {
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return false;
    }

    // Read Response
    char buffer[1024];
    DWORD bytesRead;
    std::string response;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead) {
        buffer[bytesRead] = 0;
        response += buffer;
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    // Parse JSON response
    try {
        json jsonData = json::parse(response);
        return jsonData["exists"].get<bool>(); // Assuming API returns { "exists": true }
    } catch (...) {
        return false;
    }
}

// Display ID on screen and disable functionality
void DisplayID(HWND hwnd) {
    std::string message = "Your Unique ID:\n" + uniqueID + "\n\nAccess Denied.";
    MessageBox(hwnd, message.c_str(), "Access Denied", MB_OK | MB_ICONWARNING);
}

// WinMain Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    uniqueID = GetUniqueID();
    isValidUser = VerifyID(uniqueID);

    const char CLASS_NAME[] = "API_AUTH_WINDOW";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED,
        CLASS_NAME, "Gemini AI API Caller",
        WS_POPUP, 100, 100, 400, 300,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) return 0;

    SetLayeredWindowAttributes(hwnd, 0, (255 * 90) / 100, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    RegisterHotKey(hwnd, HOTKEY_ID, MOD_ALT | MOD_SHIFT, 0x56);
    ShowWindow(hwnd, SW_SHOW);

    // If ID is invalid, show the ID and prevent access
    if (!isValidUser) {
        DisplayID(hwnd);
        return 0;  // Terminate app
    }

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
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
