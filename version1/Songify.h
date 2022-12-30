#ifndef SONGIFY_H
#define SONGIFY_H

#include "AlbumArray.h"

class Songify {
    public:
        //constructor
        Songify();
        //destructor
        ~Songify();

        //functions
        bool addAlbum(const string& artist, const string& albumTitle);
        bool addSong(const string& albumTitle, const Song& song);
        bool removeAlbum(const string& artist, const string& albumTitle);
        bool removeSong(const string& artist, const string& albumTitle, const string& songTitle);
        bool downloadAlbum(const string& artist, const string& albumTitle, Album** album) const;
        bool streamSong(const string& artist, const string& albumTitle, const string& songTitle, Song** song) const;

        void printAlbums() const;
        void printSongs() const;

    private:
        AlbumArray* albumArray;
};
#endif