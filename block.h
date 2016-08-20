#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "main.h"

struct Block{
	float x, y;

	float pulse;

	bool erase;
};

void createBlock(float x, float y);

void tickBlocks(RenderWindow &window);
void drawBlocks(RenderWindow &window);

void cleanupBlocks();

void clearBlocks();

#endif