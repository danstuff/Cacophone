#include "spring.h"

Spring::Spring(){
	//set up the sound buffer
	const uint SAMPLE_RATE = 44100; //samples per second
	const uint SAMPLES = SAMPLE_RATE*5; //total samples
	const uint AMPLITUDE = 1000;

	Int16 raw[SAMPLES];

	int frequency = random(8)*110;

	double increment = frequency/44100.0;
	double x = 0;

	//sine wave
	for(uint i = 0; i < SAMPLES; i++){
		//square wave
		if(x < 0.5)
			raw[i] = AMPLITUDE;
		else
			raw[i] = -AMPLITUDE;

		if(x > 1)
			x = 0;

		x += increment;
	}
		
	buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);

	//set up the physical properties of the instrument
	sprite.setFillColor(Color(random(255), random(255), random(255)));
	sprite.setRadius(frequency/10);
}

void Spring::play(){
	sound.stop();
	sound.setBuffer(buffer);
	sound.play();
}

void Spring::draw(RenderWindow *window){
	window->draw(sprite);
}