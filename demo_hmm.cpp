// demo_hmm.cpp : Defines the entry point for the console application.
//

// #include "stdafx.h"
#include "hmm.h"
#include <iostream>
using namespace std;

int main(int argc, const char* argv[])
{
	char** name = new char*[3] {"tronHMM", "vayrlrHMM", "xoan3vongHMM"};
	HMM* hmm[3];
	double* threshold = new double[3] { -90, -90, -63 };

	for (int k = 0; k < 3; k++){

		cout << "\n============================================================\n";
		cout << name[k] << "\n\n";

		hmm[k] = new HMM(9, 8, 1234);

		//training
		char* training_file = new char[50];

		sprintf(training_file, "data/training/%s.txt", name[k]);
		hmm[k]->batch_train(training_file, 0.005);

		sprintf(training_file, "data/training/%s.hmm", name[k]);
		hmm[k]->dump_model(training_file);
	}

	//test
	for (int j = 1; j < 30; j++){
		char* filename = new char[30];
		sprintf(filename, "data/test/test%d.txt", j);
		
		FILE* f;
		f = fopen(filename, "r");
		char c;
		int* test = new int[200];
		int i = 0;
		while ((fscanf(f, "%c", &c) != EOF)) {
			if (c != ' ') {
				test[i++] = c - 48;
			}
		}

		fclose(f);
		double result, max;
		int index = 0;
		max = -9999;
		for (int k = 0; k < 3; k++) {
			result = hmm[k]->test_one(test, i - 1);
			if (result > max) {
				max = result;
				index = k;
			}
		}

		cout << "\nTest [ " << j << " ]\t" << max << '\t' << name[index];
	}

	getchar();

	return 0;
}