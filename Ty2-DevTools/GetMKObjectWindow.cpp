#include "pch.h"
#include "GetMKObjectWindow.h"

void GetMKObjectWindow::ToggleVisibility() {
    isVisible = !isVisible;
}

void LoginWindow::Draw(int outerWidth, int outerHeight, float uiScale) {
    if (!isVisible)
        return;
    // Draw getObject window
    ImGui::Begin(name.c_str(), &isVisible, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::InputText("Server", server, IM_ARRAYSIZE(server));