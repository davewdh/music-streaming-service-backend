#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>

using namespace std;

class Song {
		
	public:
		//constructor
		Song(const string& artist, const string& title, const string& content);
		
		//getters
		string getArtist() const;
        string getTitle() const;
		
		//functions
		bool matches(const string& artist, const string& title) const;
        void print() const;
        void play() const;
	
	private:
		string artist;
        string title;
        string content;
	
};
#endif