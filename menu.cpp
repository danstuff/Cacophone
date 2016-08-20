#include "menu.h"

const float CLICK_DELAY = 0.25;

float click_time = 0;

MenuTitle title;
MenuSettings settings;

MState state;

void createText(Text &text, String str, Font &font, uint size, float x, float y){
	text.setString(str);
	text.setFont(font);
	text.setCharacterSize(size);

	text.setPosition(x, y);

	//center the text
	FloatRect bnds = text.getLocalBounds();
	text.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);
}

bool textClicked(Text &text, RenderWindow &window){
	FloatRect tbnds = text.getGlobalBounds();
	
	float mx = float(Mouse::getPosition(window).x);
	float my = float(Mouse::getPosition(window).y);

	return tbnds.contains(mx, my) && Mouse::isButtonPressed(Mouse::Left);
}

bool inState(MState tstate){
	return state == tstate;
}

void defaultSettings(){
	settings.volume_value = 10;
	settings.noise_value = true;
	settings.width_value = 900;
	settings.height_value = 600;
	settings.aalias_value = true;
}

void loadSettings(){
	ifstream file(SETTINGS_FILE);

	if(!file.is_open()) return;

	string line = "";

	getline(file, line);
	settings.volume_value = stoi(line);

	getline(file, line);
	settings.noise_value = bool(stoi(line));

	getline(file, line);
	settings.width_value = stoi(line);
	getline(file, line);
	settings.height_value = stoi(line);

	getline(file, line);
	settings.aalias_value = bool(stoi(line));

	file.close();

	Listener::setGlobalVolume(settings.volume_value*4);
}

void saveSettings(){
	ofstream file(SETTINGS_FILE);

	file.clear();

	file << to_string(long double(settings.volume_value)) << endl;

	file << to_string(long double(settings.noise_value)) << endl;

	file << to_string(long double(settings.width_value)) << endl;
	file << to_string(long double(settings.height_value)) << endl;

	file << to_string(long double(settings.aalias_value)) << endl;

	file.close();
}

MenuSettings getSettings(){
	return settings;
}

void initMenu(Font &font){
	//main/title menu
	int w = settings.width_value;
	int h = settings.height_value;

	createText(title.title, "CACOPHONE", font, 60, w/2, 34);

	createText(title.play,		"play",		font, 36, w/2, 100);
	createText(title.settings,	"settings", font, 36, w/2, 160);

	createText(title.credits, "a Dan Yost creation, summer 2016", font, 12, w/2, h-16);

	//settings menu
	createText(settings.volume,		 "volume",	font, 36, w/2-80, 108);
	createText(settings.volume_up,	 ">",		font, 36, w/2+130,  108);
	createText(settings.volume_down, "<",		font, 36, w/2+30, 108);
	createText(settings.volume_value_text, "", font, 36, w/2+80, 108);

	createText(settings.noise, "ambient noise",	font, 36, w/2, 162);
	
	createText(settings.width,		"width",	font, 36, w/2-65, 216);
	createText(settings.width_up,	">",		font, 36, w/2+130,  216);
	createText(settings.width_down, "<",		font, 36, w/2+30, 216);
	createText(settings.width_value_text, "", font, 36, w/2+80, 216);
	
	createText(settings.height,		 "height",	font, 36, w/2-70, 270);
	createText(settings.height_up,	 ">",		font, 36, w/2+130,  270);
	createText(settings.height_down, "<",		font, 36, w/2+30, 270);
	createText(settings.height_value_text, "", font, 36, w/2+80, 270);
	
	createText(settings.aalias, "anti-aliasing", font, 36, w/2, 324);

	createText(settings.confirm, "back", font, 36, w/2, 400);

	state = TITLE;
}

void tickMenu(RenderWindow &window){
	if(click_time > 0)
		click_time -= INC;

	//update text
	if(settings.noise_value)
		settings.noise.setString("ambient noise ON");
	else
		settings.noise.setString("ambient noise OFF");

	FloatRect bnds = settings.noise.getLocalBounds();
	settings.noise.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);

	if(settings.aalias_value)
		settings.aalias.setString("anti-aliasing ON");
	else
		settings.aalias.setString("anti-aliasing OFF");

	bnds = settings.aalias.getLocalBounds();
	settings.aalias.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);

	if(state == TITLE && click_time <= 0){
		if(textClicked(title.play, window)){
			state = PLAY;
			click_time = CLICK_DELAY;
		}
		if(textClicked(title.settings, window)){
			state = SETTINGS;
			click_time = CLICK_DELAY;
		}
	}
	else if(state == SETTINGS && click_time <= 0){
		//do settings buttons
		if(textClicked(settings.volume_up, window)&& settings.volume_value < 25){
			settings.volume_value++;
			Listener::setGlobalVolume(settings.volume_value*4);
			click_time = CLICK_DELAY;
		}
		if(textClicked(settings.volume_down, window) && settings.volume_value > 0){
			settings.volume_value--;
			Listener::setGlobalVolume(settings.volume_value*4);
			click_time = CLICK_DELAY;
		}

		if(textClicked(settings.noise, window)){
			settings.noise_value = !settings.noise_value;
			click_time = CLICK_DELAY;
		}

		if(textClicked(settings.width_up, window)){
			settings.width_value += 10;
			click_time = CLICK_DELAY;
		}
		if(textClicked(settings.width_down, window) && settings.width_value > 450){
			settings.width_value -= 10;
			click_time = CLICK_DELAY;
		}

		if(textClicked(settings.height_up, window)){
			settings.height_value += 10;
			click_time = CLICK_DELAY;
		}
		if(textClicked(settings.height_down, window) && settings.height_value > 450){
			settings.height_value -= 10;
			click_time = CLICK_DELAY;
		}

		if(textClicked(settings.aalias, window)){
			settings.aalias_value = !settings.aalias_value;	
			click_time = CLICK_DELAY;
		}
		if(textClicked(settings.confirm, window)){
			state = RESTART;
			click_time = CLICK_DELAY;
		}
	}
}

void drawMenu(RenderWindow &window){
	if(state == TITLE){
		window.draw(title.play);
		window.draw(title.settings);
	}
	else if(state == SETTINGS){
		window.draw(settings.volume);
		window.draw(settings.volume_up);
		window.draw(settings.volume_down);

		settings.volume_value_text.setString(to_string(long double(settings.volume_value)));
		FloatRect bnds = settings.volume_value_text.getLocalBounds();
		settings.volume_value_text.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);
		window.draw(settings.volume_value_text);
		
		window.draw(settings.noise);
		
		window.draw(settings.width);
		window.draw(settings.width_up);
		window.draw(settings.width_down);

		settings.width_value_text.setString(to_string(long double(settings.width_value)));
		bnds = settings.width_value_text.getLocalBounds();
		settings.width_value_text.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);
		window.draw(settings.width_value_text);

		window.draw(settings.height);
		window.draw(settings.height_up);
		window.draw(settings.height_down);

		settings.height_value_text.setString(to_string(long double(settings.height_value)));
		bnds = settings.height_value_text.getLocalBounds();
		settings.height_value_text.setOrigin(bnds.left + bnds.width/2, bnds.top + bnds.height/2);
		window.draw(settings.height_value_text);

		window.draw(settings.aalias);

		window.draw(settings.confirm);
	}
	
	window.draw(title.title);
	window.draw(title.credits);
}
