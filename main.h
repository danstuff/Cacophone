#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <vector>

#include <random>
#include <Windows.h>

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

using namespace std;
using namespace sf;

typedef unsigned int uint;

const uint WIDTH = 640;
const uint HEIGHT = 480;

const float PI = 3.14159265359;

const float SHAPE_RADIUS = 40;

int random(int max);

#endif