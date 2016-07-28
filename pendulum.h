#pragma once

#ifndef PENDULUM_H
#define PENDULUM_H

#include "main.h"
#include "shape.h"

class Pendulum{
private:
	SoundBuffer buffer;
	Sound sound;

	ShapeType shape;

	Color color;
	float radius;

	float x, y;
	float rot;

	float ox, length;
	float time;

public:
	Pendulum(float px, float py, ShapeType stype);

	void enable();

	void play();

	bool collidedWith(int px, int py);
	
	void physics(RenderWindow &window);

	void draw(RenderWindow &window);
};

#endif