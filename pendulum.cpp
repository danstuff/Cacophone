#include "pendulum.h"

vector<Pendulum> pendulums;

uint cap(int val, float inc, int max){
	val += int(inc);

	if(val > max)
		val = max;
	else if(val < 0)
		val = 0;

	return uint(val);
}

void createPendulum(float x, float y, ShapeType shape){
	Pendulum p;

	//initialize basic nessecary values
	p.ss.shape = shape;

	p.x = p.ox = x;
	p.y = p.oy = y;
	p.rotation = 0;

	p.time = float(PI)/2;

	p.pulse = 0;

	//set up the sound buffer
	int frequency = (random(7) + 1)*110;

	makeWave(p.ss, frequency);

	//randomly set color, higher freq = brighter color, will mostly be blueish
	int brightness = int((frequency/880.0f)*255);

	p.color.r = brightness - random(brightness);
	p.color.g = (brightness - p.color.r) - random(brightness - p.color.r);
	p.color.b = brightness - p.color.g;

	//set radius based on frequency
	p.radius = 80 - (frequency/11.0f);

	p.erase = false;

	pendulums.push_back(p);
}

void tickPendulums(RenderWindow &window){
	int mx = Mouse::getPosition(window).x;
	int my = Mouse::getPosition(window).y;

	bool mouse_erase = Mouse::isButtonPressed(Mouse::Right);

	for(uint i = 0; i < pendulums.size(); i++){
		Pendulum &p = pendulums[i];

		//if pendulum collided with the right-clicked mouse, flag for deletion
		if(mouse_erase && sqrt((p.x-mx)*(p.x-mx) + (p.y-my)*(p.y-my)) < p.radius+20){
			p.erase = true;
		}

		//pendulum ticking
		if(p.erase == false){
			//swing calculations
			p.time += INC;

			float o = cos(p.time) + float(PI)/2;

			p.x = p.ox + p.oy*cos(o);
			p.y = p.oy*sin(o);

			p.rotation = o*180/float(PI);

			//play sound at both ends of the swing
			if(p.time >= 2*PI){
				playWave(p.ss);

				p.pulse = 1;
				p.time = 0;
			}
			else if(p.time >= PI - INC/2 && p.time <= PI + INC/2){
				playWave(p.ss);

				p.pulse = 1;
			}

			//tween pulse
			if(p.pulse != 0)
				p.pulse -= p.pulse*INC;
		}
	}
}

void drawPendulums(RenderWindow &window){
	for(uint i = 0; i < pendulums.size(); i++){		
		if(!pendulums[i].erase){
			Pendulum &p = pendulums[i];

			Color pcol = p.color;
			Color rcol = p.color;

			float cfac = p.pulse*150;
			float sfac = p.pulse*10;

			pcol.r = cap(pcol.r, cfac, 254);
			pcol.g = cap(pcol.g, cfac, 254);
			pcol.b = cap(pcol.b, cfac, 254);

			rcol.r = cap(rcol.r, cfac-100, 254);
			rcol.g = cap(rcol.g, cfac-100, 254);
			rcol.b = cap(rcol.b, cfac-100, 254);

			drawLine(window, rcol, p.ox, 0, p.x, p.y);
			drawShape(p.ss.shape, window, pcol, p.radius+sfac, p.x, p.y, p.rotation);
		}
	}
}

void cleanupPendulums(){
	//for performance, must be called multiple times to erase all flagged
	for(uint i = 0; i < pendulums.size(); i++){
		if(pendulums[i].erase){
			pendulums.erase(pendulums.begin() + i);
			return;
		}
	}
}

void clearPendulums(){
	pendulums.clear();
}

vector<Pendulum> &getPendulums(){
	return pendulums;
}