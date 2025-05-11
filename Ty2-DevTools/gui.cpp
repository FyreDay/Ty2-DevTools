#include "pch.h"
#include "gui.h"


std::vector<std::unique_ptr<Window>> GUI::windows;
//std::map<std::string, unsigned int> GUI::icons;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool GUI::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_KEYDOWN && wParam == VK_F2) {
        for (auto& window : windows) {
            if (auto MKObject = dynamic_cast<GetMKObjectWindow*>(window.get())) {
                MKObject->ToggleVisibility();
                API::LogPluginMessage("Toggle GetObject window.");
                break;
            }
        }
    }
    if (API::DrawingGUI())
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;
    return false;
}


void GUI::Initialize() {
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.3f;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    HWND tyWindowHandle = API::GetTyWindowHandle();
    if (tyWindowHandle == 0) {
        API::LogPluginMessage("Error: Invalid window handle.");
        GUI::init = false;
        return;
    }

    ImGui_ImplOpenGL3_Init();
    ImGui_ImplWin32_InitForOpenGL(API::GetTyWindowHandle());

    windows.push_back(std::make_unique<GetMKObjectWindow>());

    API::LogPluginMessage("Initialized ImGui successfully.");
    GUI::init = true;
}

void GUI::DrawUI() {
    if (!GUI::init)
        Initialize();

    HWND hwnd = (HWND)API::GetTyWindowHandle();
    RECT rect;
    if (!GetClientRect(hwnd, &rect)) {
        API::LogPluginMessage("Failed to get window size.");
        return;
    }
    int windowWidth = rect.right - rect.left;
    int windowHeight = rect.bottom - rect.top;
    const int baseWidth = 1920;
    const int baseHeight = 1080;
    float widthScale = static_cast<float>(windowWidth) / baseWidth;
    float heightScale = static_cast<float>(windowHeight) / baseHeight;
    float uiScale = (((widthScale) < (heightScale)) ? (widthScale) : (heightScale));

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    //ImGui::SetNextWindowPos(ImVec2(windowWidth - (114 * uiScale), 0));


    
    for (auto& window : windows) { window.get()->Draw(windowWidth, windowHeight, uiScale); }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool GUI::ImGuiWantCaptureMouse() {
    return GUI::init && ImGui::GetIO().WantCaptureMouse;
}
