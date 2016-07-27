#include "shape.h"

void sinWave(Int16 raw[], int frequency){
	double increment = frequency/44100.0;
	double x = 0;

	//sine wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		raw[i] = SOUND_AMPLITUDE * sin(2*PI*x);
		x += increment;
	}
}

void triWave(Int16 raw[], int frequency){
	double increment = frequency/44100.0;
	double x = 0;

	bool up_phase = false;

	//triangular wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		if(x >= 1){
			up_phase = false;
			x = 1;
		}
		else if(x <= -1){
			up_phase = true;
			x = -1;
		}

		raw[i] = SOUND_AMPLITUDE * x;

		if(up_phase)
			x += increment*4;
		else
			x -= increment*4;
	}
}

void sawWave(Int16 raw[], int frequency){
	double increment = frequency/44100.0;
	double x = 0;

	//sawtooth wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		if(x >= 1)
			x = -1;
		
		raw[i] = int(SOUND_AMPLITUDE * x);

		x += increment*2;
	}
}

void drawLine(RenderWindow &window, Color &color, float x1, float y1, float x2, float y2){
	Vertex line[] = {
		Vertex(Vector2f(x1, y1), color),
		Vertex(Vector2f(x2, y2), color)
	};
	window.draw(&line[0], 2, Lines);
}

void drawCircle(RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	static CircleShape circle(1, 30);

	circle.setFillColor(color);
	circle.setRadius(radius);

	circle.setPosition(x, y);
	circle.setOrigin(radius, radius);
	circle.setRotation(rot);

	window.draw(circle);
}

void drawTriangle(RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	static CircleShape triangle(1, 3);

	triangle.setFillColor(color);
	triangle.setRadius(radius);

	triangle.setPosition(x, y);
	triangle.setOrigin(radius, radius);
	triangle.setRotation(rot);

	window.draw(triangle);
}

void drawSquare(RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	static RectangleShape square(Vector2f(1, 1));

	square.setFillColor(color);
	square.setSize(Vector2f(radius*2, radius*2));

	square.setPosition(x, y);
	square.setOrigin(radius, radius);
	square.setRotation(45 + rot);

	window.draw(square);
}