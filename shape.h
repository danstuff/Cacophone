#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "main.h"

const uint SOUND_SAMPLE_RATE	= 44100;				//samples per second
const uint SOUND_SAMPLES		= SOUND_SAMPLE_RATE/4;	//total samples
const uint SOUND_AMPLITUDE		= 1000;

enum ShapeType{
	CIRCLE,
	TRIANGLE,
	DIAMOND,
	SQUARE
};

struct ShapeSound{
	SoundBuffer buffer;
	Sound sound;

	ShapeType shape;
};

void setVolume(uint nv);

void makeWave(ShapeSound &ss, int frequency);

void playWave(ShapeSound &ss);

void startNoise();

void stopNoise();

void drawShape(ShapeType shape, RenderWindow &window, Color &color, float radius, float x, float y, float rot);

void drawLine(RenderWindow &window, Color &color, float x1, float y1, float x2, float y2);

void drawX(RenderWindow &window, Color &color, float radius, float x, float y, float rot);

#endif