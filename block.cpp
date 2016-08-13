#include "block.h"
#include "shape.h"

const float BLOCK_SIZE = 30;

const float BLOCK_INNER = BLOCK_SIZE;
const float BLOCK_OUTER = sqrt(2.0f)*BLOCK_INNER;

vector<Block> blocks;

void createBlock(float x, float y){
	Block block;

	block.x = x;
	block.y = y;
	
	block.erase = false;

	blocks.push_back(block);
}

void tickBlocks(RenderWindow &window){
	int mx = Mouse::getPosition(window).x;
	int my = Mouse::getPosition(window).y;

	//TODO check if pendulums collided with blocks, play their notes

	//if block collided with mouse cursor while right clicking, delete it
	if(Mouse::isButtonPressed(Mouse::Right)){
		for(uint i = 0; i < blocks.size(); i++){
			if(mx >= blocks[i].x - BLOCK_SIZE && 
				mx <= blocks[i].x + BLOCK_SIZE &&
				my >= blocks[i].y - BLOCK_SIZE &&
				my <= blocks[i].y + BLOCK_SIZE){
					blocks[i].erase = true;
			}
		}
	}
}
void drawBlocks(RenderWindow &window){
	for(uint i = 0; i < blocks.size(); i++){

		if(!blocks[i].erase){
			drawShape(SQUARE, window, Color(100, 100, 100), BLOCK_SIZE,
				blocks[i].x, blocks[i].y, 0);
		}
	}
}

void cleanupBlocks(){
	//for performance, must be called multiple times to erase all flagged
	for(uint i = 0; i < blocks.size(); i++){
		if(blocks[i].erase){
			blocks.erase(blocks.begin() + i);
			return;
		}
	}
}

void clearBlocks(){
	blocks.clear();
}