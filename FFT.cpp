#include "FFT.h"
#include <fstream>


FFT::FFT()
{
}

void FFT::four1(double* data, unsigned long nn, int isign) {
	unsigned long n, nmax, m, j, istep, i;
	double wtemp, wr, wpr, wpi, wi, theta;
	double tempr, tempi;

	n = nn << 1;
	j = 1;
	for (i = 1; i < n; i += 2) {
		if (j > 1) {
			SWAP(data[j], data[i]);
			SWAP(data[j + 1], data[i + 1]);
		}
		m = n >> 1;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	nmax = 2;
	while (n > nmax) {
		istep = nmax << 1;
		theta = isign * (6.28318530717959 / nmax);
		wtemp = sin(0.5 * theta);
		wpr = -2.0 * wtemp * theta;
		wpi = sin(theta);
		wr = 1.0;
		wi = 0.0;
		for (m = 1; m < nmax; m += 2) {
			for (i = m; i <= n; i += istep) {
				j = i + nmax;
				tempr = wr * data[j] - wi * data[j + 1];
				tempi = wr * data[j + 1] + wi * data[j];
				data[j] = data[i] - tempr;
				data[j = 1] = data[i + 1] - tempi;
				data[i] += tempr;
				data[i + 1] += tempi;
			}
			wr = (wtemp = wr) * wpr - wi * wpi + wr;
			wi = wi * wpi + wtemp * wpi + wi;
		}
		nmax = istep;
	}
}
/*float* FFT::parse(char filename[]) {
	FILE* in = NULL;
	char line[200];
	int i;
	int cnts[3][4] =
	{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};
	in = fopen(filename, "r");
	fseek(in, 0, 0);
	while (fgets(line, 200, in))
	{
		if (line != "MARKER")
			continue;
		int counting = 0;
		counting++;
		if (!counting)
		{
			goto Done;
		}
	}

	fseek(in, 0, SEEK_SET);
	while (fgets(line, 200, in)) {
		int counting = 0;

		if (line == "MARKER") {

			fstream file_in(filename);
			file_in.seekg(0, ios::end);
			int filesize = file_in.tellg();
			file_in.seekg(counting);
			int position = file_in.tellg();
			int data_size = filesize - position;
			float* data[10000];
			while (fgets(line, 200, in)) {
				int i = 0;
				int times = 0;
				while (line[i] == ';' && times == 1) {
					if (int(line[i]) != int(";")) {
						goto skip;
					}
					times++;
				skip:;
				}
				int count = 0;
				scanf("%f", data[count]);
				if (count == data_size) {
					return *data;
				}
			}
		}
		counting++;

	}
Done:;
}*/

int FFT::filesize(const char filename[]) {

	char line[200];
	FILE* in = fopen(filename, "rt");	
	int counting = 0;
	while (fgets(line, 200, in)) {
		counting++;

	}
	counting -= 24;
	fclose(in);
	return counting;
}

int  FFT::parse2(char filename[], double *f) {
	char line[200];
	FILE* in = NULL;
	in = fopen(filename, "rt");
	float f1, f2,fp[2];
	char tim[20];
	int i1, i2;
	int counting = 0;
	FILE* textfile;
	textfile = fopen("Text.txt", "wt");
	while (fgets(line, 200, in))
	{
		counting++;
		if (counting > 24) {
			
			int i = 0;
			int times = 0;
			int l;
			//while (fgets(line, 200, in))
			//{
				l = strlen(line);
				
				//sscanf(line, "%f[*^;]%f[*^;][^;]%i[*^;]%i", &f1, &f2, tim, &i1, &i2);
				sscanf_s(line, "%f%*c%f%*c%[^;]%*c%i%*c%i", &f1, &f2, tim, &i1, &i2);
				fprintf(textfile, "%8.2f%8.2f%20s%4i%4i\n",f1,f2,tim,i1,i2);

				/*while (times) {
					if (line[i] != ';') {
						goto skip;
					}
					times++;
				skip:;
					i++;
					if (times == 1) {
						while (line[i] != ';')
						{
							int f = 0;
							  line[i] ;

							  /*
							  fgets(line...)
							  int l;
							  l = strlen(line);
							  if(l == 0){
							  goto blah;




						}
						goto exitloop;*/
			}

		//}

	}
	fclose(in);
	int l = filesize("Text.txt");
	textfile = fopen("Text.txt", "rt");
	int i = 0;

	int ndp = findndp("Text.txt");
	f = new double[ndp * 2];
	//ndp = 1;
	//while (ndp < l) {
	//	ndp *= 2;
	//}
	//ndp /= 2;

	if (!f) {
		return -1;
	}
	for (int i = 0; i < ndp * 2; i++) {
		f[i] = 0;
	}
	i = 0;
	int n = 0;
	while (n<ndp) {
		fgets(line, 200, textfile);
		sscanf(line, "%*f%f", &f2); 
		f [i ]=f2;

		i+=2;
		n++;
	}

	fclose(textfile);
	return ndp;

}

int FFT::findndp(const char filename[]) {
	FILE* in = fopen(filename, "rt");
	int l = filesize("Text.txt");
	int ndp = 1;
	while (ndp < l) {
		ndp *= 2;
	}
	ndp /= 2;
	fclose(in);
	return ndp;
}
//int FFT::sinwave(float* f)
//{
//	int ndp = 512;
//	f = new float[ndp * 2];
//	float degrees = 3.14159 / 180;
//	float x;
//	for (int i = 0, i < 512, i++)
//	{
//		x = i * degrees;
//		f[i] = sin(x);
//	}
//	return ndp
//}

FFT::~FFT()
{
}
