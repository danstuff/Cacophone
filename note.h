#pragma once

#ifndef NOTE_H
#define NOTE_H

#include "main.h"

class Note{
private:
	bool playing;

	float pitch;
	float start_time;
	float duration;

	Sound sound;

	RectangleShape rect;

public:
	Note();

	bool play(float time, SoundBuffer &buffer);
	void draw(RenderWindow *window);
};

#endif