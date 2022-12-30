#include "Album.h"

//constructor
Album::Album(const string& artist, const string& title) {
	this->artist = artist;
    this->title = title;
    songArray = new SongArray();
}

//copy constructor
Album::Album(const Album& alb) {
    this->artist = alb.artist;
    this->title = alb.title;
    songArray = new SongArray();
    Song* song;
    for (int i = 0; i < alb.songArray->size(); i++) {
        alb.songArray->get(i, &song);
        songArray->add(new Song(*song));
    }
}

//destructor
Album::~Album() {
    for (int i = 0; i < songArray->size(); i++) {
        Song* song;
        songArray->get(i, &song);
        delete song;
    }
    delete songArray;
}

//getters
string Album::getArtist() const {
    return this->artist;
}

string Album::getTitle() const {
    return this->title;
}

//Takes an artist and title as arguments (in that order) and returns true if the Album artist and title match the parameters and false otherwise
bool Album::matches(const string& artist, const string& title) const {
    return ((this->artist == artist) && (this->title == title));
}

//Takes an Album& alb as an argument and returns true if this Album is less than alb in lexicographical order by artist and title, and false otherwise. 
bool Album::lessThan(const Album& alb) const {
    if (this->artist < alb.artist) {
        return true;
    } else if (this->artist > alb.artist) {
        return false;
    } else {
        return this->title < alb.title;
    }
}

//Takes a Song pointer as an argument. If the Song artist matches the Album artist, attempt to add it to the SongArray.
bool Album::addSong(Song* song) {
    if (this->artist == song->getArtist()) {
        return songArray->add(song);
    }
    return false;
}

//Takes an index and a Song pointer as arguments. If the Song artist matches the Album artist, attempt to add the Song to the SongArray at the index indicated
bool Album::addSong(int index, Song* song) {
    if (this->artist == song->getArtist()) {
        return songArray->add(index, song);
    }
    return false;
}

//Takes a title as an argument and returns the Song as an output parameter and true as a return value if the song exists and false otherwise.
bool Album::getSong(const string& title, Song** song) const {
    return songArray->get(getArtist(), title, song);
}

//Takes an index as an argument and returns the Song as an output parameter and true as a return value if the index is valid and false otherwise.
bool Album::getSong(int index, Song** song) const {
    return songArray->get(index, song);
}

//Takes a title as an argument, removes and returns the Song as an output parameter and true as a return value if the song exists and false otherwise.
bool Album::removeSong(const string& title, Song** song) {
    if (songArray->remove(getArtist(), title, song)) {
        return true;
    }
    return false;
}

//Takes an index as an argument and removes and returns the Song as an output parameter and true as a return value if the index is valid and false otherwise
bool Album::removeSong(int index, Song** song) {
    if (songArray->remove(index, song)) {
        return true;
    }
    return false;
}

//Prints out all the metadata for this Album along with the songs.
void Album::print() const {
    printShort();
    songArray->print();
}

//Prints the metadata for this Album, but not the songs.
void Album::printShort() const {
    cout << "Album: " << this->title << " by " << this->artist << endl;
}