#pragma once
#include "pch.h"
#include "Window.h"


class GetMKObjectWindow : public Window {
public:
	GetMKObjectWindow() : Window("GetObject") {
		isVisible = false;
	};
	void ToggleVisibility() override;
	void Draw(int outerWidth, int outerHeight, float uiScale) override;
	void SetMessage(std::string);
	uintptr_t FindObjectPtr(int objectId);
	bool InsertMission(uintptr_t missionPtr);
	void AddOpals(int amount);
	char id[128] = "";
	char mptr[128] = "";
	char opalcount[128] = "";
private:
	std::string message;
};