#include "block.h"
#include "pendulum.h"
#include "shape.h"

const float ISIZE = 30;
const float OUTER = sqrt(2.0f)*ISIZE;

vector<Block> blocks;

void createBlock(float x, float y){
	Block block;

	block.x = x;
	block.y = y;

	block.pulse = 0;

	block.erase = false;

	blocks.push_back(block);
}

void tickBlocks(RenderWindow &window){
	int mx = Mouse::getPosition(window).x;
	int my = Mouse::getPosition(window).y;

	vector<Pendulum> &ps = getPendulums();

	for(uint i = 0; i < blocks.size(); i++){
		if(blocks[i].pulse != 0)
			blocks[i].pulse -= blocks[i].pulse*INC;

		//if pendulum collided with block, play note
		//TODO fix ball-box collisions***********
		for(uint j = 0; j < ps.size() && blocks[i].pulse < 0.1f; j++){
			float bx = blocks[i].x;
			float by = blocks[i].y;

			float px = ps[j].x;
			float py = ps[j].y;

			float dist = sqrt((px-bx)*(px-bx) + (py-by)*(py-by));

			if(dist <= OUTER){
				float mx = (px + bx)/2.0f;
				float my = (py + by)/2.0f;

				float bleft		= bx - ISIZE;
				float bright	= bx + ISIZE;
				float btop		= by - ISIZE;
				float bbottom	= by + ISIZE;

				if(dist <= ISIZE ||
					(mx >= bleft && mx <= bright &&
					my >= btop && my <= bbottom)){
						playWave(ps[j].ss);

						ps[j].pulse = 1;
						blocks[i].pulse = 1;

						j = ps.size();
				}
			}
		}
	}

	//if block collided with mouse cursor while right clicking, delete it
	if(Mouse::isButtonPressed(Mouse::Right)){
		for(uint i = 0; i < blocks.size(); i++){
			if(mx >= blocks[i].x - ISIZE && 
				mx <= blocks[i].x + ISIZE &&
				my >= blocks[i].y - ISIZE &&
				my <= blocks[i].y + ISIZE){
					blocks[i].erase = true;
			}
		}
	}
}
void drawBlocks(RenderWindow &window){
	for(uint i = 0; i < blocks.size(); i++){
		if(!blocks[i].erase){
			uint cfac = uint(blocks[i].pulse*150);
			float sfac = blocks[i].pulse*10;

			drawShape(SQUARE, window, Color(40+cfac, 100+cfac, 100+cfac, 240), ISIZE+sfac,
				blocks[i].x, blocks[i].y, 0);
		}
	}
}

void cleanupBlocks(){
	//for performance, must be called multiple times to erase all flagged
	for(uint i = 0; i < blocks.size(); i++){
		if(blocks[i].erase){
			iter_swap(blocks.begin() + i, blocks.end());
			blocks.erase(blocks.end());
			return;
		}
	}
}

void clearBlocks(){
	blocks.clear();
}