#ifndef ALBUM_H
#define ALBUM_H

#include "Array.h"
#include "Song.h"

class Album {
    public:
        friend ostream& operator<<(ostream&, const Album&);

        //constructor
        Album(const string& artist, const string& title);
        //destructor
        ~Album();

        //getters
		string getArtist() const;
        string getTitle() const;

        //functions
		bool matches(const string& artist, const string& title) const;
        bool lessThan(const Album& alb) const;
        bool addSong(Song* song);
        Song* operator[](int index);
		Song* operator[](int index) const;
        bool getSong(const string& title, Song** song) const;
        bool removeSong(const string&, Song** song);
        bool removeSong(int index, Song** song);
        int getSize() const;
        void print(ostream& ost) const;
        void printShort(ostream& ost) const;

    private:
        string artist;
        string title;
        Array<Song*> songArray;
};

#endif