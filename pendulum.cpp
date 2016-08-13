#include "pendulum.h"

const float INC = 0.1f/MS_PER_UPDATE;

int random(int max){
	if(max <= 0) return 0;

	return rand() % max;
}

vector<Pendulum> pendulums;

void createPendulum(float x, float y, ShapeType shape){
	Pendulum p;

	//initialize basic nessecary values
	p.shape = shape;

	p.x = x;
	p.y = y;
	p.rot = 0;

	p.ox = x;
	p.oy = y;
	p.time = float(PI)/2;

	//set up the sound buffer
	int frequency = (random(7) + 1)*110;

	Int16 raw[SOUND_SAMPLES];

	makeWave(shape, raw, frequency);

	p.buffer.loadFromSamples(raw, SOUND_SAMPLES, 1, SOUND_SAMPLE_RATE);

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

		//if the pendulum collided with the right-clicked mouse, flag for deletion
		if(mouse_erase && sqrt((p.x-mx)*(p.x-mx) + (p.y-my)*(p.y-my)) < p.radius){
			p.erase = true;
		}

		//do all physics calculations for the pendulum
		if(p.erase == false){
			p.time += INC;

			if(p.time >= 2*PI){
				p.sound.setBuffer(p.buffer);
				p.sound.play();

				p.time = 0;
			}
			else if(p.time >= PI - INC/2 && p.time <= PI + INC/2){
				p.sound.setBuffer(p.buffer);
				p.sound.play();
			}

			float o = cos(p.time) + float(PI)/2;

			p.x = p.ox + p.oy*cos(o);
			p.y = p.oy*sin(o);

			p.rot = o*180/float(PI);
		}
	}
}
void drawPendulums(RenderWindow &window){
	for(uint i = 0; i < pendulums.size(); i++){
		Pendulum &p = pendulums[i];
		
		if(!p.erase){
			drawLine(window, p.color, p.ox, 0, p.x, p.y);
			drawShape(p.shape, window, p.color, p.radius, p.x, p.y, p.rot);
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