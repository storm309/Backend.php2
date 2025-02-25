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

    HINTERNET hConnect = InternetConnect(hInternet, "requestmac.vercel.app", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return false;
    }

    HINTERNET hRequest = HttpOpenRequest(hConnect, "GET", url.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
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

    // Debug: Print API Response
    std::cout << "API Response: " << response << std::endl;

    try {
        json jsonData = json::parse(response);
        std::cout << "Parsed message: " << jsonData["message"] << std::endl;
        return jsonData["message"].get<std::string>() == "yes";
    } catch (const std::exception& e) {
        std::cout << "JSON Parsing Error: " << e.what() << std::endl;
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

    std::cout << "User Verified: " << isValidUser << std::endl;

    const char CLASS_NAME[] = "API_AUTH_WINDOW";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,  
        CLASS_NAME, "Gemini AI API Caller",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) {
        MessageBox(nullptr, "Failed to create the window!", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd); // Ensure the window is updated

    // If ID is invalid, show the ID and prevent access
    if (!isValidUser) {
        DisplayID(hwnd);
        DestroyWindow(hwnd);
        return 0;  // Terminate app
    }

    std::cout << "Entering Message Loop..." << std::endl;

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) { // Proper message loop
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
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
