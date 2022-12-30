#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "Songify.h"
#include "View.h"
#include "MediaFactory.h"

using namespace std;

class Controller {
		
	public:
				
		void launch();
	
	private:
		void initFromFile();
		void showAllAlbums();
		void showSingleAlbum();
		void getSongByA(); 
		void getSongByC(); 
		void getSongByAandC(); 
		void printCurrentSong(); 
		void playCurrentSong(); 
		View view;
		Songify av;
		Array<Song*> playlist;

	
};
#endif