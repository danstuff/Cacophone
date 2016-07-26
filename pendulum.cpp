#include "pendulum.h"

Pendulum::Pendulum(){
	//set up the sound buffer
	const uint SAMPLE_RATE = 44100; //samples per second
	const uint SAMPLES = SAMPLE_RATE/4; //total samples
	const uint AMPLITUDE = 1000;

	Int16 raw[SAMPLES];

	int frequency = (random(7) + 1)*110;

	double increment = frequency/44100.0;
	double x = 0;

	//sawtooth wave
	for(uint i = 0; i < SAMPLES; i++){
		if(x >= 1)
			x = -1;
		
		raw[i] = int(AMPLITUDE * x);

		x += increment*2;
	}
		
	buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);

	//set up the physical properties of the instrument
	sprite.setFillColor(Color(100, 100, 100, 100));
	sprite.setSize(Vector2f(SHAPE_RADIUS*2, SHAPE_RADIUS*2));
	sprite.setOrigin(SHAPE_RADIUS, SHAPE_RADIUS);
	sprite.setRotation(45);

	int freqfac = int((frequency/880.0f)*255);

	color.r = freqfac + 1 - random(freqfac);
	color.g = (freqfac - color.r) + 1 - random(freqfac - color.r);
	color.b = freqfac - color.g;

	enabled = false;

	ox = 0;
}

void Pendulum::enable(){
	sprite.setFillColor(color);

	ox = sprite.getPosition().x;
	length = sprite.getPosition().y;
	time = PI/2;

	enabled = true;
}

float Pendulum::getX(){
	return sprite.getPosition().x;
}
float Pendulum::getY(){
	return sprite.getPosition().y;
}
float Pendulum::getRadius(){
	return sprite.getSize().x/2;
}

void Pendulum::physics(RenderWindow &window){
	if(!enabled){
		sprite.setPosition(Vector2f(Mouse::getPosition(window)));

		return;
	}
	
	time += 0.001f;

	if(time >= 2*PI){
		play();
		time = 0;
	}

	float o = cos(time) + PI/2;

	float x = ox + length*cos(o);
	float y = length*sin(o);

	sprite.setRotation(45 + o*180/PI);
	sprite.setPosition(x, y);
}

void Pendulum::play(){
	sound.stop();
	sound.setBuffer(buffer);
	sound.play();
}
void Pendulum::draw(RenderWindow &window){
	Vertex line[] = {
		Vector2f(ox, 0),
		sprite.getPosition()
	};
	window.draw(&line[0], 2, Lines);
	window.draw(sprite);
}