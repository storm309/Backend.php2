#include <windows.h>
#include <string>
#include <iostream>
#include <wininet.h>
#include <nlohmann/json.hpp> // Include a JSON library (e.g., nlohmann/json)

#pragma comment(lib, "wininet.lib")

using json = nlohmann::json;

#define ID_INPUT 101
#define ID_BUTTON 102
#define ID_OUTPUT 103

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
std::string SendAPIRequest(const std::string& input);
std::string ExtractGeneratedText(const std::string& jsonResponse);

// ... [Rest of WinMain and WindowProc remains the same until the SendAPIRequest call]

std::string SendAPIRequest(const std::string& input) {
    const std::string apiKey = "AIzaSyB0G4NtJlvCr9GRlnvp1McqWrUbXCIQBx4"; // Replace with your actual API key
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

    std::string postData = R"({"contents":[{"parts":[{"text":")" + input + R"("}]}]})";

    const char* headers = "Content-Type: application/json\r\n";

    if (!HttpSendRequest(hRequest, headers, strlen(headers), (LPVOID)postData.c_str(), postData.size())) {
        DWORD error = GetLastError();
        InternetCloseHandle(hRequest);
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return "Request Send Failed, Error Code: " + std::to_string(error);
    }

    char buffer[4096];
    DWORD bytesRead;
    std::string response;
    while (InternetReadFile(hRequest, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        response += buffer;
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    if (response.empty()) {
        return "No Response";
    }

    // Parse the JSON response to extract the generated text
    return ExtractGeneratedText(response);
}

std::string ExtractGeneratedText(const std::string& jsonResponse) {
    try {
        json parsed = json::parse(jsonResponse);

        if (parsed.contains("candidates") && !parsed["candidates"].empty()) {
            const auto& candidate = parsed["candidates"][0];
            if (candidate.contains("content") && candidate["content"].contains("parts")) {
                const auto& parts = candidate["content"]["parts"];
                if (!parts.empty() && parts[0].contains("text")) {
                    return parts[0]["text"].get<std::string>();
                }
            }
        } else if (parsed.contains("error")) {
            return "API Error: " + parsed["error"]["message"].get<std::string>();
        }
        return "No text found in response";
    } catch (const json::exception& e) {
        return "JSON Parse Error: " + std::string(e.what());
    }
}