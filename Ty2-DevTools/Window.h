#pragma once
#include "pch.h"

class Window
{
public:
	virtual ~Window() = default;
	virtual void ToggleVisibility() = 0;
	virtual void Draw(int outerWidth, int outerHeight, float uiScale) = 0;
	bool isVisible = true;
	const std::string name = "";
	Window(const std::string& n) : name(n) {}
};

