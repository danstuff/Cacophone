#include "pendulum.h"

Pendulum::Pendulum(float px, float py, ShapeType pshape){
	//initialize basic nessecary values
	shape = pshape;

	x = px;
	y = py;
	rot = 0;

	ox = x;
	length = y;
	time = float(PI)/2;

	//set up the sound buffer
	int frequency = (random(7) + 1)*110;

	Int16 raw[SOUND_SAMPLES];

	makeWave(shape, raw, frequency);

	buffer.loadFromSamples(raw, SOUND_SAMPLES, 1, SOUND_SAMPLE_RATE);

	//randomly set color, higher freq = brighter color, will mostly be blueish
	int brightness = int((frequency/880.0f)*255);

	color.r = brightness - random(brightness);
	color.g = (brightness - color.r) - random(brightness - color.r);
	color.b = brightness - color.g;

	//set radius based on frequency
	radius = 80 - (frequency/11.0f);
}

bool Pendulum::collidedWith(int px, int py){
	return sqrt(pow(x - px + radius, 2) + pow(y - py + radius, 2)) < radius;
}

void Pendulum::physics(RenderWindow &window){
	time += 0.00001f;

	if(time >= 2*PI){
		play();
		time = 0;
	}
	else if(time >= PI - 0.0001 && time <= PI + 0.0001){
		play();
	}

	float o = cos(time) + float(PI)/2;

	x = ox + length*cos(o);
	y = length*sin(o);

	rot = o*180/float(PI);
}

void Pendulum::play(){
	sound.stop();
	sound.setBuffer(buffer);
	sound.play();
}
void Pendulum::draw(RenderWindow &window){
	drawLine(window, color, ox, 0, x, y);

	drawShape(shape, window, color, radius, x, y, rot);
}