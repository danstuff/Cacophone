#include "main.h"
#include "bouncing_ball.h"
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

	vector<BouncingBall> balls;
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
					Keyboard::isKeyPressed(Keyboard::LShift)){
					BouncingBall ball;
					balls.push_back(ball);
				}
				else if(event.mouseButton.button == Mouse::Left &&
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

		for(uint i = 0; i < balls.size(); i++){
			if(!balls[i].enabled && !Mouse::isButtonPressed(Mouse::Left))
				balls[i].enable();
		
			balls[i].physics(window);
			balls[i].draw(window);
			
			float bx = balls[i].getX();
			float by = balls[i].getY();
			float br = balls[i].getRadius();

			//if the ball is too close to right-clicked mouse, delete it
			if(Mouse::isButtonPressed(Mouse::Right) &&
				sqrt(pow(bx - mx + br, 2) + pow(by - my + br, 2)) < balls[i].getRadius()){
					balls.erase(balls.begin() + i);
			}
		}

		for(uint i = 0; i < pendulums.size(); i++){
			if(!pendulums[i].enabled && !Mouse::isButtonPressed(Mouse::Left))
				pendulums[i].enable();
		
			pendulums[i].physics(window);
			pendulums[i].draw(window);
			
			float bx = pendulums[i].getX();
			float by = pendulums[i].getY();
			float br = pendulums[i].getRadius();

			//if the ball is too close to right-clicked mouse, delete it
			if(Mouse::isButtonPressed(Mouse::Right) &&
				sqrt(pow(bx - mx + br, 2) + pow(by - my + br, 2)) < pendulums[i].getRadius()){
					pendulums.erase(pendulums.begin() + i);
			}
		}

        window.display();
    }

    return 0;
}