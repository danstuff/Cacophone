#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <vector>

#include <random>
#include <Windows.h>

using namespace std;
using namespace sf;

typedef unsigned int uint;

const double PI = 3.14159265359;

const double MS_PER_FRAME = 1000/120.0f;

const int MS_PER_UPDATE = 8;
const float INC = 0.1f/MS_PER_UPDATE;

const string FONT_FILE = "comfortaa.ttf";

int random(int max);

#endif