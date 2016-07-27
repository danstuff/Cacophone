#include "pendulum.h"

Pendulum::Pendulum(){
	//set up the sound buffer
	int frequency = (random(7) + 1)*110;

	Int16 raw[SOUND_SAMPLES];
	sinWave(raw, frequency);

	buffer.loadFromSamples(raw, SOUND_SAMPLES, 1, SOUND_SAMPLE_RATE);

	//randomly set color, higher freq = brighter color, will mostly be blue
	int brightness = int((frequency/880.0f)*255);

	color.r = brightness + 1 - random(brightness);
	color.g = (brightness - color.r) + 1 - random(brightness - color.r);
	color.b = brightness - color.g;

	//set other nessecary values
	radius = 80 - (frequency/11);

	x = y = 0;
	rot = 0;

	ox = length = 0;
	time = 0;

	enabled = false;
}

void Pendulum::enable(){
	ox = x;
	length = y;
	time = PI/2;

	enabled = true;
}

bool Pendulum::collidedWith(int px, int py){
	return sqrt(pow(x - px + radius, 2) + pow(y - py + radius, 2)) < radius;
}

void Pendulum::physics(RenderWindow &window){
	if(!enabled){
		x = Mouse::getPosition(window).x;
		y = Mouse::getPosition(window).y;
		return;
	}
	
	time += 0.001f;

	if(time >= 2*PI){
		play();
		time = 0;
	}

	float o = cos(time) + PI/2;

	x = ox + length*cos(o);
	y = length*sin(o);

	rot = o*180/PI;
}

void Pendulum::play(){
	sound.stop();
	sound.setBuffer(buffer);
	sound.play();
}
void Pendulum::draw(RenderWindow &window){
	drawLine(window, color, ox, 0, x, y);
	drawCircle(window, color, radius, x, y, rot);
}