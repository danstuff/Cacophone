#include "main.h"
#include "pendulum.h"
#include "block.h"
#include "menu.h"

ShapeType toolShape = CIRCLE;
Color toolColor(100, 100, 100, 100);
float tool_radius = 10;

int random(int max){
	if(max <= 0) return 0;

	return rand() % max;
}

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
				tool_radius = 1;

				if(inState(PLAY)){
					if(toolShape == SQUARE)
						createBlock(mx, my);
					else
						createPendulum(mx, my, toolShape);
				}				
			}
			break;

		case Event::MouseWheelMoved:
			int d = event.mouseWheel.delta;
			toolShape = ShapeType(toolShape + d);

			if(toolShape < CIRCLE)	
				toolShape = CIRCLE;
			else if(toolShape > SQUARE)
				toolShape = SQUARE;
			else
				tool_radius = 1;

			break;
		}
	}
}

int game(){
	//load settings
	ContextSettings settings;

	loadSettings();

	if(getSettings().aalias_value)
		settings.antialiasingLevel = 4;
	
	//set up the window
	RenderWindow window(VideoMode(450, 450), "Cacophone", Style::Titlebar, settings);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	
	//load font
	Font font;
	font.loadFromFile(FONT_FILE);

	//display loading splash
	window.clear(Color(160, 200, 200));

	Text text("loading...", font, 30);

	FloatRect bnds = text.getLocalBounds();
	text.setOrigin(bnds.width/2, bnds.height/2);

	text.setPosition(225, 225);

	window.draw(text);

	window.display();

	//start noise
	if(getSettings().noise_value)
		startNoise();

	//create menus
	initMenu(font);

	//update window size
	window.setSize(Vector2u(getSettings().width_value, getSettings().height_value));

	View view(FloatRect(0, 0, getSettings().width_value, getSettings().height_value));
	window.setView(view);

	//start timer for lag compensation
	Clock runTime;
	double lag = 0.0;

	while (window.isOpen()){
		//drawing
		window.clear(Color(160, 200, 200));

		//draw objects
		drawPendulums(window);
		drawBlocks(window);
		
		drawMenu(window);

		//draw tool at mouse cursor
		float mx = float(Mouse::getPosition(window).x);
		float my = float(Mouse::getPosition(window).y);

		if(Mouse::isButtonPressed(Mouse::Right))
			drawX(window, toolColor, tool_radius, mx, my, 0);
		else if(toolShape == TRIANGLE)
			drawShape(toolShape, window, toolColor, tool_radius, mx, my, -30);
		else
			drawShape(toolShape, window, toolColor, tool_radius, mx, my, 0);

		window.display();

		//ticking
		double ms_elapsed = runTime.restart().asMicroseconds()/1000.0;
		lag += ms_elapsed;

		cout << "Frame Rate: " << (1/ms_elapsed)*1000 << endl;

		if(ms_elapsed < MS_PER_FRAME){
			Int64 us_in_sleep = Int64((MS_PER_FRAME - ms_elapsed)*1000);
			sleep(microseconds(us_in_sleep));
		}

		while(lag >= MS_PER_UPDATE){
			tickPendulums(window);
			tickBlocks(window);

			tickMenu(window);

			if(inState(RESTART))
				return 1;

			if(!Mouse::isButtonPressed(Mouse::Right) && lag < MS_PER_UPDATE*2){
				cleanupPendulums();
				cleanupBlocks();
			}

			if(inState(PLAY))
				tool_radius += (30-tool_radius)*5*INC;
			else
				tool_radius += (10-tool_radius)*5*INC;

			handleEvents(window);
			lag -= MS_PER_UPDATE;
		}		
	}

	return 0;
}

int main(){
	//set random seed
	SYSTEMTIME gtime;
	GetSystemTime(&gtime);
	srand((uint)gtime.wMilliseconds);

	defaultSettings();

	int code = 1;

	while(code){
		code = game();

		stopNoise();

		clearPendulums();
		clearBlocks();

		saveSettings();
	}
	
	return 0;
}