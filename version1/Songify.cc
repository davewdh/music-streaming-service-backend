#include "Songify.h"

//constructor
Songify::Songify() {
    albumArray = new AlbumArray();
}

//destructor
Songify::~Songify() {
    for (int i = 0; i < albumArray->size(); i++) {
        Album* album;
        albumArray->get(i, &album);
        delete album;
    }
    delete albumArray;
}

// If there is room in the AlbumArray create a new Album and add it to the AlbumArray and return true
bool Songify::addAlbum(const string& artist, const string& albumTitle) {
    if (!albumArray->isFull()) {
        if (albumArray->add(new Album(artist, albumTitle))) {
            return true;
        }
    }
    cout << "Fail to add album!" << endl;
    return false;
}

//add the Song to the given Album
bool Songify::addSong(const string& albumTitle, const Song& song) {
    for (int i = 0; i < albumArray->size(); i++) {
        Album* album;
        albumArray->get(i, &album);
        if (album->getTitle() == albumTitle) {
            Song* s = new Song(song);
            if (album->addSong(s)) {
                return true;
            }
        }
    }
    cout << "Fail to add the song!" << endl;
    return false;
}

//If there is an Album that matches the arguments remove it from the AlbumArray and return true. 
bool Songify::removeAlbum(const string& artist, const string& albumTitle) {
    Album* album;
    if (albumArray->remove(artist, albumTitle, &album)) {
        delete album;
        return true;
    }
    cout << "Fail to remove the album!" << endl;
    return false;
}

// If there is a Song with the given title by the given artist in the given Album, remove the Song and return true
bool Songify::removeSong(const string& artist, const string& albumTitle, const string& songTitle) {
    Album* album;
    if (albumArray->get(artist, albumTitle, &album)) {
        Song* song;
        if (album->removeSong(songTitle, &song)) {
            delete song;
            return true;
        }
    }
    cout << "Fail to remove the song!" << endl;
    return false;
}

//Returns an Album pointer and true if the Album exists
bool Songify::downloadAlbum(const string& artist, const string& albumTitle, Album** album) const {
    if (albumArray->get(artist, albumTitle, album)) {
        return true;
    }
    cout << "Fail to download the album!" << endl;
    return false;
}

//Returns a Song pointer and true if the Song exists
bool Songify::streamSong(const string& artist, const string& albumTitle, const string& songTitle, Song** song) const {
    Album* album;
    if (albumArray->get(artist, albumTitle, &album)) {
        if (album->getSong(songTitle, song)) {
            return true;
        }
    }
    cout << "Fail to stream!" << endl;
    return false;
}

//print the short version of all Albums stored in Songify
void Songify::printAlbums() const {
    albumArray->printShort();
}

//print every Album and the associated Songs
void Songify::printSongs() const {
    for (int i = 0; i < albumArray->size(); i++) {
        Album* album;
        albumArray->get(i, &album);
        album->print();
    }
}