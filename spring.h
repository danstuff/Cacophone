#pragma once

#ifndef SPRING_H
#define SPRING_H

#include "main.h"

class Spring{
private:
	SoundBuffer buffer;
	Sound sound;

	CircleShape sprite;

public:
	Spring();

	void play();

	void draw(RenderWindow *window);
};

#endif