#ifndef SONGARRAY_H
#define SONGARRAY_H

#include "Song.h"
#include "defs.h"

class SongArray {
    public:
        //constructor
        SongArray();
        //destructor
        ~SongArray();

        //functions
        bool add(Song* song);
        bool add(int index, Song* song);
        bool get(const string&, const string& title, Song** song) const;
        bool get(int index, Song** song) const;
        bool remove(const string& artist, const string& title, Song** song);
        bool remove(int index, Song** song);
        int size() const;
        bool isFull() const;
        void print() const;

    private:
        Song** songs;
        int numOfSongs;
};

#endif