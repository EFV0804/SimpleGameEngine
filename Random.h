#pragma once
#include<random>
#include"Vector2.h"

class Random
{
public:
	static void init();

	//Seed the generator with specified int
	static void seed(unsigned int seed);

	//Get float between 0.0f and 1.0f
	static float getFloat();

	//get a float from a specified range
	static float getFloatRange(float min, float max);

	//Get an int from specidied range
	static int getIntRange(int min, int max);

	//get a random vector given the nim/max bounds
	static Vector2 getVector(const Vector2& min, const Vector2& max);

private:
	static std::mt19937 sGenerator;
};