#pragma once

#ifndef BOUNCING_BALL_H
#define BOUNCING_BALL_H

#include "main.h"

class BouncingBall{
private:
	SoundBuffer buffer;
	Sound sound;

	Color color;

	float xacc, yacc;
	float xvel, yvel;

	CircleShape sprite;

public:
	bool enabled;

	BouncingBall();

	void enable();

	float getX(), getY();
	float getRadius();

	void physics(RenderWindow &window);

	void play();
	void draw(RenderWindow &window);
};

#endif