#pragma once

#ifndef PENDULUM_H
#define PENDULUM_H

#include "main.h"
#include "shape.h"

struct Pendulum{
	ShapeSound ss;

	Color color;

	float x, y, ox, oy;

	float radius;
	float rotation;

	float time;

	float pulse;

	bool erase;
};

void createPendulum(float x, float y, ShapeType shape);

void tickPendulums(RenderWindow &window);
void drawPendulums(RenderWindow &window);

void cleanupPendulums();

void clearPendulums();

vector<Pendulum> &getPendulums();

#endif