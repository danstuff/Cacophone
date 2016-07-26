#include "bouncing_ball.h"

BouncingBall::BouncingBall(){
	//set up the sound buffer
	const uint SAMPLE_RATE = 44100; //samples per second
	const uint SAMPLES = SAMPLE_RATE/4; //total samples
	const uint AMPLITUDE = 1000;

	Int16 raw[SAMPLES];

	int frequency = (random(7) + 1)*110;

	double increment = frequency/44100.0;
	double x = 0;

	//sine wave
	for(uint i = 0; i < SAMPLES; i++){
		raw[i] = (Int16) (AMPLITUDE * sin(2*PI*x));
		x += increment;
	}
		
	buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);

	//set up the physical properties of the instrument
	sprite.setFillColor(Color(100, 100, 100, 100));
	sprite.setRadius(SHAPE_RADIUS);
	sprite.setOrigin(SHAPE_RADIUS, SHAPE_RADIUS);

	int freqfac = int((frequency/880.0f)*255);

	color.r = freqfac + 1 - random(freqfac);
	color.g = (freqfac - color.r) + 1 - random(freqfac - color.r);
	color.b = freqfac - color.g;

	enabled = false;
}

void BouncingBall::enable(){
	sprite.setFillColor(color);

	xvel = 0;
	yvel = 0;

	enabled = true;
}

float BouncingBall::getX(){
	return sprite.getPosition().x;
}
float BouncingBall::getY(){
	return sprite.getPosition().y;
}
float BouncingBall::getRadius(){
	return sprite.getRadius();
}

void BouncingBall::physics(RenderWindow &window){
	if(!enabled){
		sprite.setPosition(Vector2f(Mouse::getPosition(window)));

		return;
	}

	float x = sprite.getPosition().x;
	float y = sprite.getPosition().y;

	float r = sprite.getRadius();

	yvel += 0.0001f;

	x += xvel;
	y += yvel;

	if(y + r >= HEIGHT){
		yvel = -abs(yvel);
		play();
	}
	else if(y - r <= 0){
		yvel = abs(yvel);
		play();
	}

	if(x + r >= WIDTH){
		xvel = -abs(xvel);
		play();
	}
	else if(x - r<= 0){
		xvel = abs(xvel);
		play();
	}

	sprite.setPosition(x, y);
}

void BouncingBall::play(){
	sound.stop();
	sound.setBuffer(buffer);
	sound.play();
}
void BouncingBall::draw(RenderWindow &window){
	window.draw(sprite);
}