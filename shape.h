#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "main.h"

const uint SOUND_SAMPLE_RATE	= 44100;				//samples per second
const uint SOUND_SAMPLES		= SOUND_SAMPLE_RATE/4;	//total samples
const uint SOUND_AMPLITUDE		= 1000;					//volume

enum ShapeType{
	CIRCLE,
	TRIANGLE,
	SQUARE
};

void sinWave(Int16 raw[], int frequency);

void triWave(Int16 raw[], int frequency);

void sawWave(Int16 raw[], int frequency);

void drawLine(RenderWindow &window, Color &color, float x1, float y1, float x2, float y2);

void drawCircle(RenderWindow &window, Color &color, float radius, float x, float y, float rot);

void drawTriangle(RenderWindow &window, Color &color, float radius, float x, float y, float rot);

void drawSquare(RenderWindow &window, Color &color, float radius, float x, float y, float rot);

#endif