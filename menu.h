#pragma once

#ifndef MENU_H
#define MENU_H

#include "main.h"

const string SETTINGS_FILE = "cacophone.dat";

enum MState{
	TITLE,
	SETTINGS,
	PLAY,
	RESTART
};

struct MenuTitle{
	Text title;

	Text play;
	Text settings;

	Text credits;
};

struct MenuSettings{
	Text volume;
	Text volume_up;
	Text volume_down;
	uint volume_value;
	Text volume_value_text;

	Text noise;
	bool noise_value;

	Text width;
	Text width_up;
	Text width_down;
	uint width_value;
	Text width_value_text;

	Text height;
	Text height_up;
	Text height_down;
	uint height_value;
	Text height_value_text;

	Text aalias;
	bool aalias_value;

	Text confirm;
};

bool inState(MState tstate);

void defaultSettings();

void loadSettings();
void saveSettings();

MenuSettings getSettings();

void initMenu(Font &font);

void tickMenu(RenderWindow &window);
void drawMenu(RenderWindow &window);

#endif