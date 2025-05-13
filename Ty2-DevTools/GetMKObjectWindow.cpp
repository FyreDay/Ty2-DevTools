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
            uintptr_t address =FindObjectPtr(oID);
            char hexStr[20];

            sprintf_s(hexStr, "0x%p", (void*)address);
            SetMessage(hexStr);
        }
        catch (const std::invalid_argument& e) {
            SetMessage("ID Not an int");
            API::LogPluginMessage(e.what());
        }
    }
    ImGui::InputText("Pointer", message.data(), message.size(), ImGuiInputTextFlags_ReadOnly);
    ImGui::InputText("Mission Ptr", mptr, IM_ARRAYSIZE(id));
    if (ImGui::Button("Add Mission")) {
        try {
            // Try converting the char array to an int using std::stoi
            uintptr_t addr = static_cast<uintptr_t>(std::stoull(mptr, nullptr, 16));
            bool success = InsertMission(addr);
            SetMessage(success ? "Wow!": "Awww");
        }
        catch (const std::invalid_argument& e) {
            SetMessage("uh oh");
            API::LogPluginMessage(e.what());
        }
    }
    ImGui::InputText("Opal Amount", opalcount, IM_ARRAYSIZE(id));
    if (ImGui::Button("Add Opals")) {
        try {
            // Try converting the char array to an int using std::stoi
            int value = std::atoi(opalcount);
            AddOpals(value);
            SetMessage("Tried to add Opals");
        }
        catch (const std::invalid_argument& e) {
            SetMessage("uh oh");
            API::LogPluginMessage(e.what());
        }
    }
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

bool GetMKObjectWindow::InsertMission(uintptr_t missionPtr) {
    using insertmission = uint32_t(__thiscall*)(uintptr_t thisPtr, uintptr_t objPtr);
    insertmission getObjPtr = reinterpret_cast<insertmission>((uintptr_t)API::Get()->param()->TyHModule + 0x00117670);
    uintptr_t thisPtr = (uintptr_t)API::Get()->param()->TyHModule + 0x4EB580 + 0x1bc;

    bool success = (getObjPtr(thisPtr, missionPtr) & 0xFF) != 0;
    return success;
}

void GetMKObjectWindow::AddOpals(int amount) {
    using Addopals = uint32_t(__thiscall*)(uintptr_t thisPtr, uintptr_t objPtr);
    Addopals addopals = reinterpret_cast<Addopals>((uintptr_t)API::Get()->param()->TyHModule + 0x00119fb0);
    uintptr_t thisPtr = (uintptr_t)API::Get()->param()->TyHModule+ 0x4EB580;

    addopals(thisPtr, amount);
    return;
}