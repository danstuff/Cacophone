#pragma once

#ifndef PENDULUM_H
#define PENDULUM_H

#include "main.h"

class Pendulum{
private:
	SoundBuffer buffer;
	Sound sound;

	Color color;

	float ox, length;
	float time;

	RectangleShape sprite;

public:
	bool enabled;

	Pendulum();

	void enable();

	float getX(), getY();
	float getRadius();

	void physics(RenderWindow &window);

	void play();
	void draw(RenderWindow &window);
};

#endif