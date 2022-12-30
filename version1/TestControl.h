#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include "Songify.h"
#include <random>
#include <unordered_set>

using namespace std;

class TestControl {
		
	public:
		void launch();
	
	private:
		int  songTest();
		int  albumTest();
		int  albumArrayTest();
		int  songifyTest();
		int  clientTest();

		//initialize with some Songs and Albums
		void initialize(Songify*);

		// generate a set (no duplicates) of "count" random integers
		// from 0 to "range"
		void ran(unordered_set<int>& s, int count, int range);
		// generate a random integer in the given range
		int ran(int range_from, int range_to);

		// Some initial data
		const static string artists[3];
		const static string albums[3][2];
		const static string songTitles[3][2][5];
		const static string songContent[3][2][5];
	
};
#endif