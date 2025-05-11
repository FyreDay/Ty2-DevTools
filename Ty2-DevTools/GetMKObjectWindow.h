#pragma once
#include "Window.h"

class GetMKObjectWindow : public Window {
public:
	GetMKObjectWindow() : Window("GetObject") {
		isVisible = false;
	};
	void ToggleVisibility() override;
	void Draw(int outerWidth, int outerHeight, float uiScale) override;
	bool LoadLoginData(std::string& objectId);
	char id[128] = "";
};