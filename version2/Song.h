#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>

using namespace std;

class Song {
	friend ostream& operator<<(ostream&, const Song& song);
	
	public:
		//constructor
		Song(const string& artist, const string& title, const string& category, const string& content);
		
		//getters
		string getArtist() const;
        string getTitle() const;
		string getCategory() const;
		
		//functions
		bool matches(const string& artist, const string& title) const;
        void print(ostream& ost) const;
        void play(ostream& ost) const;
	
	private:
		string artist;
        string title;
        string content;
		string category;
	
};
#endif