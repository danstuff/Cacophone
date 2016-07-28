#include "main.h"
#include "pendulum.h"

vector<Pendulum> pendulums;

ShapeType toolShape = CIRCLE;
Color toolColor(100, 100, 100, 100);

int random(int max){
	if(max <= 0) return 0;

	return rand() % max;
}

void handleEvents(RenderWindow &window){
	int mx = Mouse::getPosition(window).x;
	int my = Mouse::getPosition(window).y;

	Event event;
	while (window.pollEvent(event)){

		switch(event.type){

		case Event::Closed:
			window.close();
			break;

		case Event::MouseButtonPressed:
			if(event.mouseButton.button == Mouse::Left){
				Pendulum pend(mx, my, toolShape);
				pendulums.push_back(pend);
			}
			break;

		case Event::MouseWheelMoved:
			int d = event.mouseWheel.delta;
			toolShape = ShapeType(toolShape + d);

			if(toolShape < CIRCLE)	toolShape = CIRCLE;
			if(toolShape > SQUARE)	toolShape = SQUARE;
			break;
		}
	}
}

void pendulumPhysics(RenderWindow &window){
	int mx = Mouse::getPosition(window).x;
	int my = Mouse::getPosition(window).y;

	for(uint i = 0; i < pendulums.size(); i++){		
		pendulums[i].physics(window);

		//if the ball is too close to right-clicked mouse, delete it
		if(Mouse::isButtonPressed(Mouse::Right) &&
			pendulums[i].collidedWith(mx, my)){
				pendulums.erase(pendulums.begin() + i);
		}
	}
}

int main(){
	//set random seed
	SYSTEMTIME gtime;
	GetSystemTime(&gtime);
	srand((uint)gtime.wMilliseconds);

	//set up the window
    RenderWindow window(VideoMode(640, 480), "Cacophone");
	window.setKeyRepeatEnabled(false);

	//timer for lag compensation
	Clock runTime;

	double lag = 0.0;

    while (window.isOpen()){
		double elapsed = runTime.restart().asMicroseconds();
		lag += elapsed;

		handleEvents(window);

		while(lag >= MS_PER_UPDATE){
			pendulumPhysics(window);
			lag -= MS_PER_UPDATE;
		}		

		//drawing
        window.clear();

		//draw tool at mouse cursor
		int mx = Mouse::getPosition(window).x;
		int my = Mouse::getPosition(window).y;

		if(Mouse::isButtonPressed(Mouse::Right))
			drawX(window, toolColor, 20, mx, my, 0);
		else
			drawShape(toolShape, window, toolColor, 20, mx, my, 0);
		
		//loop and draw all pendulums
		for(uint i = 0; i < pendulums.size(); i++){		
			pendulums[i].draw(window);
		}

        window.display();
    }

    return 0;
}