#include "main.h"
#include "instrument.h"

int random(int max){
	return rand() % max;
}

int main(){
	//set random seed
	SYSTEMTIME gtime;
	GetSystemTime(&gtime);
	srand((uint)gtime.wMilliseconds);

	//set up the window
    RenderWindow window(VideoMode(640, 480), "Cacophone");

	Clock song_time;

	RectangleShape progress(Vector2f(1, 640));
	progress.setFillColor(Color::Red);

	Instrument instrument;

	instrument.play(1);

    while (window.isOpen()){
		//check for an exiting event
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }

		//timing and progress bar
		if(song_time.getElapsedTime().asSeconds() >= SONG_DURATION)
			song_time.restart();

		progress.setPosition((song_time.getElapsedTime().asSeconds()/SONG_DURATION)*640, 0);

		//drawing
        window.clear();

		window.draw(progress);

		instrument.draw(&window);

        window.display();
    }

    return 0;
}