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
	char id[128] = "";
private:
	std::string message;
};