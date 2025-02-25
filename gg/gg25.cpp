#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wininet.h>
#include "json.hpp"
#include <ole2.h>

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "uuid.lib")

using json = nlohmann::json;

#define ID_TEXTAREA 101
#define HOTKEY_ID 1

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string SendAPIRequest(const std::string& input);
std::string ReadFileContent(const std::string& filePath);

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
                    std::wstring ws(data);
                    std::string inputText(ws.begin(), ws.end());
                    std::string response = SendAPIRequest(inputText);
                    SetWindowText(m_hwndTarget, response.c_str());
                    GlobalUnlock(stg.hGlobal);
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

bool isVisible = true;
HWND hTextArea;
MyDropTarget* pDropTarget = nullptr;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    OleInitialize(nullptr);
    
    const char CLASS_NAME[] = "GeminiOverlay";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, CLASS_NAME, "Gemini AI Drag & Drop", WS_POPUP,
                               100, 100, 400, 300, nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 0;
    
    SetLayeredWindowAttributes(hwnd, 0, (255 * 90) / 100, LWA_ALPHA);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    RegisterHotKey(hwnd, HOTKEY_ID, MOD_ALT | MOD_SHIFT, 0x56);
    ShowWindow(hwnd, SW_SHOW);
    
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
    }
    OleUninitialize();
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch(uMsg) {
        case WM_CREATE: {
            LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
            hTextArea = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL,
                                     20, 20, 340, 220, hwnd, (HMENU)ID_TEXTAREA, pcs->hInstance, nullptr);
            pDropTarget = new MyDropTarget(hTextArea);
            RegisterDragDrop(hTextArea, pDropTarget);
            break;
        }
        case WM_HOTKEY:
            if (wParam == HOTKEY_ID) ShowWindow(hwnd, isVisible ? SW_HIDE : SW_SHOW), isVisible = !isVisible;
            break;
        case WM_CLOSE:
            RevokeDragDrop(hTextArea);
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
    return "Gemini Response: " + input;
}


// Working finne but not draggable
