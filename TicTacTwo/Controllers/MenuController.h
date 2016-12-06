#pragma once
#include "stdafx.h"
#include <list>

class MenuController : public MainController
{
public:
	MenuController(GameConfiguration * config);
	~MenuController();

	void createButtons() override;
	void manageChoice(Button & _button) override;
};

