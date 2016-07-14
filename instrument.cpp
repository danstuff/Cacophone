#include "instrument.h"

Instrument::Instrument(){
	//set up the sound buffer
	const uint SAMPLE_RATE = 44100; //samples per second
	const uint SAMPLES = SAMPLE_RATE*5; //total samples
	const uint AMPLITUDE = 1000;

	int type = random(5);

	Int16 raw[SAMPLES];

	const double increment = 440.0/44100;
	double x = 0;

	bool up_phase = true;

	for(uint i = 0; i < SAMPLES; i++){
		switch(type){
		case 0:		
			//sine wave
			raw[i] = AMPLITUDE * sin(2*PI*x);
			x += increment;
			break;
		case 1:		
			//square wave
			if(x < 0.5)
				raw[i] = AMPLITUDE;
			else
				raw[i] = -AMPLITUDE;

			if(x > 1)
				x = 0;

			x += increment;
			break;
		case 2:		
			//sawtooth wave
			if(x >= 1)
				x = -1;

			raw[i] = AMPLITUDE * x;

			x += increment*2;
			break;
		case 3:		
			//triangular wave
			if(x >= 1){
				up_phase = false;
				x = 1;
			}
			else if(x <= -1){
				up_phase = true;
				x = -1;
			}

			raw[i] = AMPLITUDE * x;

			if(up_phase)
				x += increment*4;
			else
				x -= increment*4;
			break;
		case 4:
			raw[i] = random(AMPLITUDE);
			break;
		}
	}
		
	buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);

	//set up the physical properties of the instrument
	rect.setFillColor(Color(random(255), random(255), random(255)));
	rect.setSize(Vector2f(random(200)+100, random(200)+100));
	rect.setPosition(100, 100);
}

void Instrument::play(float pitch){
	sound.stop();

	sound.setBuffer(buffer);
	sound.setPitch(pitch);
	sound.setLoop(true);

	sound.play();
}
void Instrument::stop(){
	sound.stop();
}

void Instrument::draw(RenderWindow *window){
	window->draw(rect);
}