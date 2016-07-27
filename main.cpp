#include "main.h"
#include "pendulum.h"

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
	window.setKeyRepeatEnabled(false);

	vector<Pendulum> pendulums;

	bool mousedown = false;

    while (window.isOpen()){
		//check for an exiting event
        Event event;
        while (window.pollEvent(event)){

			switch(event.type){

			case Event::Closed:
				window.close();
				break;

			case Event::MouseButtonPressed:
				if(event.mouseButton.button == Mouse::Left &&
					Keyboard::isKeyPressed(Keyboard::Z)){
					Pendulum pend;
					pendulums.push_back(pend);
				}
				break;
			}
        }

		//drawing and processing
        window.clear();

		int mx = Mouse::getPosition(window).x;
		int my = Mouse::getPosition(window).y;

		for(uint i = 0; i < pendulums.size(); i++){
			if(!pendulums[i].enabled && !Mouse::isButtonPressed(Mouse::Left))
				pendulums[i].enable();
		
			pendulums[i].physics(window);
			pendulums[i].draw(window);

			//if the ball is too close to right-clicked mouse, delete it
			if(Mouse::isButtonPressed(Mouse::Right) && pendulums[i].collidedWith(mx, my)){
					pendulums.erase(pendulums.begin() + i);
			}
		}

        window.display();
    }

    return 0;
}