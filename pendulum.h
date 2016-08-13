#pragma once

#ifndef PENDULUM_H
#define PENDULUM_H

#include "main.h"
#include "shape.h"

struct Pendulum{
	SoundBuffer buffer;
	Sound sound;

	ShapeType shape;
	
	Color color;
	float radius;

	float x, y;
	float rot;

	float ox, oy;
	float time;

	bool erase;
};

void createPendulum(float x, float y, ShapeType shape);

void tickPendulums(RenderWindow &window);
void drawPendulums(RenderWindow &window);

void cleanupPendulums();

void clearPendulums();

#endif