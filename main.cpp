#include "main.h"
#include "note.h"

float random(float max){
	return ((float)rand() / (float)RAND_MAX) * max;
}

int main(){
	//set random seed
	SYSTEMTIME gtime;
	GetSystemTime(&gtime);
	srand((uint)gtime.wMilliseconds);

	vector<Note> notes;
	
	for(uint i = 0; i < 10; i++){
		Note note;

		notes.push_back(note);
	}

	//set up the window
    RenderWindow window(VideoMode(640, 480), "Cacophone");

	Clock song_time;

	RectangleShape progress(Vector2f(1, 640));
	progress.setFillColor(Color::Red);

    while (window.isOpen()){
		//check for an exiting event
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();

		for(uint i = 0; i < notes.size(); i++){
			notes[i].draw(&window);
			notes[i].play(song_time.getElapsedTime().asSeconds());
		}

		if(song_time.getElapsedTime().asSeconds() >= SONG_DURATION)
			song_time.restart();

		progress.setPosition((song_time.getElapsedTime().asSeconds()/SONG_DURATION)*640, 0);

		window.draw(progress);

        window.display();
    }

    return 0;
}