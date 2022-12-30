#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include "Album.h"

using namespace std;

class View {
		
	public:
		View();
    	void mainMenu(int&);
		void printAllAlbums(const Array<Album*>& albums);
		void albumMenu( const Array<Album*>& albums, int& choice);
		void printAlbum(const Album*);
		void songMenu(Album&, int& choice);
        void promptArtist(string& artist);
		void promptCategory(string& category);
		void printPlaylist(Array<Song*>&);
		void playPlaylist(Array<Song*>&);

	private:
		
	
};
#endif