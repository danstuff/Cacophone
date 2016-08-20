#include "shape.h"

ShapeSound noise;

void sinWave(Int16 raw[], int frequency){
	double increment = double(frequency)/44100.0;
	double x = 0;

	//sine wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		raw[i] = Int16(SOUND_AMPLITUDE * sin(2*PI*x));
		x += increment;
	}
}

void triWave(Int16 raw[], int frequency){
	double increment = double(frequency)/44100.0;
	double x = -1;

	bool up_phase = true;

	//triangular wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		if(x > 1){
			up_phase = false;
			x = 1;
		}
		else if(x < -1){
			up_phase = true;
			x = -1;
		}

		raw[i] = Int16(SOUND_AMPLITUDE * x);

		if(up_phase)
			x += increment*4;
		else
			x -= increment*4;
	}
}

void sawWave(Int16 raw[], int frequency){
	double increment = double(frequency)/44100.0;
	double x = 0;

	//sawtooth wave
	for(uint i = 0; i < SOUND_SAMPLES; i++){
		if(x >= 1)
			x = -1;

		raw[i] = Int16(SOUND_AMPLITUDE*0.35 * x);

		x += increment*2;
	}
}

void noiseWave(Int16 raw[]){
	double lval = 0, mval = 0;
	double lval_s = 0, mval_s = 0;
	double lval_t = 0, mval_t = 0;

	for(uint i = 0; i < SOUND_SAMPLES*16; i++){
		if(i % 30 == 0){
			lval_t = random(10)/10.0;
			lval_s = (lval_t - lval)/20;
		}
		if(i % 15 == 0){
			mval_t = random(10)/10.0;
			mval_s = (mval_t - mval)/10;
		}

		lval += lval_s;
		mval += mval_s;

		double hval = random(5)/10.0;

		raw[i] = SOUND_AMPLITUDE/16 * (hval + mval + lval);
	}
}

void makeWave(ShapeSound &ss, int frequency){
	Int16 raw[SOUND_SAMPLES];

	switch(ss.shape){
	case CIRCLE:
		sinWave(raw, frequency);
		break;
	case TRIANGLE:
		triWave(raw, frequency);
		break;
	case DIAMOND:
		sawWave(raw, frequency);
		break;
	}

	ss.buffer.loadFromSamples(raw, SOUND_SAMPLES, 1, SOUND_SAMPLE_RATE);
}

void playWave(ShapeSound &ss){
	ss.sound.setBuffer(ss.buffer);
	ss.sound.play();
}

void startNoise(){
	Int16 raw[SOUND_SAMPLES*16];

	noiseWave(raw);

	noise.buffer.loadFromSamples(raw, SOUND_SAMPLES*16, 1, SOUND_SAMPLE_RATE);
	noise.sound.setBuffer(noise.buffer);
	noise.sound.setLoop(true);
	noise.sound.play();
}

void stopNoise(){
	noise.sound.stop();
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
	triangle.setRotation(rot-90);

	window.draw(triangle);
}

void drawSquare(RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	static RectangleShape square(Vector2f(1,1));

	square.setFillColor(color);

	square.setPosition(x, y);
	square.setSize(Vector2f(radius*2, radius*2));
	square.setOrigin(radius, radius);
	square.setRotation(rot);

	window.draw(square);
}

void drawShape(ShapeType shape, RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	switch(shape){
	case CIRCLE:
		drawCircle(window, color, radius, x, y, rot);
		break;
	case TRIANGLE:
		drawTriangle(window, color, radius, x, y, rot);
		break;
	case DIAMOND:
		drawSquare(window, color, radius, x, y, 45+rot);
		break;
	case SQUARE:
		drawSquare(window, color, radius, x, y, rot);
		break;
	}
}


void drawLine(RenderWindow &window, Color &color, float x1, float y1, float x2, float y2){
	Vertex line[] = {
		Vertex(Vector2f(x1, y1), color),
		Vertex(Vector2f(x2, y2), color)
	};
	window.draw(&line[0], 2, Lines);
}

void drawX(RenderWindow &window, Color &color, float radius, float x, float y, float rot){
	static RectangleShape r1(Vector2f(1, 1));
	static RectangleShape r2(Vector2f(1, 1));

	r1.setSize(Vector2f(radius*2, radius/2));
	r2.setSize(Vector2f(radius*2, radius/2));

	r1.setFillColor(color);
	r2.setFillColor(color);

	r1.setOrigin(radius, radius/4);
	r2.setOrigin(radius, radius/4);

	r1.setPosition(x, y);
	r2.setPosition(x, y);
	
	r1.setRotation(rot - 45);
	r2.setRotation(rot + 45);

	window.draw(r1);
	window.draw(r2);
}