// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "gui.h"

void TickBeforeGame(float deltaSeconds) {
    GUI::DrawUI();
}

extern "C" __declspec(dllexport) bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    //Make sure to call this first before any API Functions
    if (!API::Initialize(param))
        return false;

    API::AddTickBeforeGame(TickBeforeGame);
    API::AddPluginImGuiWantCaptureMouse((ImGuiWantCaptureMouseFunc)GUI::ImGuiWantCaptureMouse);
    API::AddPluginWndProc((WndProcFunc)GUI::WndProc);
    API::LogPluginMessage(std::to_string(((int)API::Get()->param()->TyHModule)));
    return true;
}

extern "C" __declspec(dllexport) void TygerFrameworkPluginRequiredVersion(TygerFrameworkPluginVersion* version) {
    version->Major = 1;
    version->Minor = 1;
    version->Patch = 3;
    version->CompatibleGames = { 2 };
}