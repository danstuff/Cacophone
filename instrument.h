#pragma once

#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "main.h"

class Instrument{
private:
	bool playing;

	SoundBuffer buffer;
	Sound sound;

	RectangleShape rect;

public:
	Instrument();

	void play(float pitch);
	void stop();

	void draw(RenderWindow *window);

	void reset();
};

#endif