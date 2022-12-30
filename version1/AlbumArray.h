#ifndef ALBUMARRAY_H
#define ALBUMARRAY_H

#include "Album.h"
#include "defs.h"

class AlbumArray {
    public:
        //constructor
        AlbumArray();
        //copy constructor
        ~AlbumArray();

        //functions
        bool add(Album* album);
        bool get(const string& artist, const string& title, Album** album) const;
        bool get(int index, Album** album) const;
        bool remove(const string& artist, const string& title, Album** album);
        bool remove(int index, Album** album);
        int size() const;
        bool isFull() const;
        void printShort() const;

    private:
        Album** albums;
        int numOfAlbums;
};
#endif