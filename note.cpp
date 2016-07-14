#include "note.h"

Note::Note(){
	playing = false;

	pitch = random(100)/50.0f;
	start_time = random(SONG_DURATION);
	duration = random(SONG_DURATION-start_time)+1;

	//set up the note's display
	rect.setPosition(start_time*64, pitch*40+10);
	rect.setSize(Vector2f(duration*64, 10.0f));
	rect.setFillColor(Color((uint)random(255), (uint)random(255), (uint)random(255)));

	sound.setPitch(pitch);
}

bool Note::play(float time, SoundBuffer &buffer){
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