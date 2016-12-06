#pragma once
#include "stdafx.h"

class OptionsController : public MainController
{
public:
	OptionsController(GameConfiguration * config);
	~OptionsController();

	void updateWindow() override;
	void createButtons() override;
	void manageChoice(Button & _button) override;

private:
	Button * typeChoice;
	Button * difficultyChoice;
	Button * imageChoice;
	Button * defaultImage;
	Button * customImage;

	GameConfiguration * configuration;
};

