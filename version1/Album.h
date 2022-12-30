#ifndef ALBUM_H
#define ALBUM_H

#include "SongArray.h"

class Album {
    public:
        //constructor
        Album(const string& artist, const string& title);
        //copy constructor
        Album(const Album&);
        //destructor
        ~Album();

        //getters
		string getArtist() const;
        string getTitle() const;

        //functions
		bool matches(const string& artist, const string& title) const;
        bool lessThan(const Album& alb) const;
        bool addSong(Song* song);
        bool addSong(int index, Song* song);
        bool getSong(const string& title, Song** song) const;
        bool getSong(int index, Song** song) const;
        bool removeSong(const string&, Song** song);
        bool removeSong(int index, Song** song);
        void print() const;
        void printShort() const;

    private:
        string artist;
        string title;
        SongArray* songArray;
};

#endif