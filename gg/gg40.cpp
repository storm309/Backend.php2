#include <regex> // Add this include for regex support
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wininet.h>
#include <ole2.h>
#include <shlobj.h> // For IID_IDropTarget
#include <algorithm> // For std::remove
#include "json.hpp"
#include <initguid.h>  // Must be included before defining GUIDs

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

using json = nlohmann::json;

//----------------------------------------------------------
// Global definitions and variables
//----------------------------------------------------------
DEFINE_GUID(IID_IDropTarget, 0x00000122, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
#define ID_INPUT 101
#define HOTKEY_ID 1

bool isVisible = true;
HWND hInput;
class MyDropTarget; // Forward declaration
MyDropTarget* pDropTarget = nullptr;

// Variables for hardware ID verification
std::string uniqueID;
bool isValidUser = false;

//----------------------------------------------------------
// Function Declarations
//----------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string SendAPIRequest(const std::string& input);
std::string ReadFileContent(const std::string& filePath);

// Hardware ID and Verification functions
std::string GetUniqueID();
bool VerifyID(const std::string& id);
void DisplayID(HWND hwnd);

//----------------------------------------------------------
// OLE Drop Target Class for Drag and Drop
//----------------------------------------------------------
class MyDropTarget : public IDropTarget {
public:
    MyDropTarget(HWND hwndTarget) : m_refCount(1), m_hwndTarget(hwndTarget) {}

    HRESULT __stdcall QueryInterface(REFIID riid, void** ppvObject) override {
        if (!ppvObject) return E_POINTER;
        if (riid == IID_IUnknown || riid == IID_IDropTarget) {
            *ppvObject = static_cast<IDropTarget*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    ULONG __stdcall AddRef(void) override { return InterlockedIncrement(&m_refCount); }
    ULONG __stdcall Release(void) override {
        ULONG count = InterlockedDecrement(&m_refCount);
        if (count == 0) delete this;
        return count;
    }

    HRESULT __stdcall DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        *pdwEffect = HasText(pDataObj) ? DROPEFFECT_COPY : DROPEFFECT_NONE;
        return S_OK;
    }
    HRESULT __stdcall DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        *pdwEffect = DROPEFFECT_COPY;
        return S_OK;
    }
    HRESULT __stdcall DragLeave() override { return S_OK; }
    
    HRESULT __stdcall Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) override {
        if (HasText(pDataObj)) {
            FORMATETC fmt = { CF_UNICODETEXT, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
            STGMEDIUM stg = {};
            if (SUCCEEDED(pDataObj->GetData(&fmt, &stg))) {
                wchar_t* data = static_cast<wchar_t*>(GlobalLock(stg.hGlobal));
                if (data) {
                    SetWindowTextW(m_hwndTarget, data);
                    GlobalUnlock(stg.hGlobal);
                    // Automatically send API request
                    char inputText[512];
                    GetWindowTextA(m_hwndTarget, inputText, sizeof(inputText));
                    std::string response = SendAPIRequest(inputText);
                    SetWindowTextA(m_hwndTarget, response.c_str());
                }
                ReleaseStgMedium(&stg);
            }
            *pdwEffect = DROPEFFECT_COPY;
        } else {
            *pdwEffect = DROPEFFECT_NONE;
        }
        return S_OK;
    }
    
private:
    LONG m_refCount;
    HWND m_hwndTarget;
    bool HasText(IDataObject* pDataObj) {
        FORMATETC fmt = { CF_UNICODETEXT, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        return (pDataObj->QueryGetData(&fmt) == S_OK);
    }
};

//----------------------------------------------------------
// WinMain: Entry Point
//----------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize OLE for drag-and-drop support
    OleInitialize(nullptr);

    // ----------------------------
    // Hardware ID Verification
    // ----------------------------
    uniqueID = GetUniqueID();
    isValidUser = VerifyID(uniqueID);
    if (!isValidUser) {
        // Show message box with the unique ID and deny access
        std::string message = "Your Unique ID:\n" + uniqueID + "\n\nAccess Denied.";
        MessageBox(NULL, message.c_str(), "Access Denied", MB_OK | MB_ICONWARNING);
        OleUninitialize();
        return 0;
    }
    
    // ----------------------------
    // Create Main Window (Overlay)
    // ----------------------------
    const char CLASS_NAME[] = "F-22 Raptor";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, 
        CLASS_NAME, "Falcon",
        WS_POPUP, 100, 100, 400, 300,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hwnd) {
        OleUninitialize();
        return 0;
    }

    SetLayeredWindowAttributes(hwnd, 0, (255 * 90) / 100, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    RegisterHotKey(hwnd, HOTKEY_ID, MOD_ALT | MOD_SHIFT, 0x56);
    ShowWindow(hwnd, SW_SHOW);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    OleUninitialize();
    return 0;
}

//----------------------------------------------------------
// Toggle Window Visibility (Hotkey Handler)
//----------------------------------------------------------
void ToggleVisibility(HWND hwnd) {
    isVisible = !isVisible;
    ShowWindow(hwnd, isVisible ? SW_SHOW : SW_HIDE);
    if (isVisible) {
        SetForegroundWindow(hwnd);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

//----------------------------------------------------------
// Window Procedure for handling messages
//----------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            hInput = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL,
                                  20, 20, 360, 250, hwnd, (HMENU)ID_INPUT, pcs->hInstance, nullptr);

            DragAcceptFiles(hwnd, TRUE);
            pDropTarget = new MyDropTarget(hInput);
            RegisterDragDrop(hInput, pDropTarget);
            break;
        }
        case WM_DROPFILES: {
            HDROP hDrop = (HDROP)wParam;
            char droppedFile[MAX_PATH];
            if (DragQueryFile(hDrop, 0, droppedFile, MAX_PATH)) {
                std::string fileContent = ReadFileContent(droppedFile);
                SetWindowText(hInput, fileContent.c_str());
                std::string response = SendAPIRequest(fileContent);
                SetWindowText(hInput, response.c_str());
            }
            DragFinish(hDrop);
            break;
        }
        case WM_HOTKEY:
            if (wParam == HOTKEY_ID) ToggleVisibility(hwnd);
            break;
        case WM_NCHITTEST: {
            LRESULT hit = DefWindowProc(hwnd, uMsg, wParam, lParam);
            if (hit == HTCLIENT) return HTCAPTION;
            return hit;
        }
        case WM_CLOSE:
            RevokeDragDrop(hInput);
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

//----------------------------------------------------------
// Utility: Read File Content
//----------------------------------------------------------
std::string ReadFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return "Failed to open file";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

//----------------------------------------------------------
// Utility: Send API Request to Gemini AI
//----------------------------------------------------------
std::string SendAPIRequest(const std::string& input) {
    const std::string apiKey = "AIzaSyB0G4NtJlvCr9GRlnvp1McqWrUbXCIQBx4";  // Replace with your API key
    const std::string apiUrl = "/v1beta/models/gemini-pro:generateContent?key=" + apiKey;
    
    HINTERNET hInternet = InternetOpen("HTTPAPI", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) return "Internet Open Failed";

    HINTERNET hConnect = InternetConnect(hInternet, "generativelanguage.googleapis.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if (!hConnect) {
        InternetCloseHandle(hInternet);
        return "Connection Failed";
    }

    HINTERNET hRequest = HttpOpenRequest(hConnect, "POST", apiUrl.c_str(), NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
    if (!hRequest) {
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "Request Open Failed";
    }

    // Set Headers and prepare JSON payload
    std::string headers = "Content-Type: application/json\r\n";
    std::string postData = R"({"contents":[{"parts":[{"text":")" + input + R"("}]}]})";

    if (!HttpSendRequest(hRequest, headers.c_str(), headers.length(), (LPVOID)postData.c_str(), postData.length())) {
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "Request Send Failed";
    }

    // Read Response
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

    // Parse JSON to extract the response text
    try {
        json jsonData = json::parse(response);
        if (!jsonData["candidates"].empty() && !jsonData["candidates"][0]["content"]["parts"].empty()) {
            std::string rawText = jsonData["candidates"][0]["content"]["parts"][0]["text"];

            // Clean up the text using regex
            std::regex starRegex(R"(\*+)"); // Matches one or more '*' characters
            std::string cleanedText = std::regex_replace(rawText, starRegex, "");

            // Ensure newlines are preserved
            cleanedText = std::regex_replace(cleanedText, std::regex(R"(\r\n|\r|\n)"), "\n"); // Normalize newlines

            // Remove extra spaces and newlines
            cleanedText = std::regex_replace(cleanedText, std::regex(R"(\s{2,})"), " "); // Replace multiple spaces with a single space
            cleanedText = std::regex_replace(cleanedText, std::regex(R"(\n{2,})"), "\n"); // Replace multiple newlines with a single newline

            // Trim leading and trailing whitespace
            cleanedText.erase(0, cleanedText.find_first_not_of(" \n\r\t"));
            cleanedText.erase(cleanedText.find_last_not_of(" \n\r\t") + 1);

            return cleanedText;
        }
    } catch (const std::exception& e) {
        return "JSON Parse Error: " + std::string(e.what());
    }

    return response.empty() ? "No Response" : response;
}

//--------bytesRead--------------------------------------------------
// Hardware ID Functions
//----------------------------------------------------------

// Retrieve BIOS Serial Number as the unique hardware ID
std::string GetUniqueID() {
    char buffer[128];
    std::string result;
    FILE* pipe = _popen("wmic bios get serialnumber", "r");
    if (!pipe) return "UNKNOWN";

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    _pclose(pipe);

    // Clean up the result by removing header and newline characters
    size_t pos = result.find("\n");
    if (pos != std::string::npos) {
        result = result.substr(pos + 1);
    }
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    return result.empty() ? "UNKNOWN" : result;
}

// Check the unique ID against the server
// Check the unique ID against the server
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

    // Read the API response
    char buffer[1024];
    DWORD bytesRead;
    std::string response;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = 0;
        response += buffer;
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    try {
        json jsonData = json::parse(response);
        return jsonData["message"].get<std::string>() == "yes";
    } catch (const std::exception& e) {
        return false;
    }
}
// Display the unique ID along with an access denied message (if needed)
void DisplayID(HWND hwnd) {
    std::string message = "Your Unique ID:\n" + uniqueID + "\n\nAccess Denied.";
    MessageBox(hwnd, message.c_str(), "Access Denied", MB_OK | MB_ICONWARNING);
}