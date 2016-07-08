#include "note.h"

Note::Note(){
	playing = false;

	pitch = random(10)+1;
	start_time = random(SONG_DURATION);
	duration = random(SONG_DURATION-start_time)+1;

	//set up the note's display
	rect.setPosition(start_time*64, pitch*40);
	rect.setSize(Vector2f(duration*64, 10.0f));
	rect.setFillColor(Color((uint)random(255), (uint)random(255), (uint)random(255)));

	//set up the sound buffer
	const uint SAMPLE_RATE = 44100; //samples per second
	const uint SAMPLES = SAMPLE_RATE*5; //total samples
	const uint AMPLITUDE = 1000;

	Int16 raw[SAMPLES];

	const double increment = (110.0*pitch)/44100;
	double x = 0;

	for(uint i = 0; i < SAMPLES; i++){
		raw[i] = AMPLITUDE * sin(2*PI*x);
		x += increment;
	}
		
	buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE);
}

bool Note::play(float time){
	if(time >= start_time && time <= start_time+duration && !playing){
		sound.setBuffer(buffer);
		sound.setLoop(true);
		sound.play();

		playing = true;
		return true;
	}
	else if((time < start_time || time > start_time+duration) && playing){
		sound.stop();

		playing = false;
	}

	return false;
}

void Note::draw(RenderWindow *window){
	window->draw(rect);
}