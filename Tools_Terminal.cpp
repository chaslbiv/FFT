// Tools_Terminal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "FFT.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	
	cout << "What would you like to do:" << endl;
	cout << "[1] Fourier Transform\n[e] exit\n";

	char input;
	FILE* in;
	_complex c;
	double* data = NULL;
	cin >> input;
	if (input == '1') {
		FFT transform;
		cout << "Input the file that you would like to be transformed:" << endl;
		char input2[1000];
		cin >> input2;
		char new_file[200];
		int ndp = transform.findndp("Text.txt");
		/*data = new double[ndp * 2];*/
		transform.parse2(input2, data);
		transform.four1(data-1, ndp, 1);
		fstream trunc;
		trunc.open("FFT.txt", std::fstream::trunc);
		trunc.close();
		in = fopen("FFT.txt", "wt");
		int x = 1;
		double d;
		for (int j = 0; j <ndp*2; j+=1) {
			c.x = data[j];
			c.y = data[j + 1];
			d = _cabs(c);
			fprintf(in, "%12i%12.4f\n", x, d);
				x++;
		}
		fclose(in);
		//E:\Mobbs_Data\breath_analysis.txt
		return 0;
	}
	else if (input == 'e') {
		system("exit");
		return 0;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
