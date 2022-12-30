#include "Client.h"

//constructor
Client::Client() {
    albumArray = new AlbumArray();
}

//destructor
Client::~Client() {
    for (int i = 0; i < albumArray->size(); i++) {
        Album* album;
        albumArray->get(i, &album);
        delete album;
    }
    delete albumArray;
}

//make a copy of the Album and add it to the AlbumArray and return true. If unsuccessful return false
bool Client::download(const Songify* sfy, const string& artist, const string& albumTitle) const {
    Album* album;
    if (sfy->downloadAlbum(artist, albumTitle, &album)) {
        return albumArray->add(new Album(*album));
    }
    return false;
}

//play the Song and return true. If unsuccessful return false.
bool Client::stream(const Songify* sfy, const string& artist, const string& albumTitle, const string& songTitle) const {
    Song* song;
    if (sfy->streamSong(artist, albumTitle, songTitle, &song)) {
        song->play();
        return true;
    }
    return false;
}

// Attempt to retrieve the Song from the AlbumArray. If successful, play the Song and return true.
bool Client::playLocal(const string& artist, const string& albumTitle, const string& songTitle) const {
    Album* album;
    if (albumArray->get(artist, albumTitle, &album)) {
        Song* song;
        if (album->getSong(songTitle, &song)) {
            song->play();
            return true;
        }
    }
    return false;
}

void Client::printAlbums() const {
    albumArray->printShort();
}

void Client::printSongs() const {
    for (int i = 0; i < albumArray->size(); i++) {
        Album* album;
        albumArray->get(i, &album);
        album->print();
    }
}