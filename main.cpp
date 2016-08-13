#include "main.h"
#include "pendulum.h"
#include "block.h"

ShapeType toolShape = CIRCLE;
Color toolColor(100, 100, 100, 100);

void handleEvents(RenderWindow &window){
	float mx = float(Mouse::getPosition(window).x);
	float my = float(Mouse::getPosition(window).y);

	Event event;
	while (window.pollEvent(event)){

		switch(event.type){

		case Event::Closed:
			window.close();
			break;

		case Event::KeyPressed:
			if(event.key.code == Keyboard::Escape)
				window.close();
			break;

		case Event::MouseButtonPressed:
			if(event.mouseButton.button == Mouse::Left){
				if(toolShape == SQUARE)
					createBlock(mx, my);
				else
					createPendulum(mx, my, toolShape);
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

int main(){
	//set random seed
	SYSTEMTIME gtime;
	GetSystemTime(&gtime);
	srand((uint)gtime.wMilliseconds);

	//turn on anti-aliasing
	ContextSettings settings;
	settings.antialiasingLevel = 4;

	//set up the window
	RenderWindow window(VideoMode(640, 480), "Cacophone", Style::Default, settings);
	window.setKeyRepeatEnabled(false);

	//timer for lag compensation
	Clock runTime;

	double lag = 0.0;

    while (window.isOpen()){
		double elapsed = runTime.restart().asMicroseconds()/1000.0;
		lag += elapsed;
		
		cout << "Frame Rate: " << (1/elapsed)*1000 << endl;
		
		while(lag >= MS_PER_UPDATE){
			handleEvents(window);

			//ticking
			tickPendulums(window);
			tickBlocks(window);

			cleanupPendulums();
			cleanupBlocks();

			lag -= MS_PER_UPDATE;
		}		

		//drawing
        window.clear(Color(100, 200, 200));

		//draw tool at mouse cursor
		float mx = float(Mouse::getPosition(window).x);
		float my = float(Mouse::getPosition(window).y);

		if(Mouse::isButtonPressed(Mouse::Right))
			drawX(window, toolColor, 20, mx, my, 0);
		else
			drawShape(toolShape, window, toolColor, 20, mx, my, 0);
		
		//draw objects
		drawPendulums(window);
		drawBlocks(window);

        window.display();
    }

	clearPendulums();
	clearBlocks();

    return 0;
}