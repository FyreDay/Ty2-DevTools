#include "pch.h"
#include "GetMKObjectWindow.h"

void GetMKObjectWindow::ToggleVisibility() {
    isVisible = !isVisible;
}

void GetMKObjectWindow::Draw(int outerWidth, int outerHeight, float uiScale) {
    if (!isVisible)
        return;
    // Draw getObject window
    ImGui::Begin(name.c_str(), &isVisible, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::InputText("Object Id", id, IM_ARRAYSIZE(id));

    if (ImGui::Button("Find Ptr")) {
        int oID = 0;
        try {
            // Try converting the char array to an int using std::stoi
            oID = std::stoi(id);
            SetMessage(std::to_string(FindObjectPtr(oID)));
        }
        catch (const std::invalid_argument& e) {
            SetMessage("ID Not an int");
            API::LogPluginMessage(e.what());
        }
    }
    ImGui::InputText("Pointer", message.data(), message.size(), ImGuiInputTextFlags_ReadOnly);
    ImGui::End();
}

void GetMKObjectWindow::SetMessage(std::string newMessage) {
    message = newMessage;
}

uintptr_t GetMKObjectWindow::FindObjectPtr(int objectId) {
    uintptr_t result;
    uintptr_t(*getObjPtr)(int) = reinterpret_cast<uintptr_t(*)(int)>(((uintptr_t)API::Get()->param()->TyHModule) + 0x00314f10);
    __asm {
        push objectId
        call getObjPtr
        add esp, 0x4
        mov result, eax
    }
    return result;
}