#ifndef CLIENT_H
#define CLIENT_H

#include "Songify.h"

class Client {
    public:
        //constructor
        Client();
        //destructor
        ~Client();

        //functions
        bool download(const Songify* sfy, const string& artist, const string& albumTitle) const;
        bool stream(const Songify* sfy, const string& artist, const string& albumTitle, const string& songTitle) const;
        bool playLocal(const string& artist, const string& albumTitle, const string& songTitle) const;

        void printAlbums() const;
        void printSongs() const;


    private:
        AlbumArray* albumArray;
};

#endif