#pragma once
#define SWAP(a, b) tempr = (a); (a)=(b); (b)=tempr;
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

class FFT
{
public:
	FFT();
	void four1(double* data, unsigned  long nn, int isign);
	/*float* parse(char filename[]);*/
	int filesize(const char filename[]);
	int parse2(char filename[], double* f);
	int findndp(const char filename[]);
	//int sinwave(float* f);
	~FFT();
};

