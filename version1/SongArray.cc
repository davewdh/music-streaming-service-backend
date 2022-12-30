#include "SongArray.h"

//constructor
SongArray::SongArray(){
	songs = new Song*[MAX_ARRAY];
    numOfSongs = 0;
}

//destructor
SongArray::~SongArray(){
	delete [] songs;
}

//adds it to the back of the array
bool SongArray::add(Song* song) {
    if (isFull()) {
        return false;
    }
    songs[numOfSongs] = song;
    numOfSongs++;
    return true;
}

// add the Song to the array at the index indicated
bool SongArray::add(int index, Song* song) {
    if (isFull()) {
        return false;
    }
    if (index < 0 || index > numOfSongs) {
        return false;
    }
    for (int i = numOfSongs; i > index; i--) {
        songs[i] = songs[i-1];
    }
    songs[index] = song;
    numOfSongs++;
    return true;
}

//assigns the pointer to the Song that matches these arguments to the output parameter
bool SongArray::get(const string& artist, const string& title, Song** song) const {
    for (int i = 0; i < numOfSongs; i++) {
        if (songs[i]->matches(artist, title)) {
            *song = songs[i];
            return true;
        }
    }
    return false;
}


//takes an index as an argument and assigns the Song pointer to the output parameter.
bool SongArray::get(int index, Song** song) const {
    if (index < 0 || index >= numOfSongs) {
        return false;
    }
     *song = songs[index];
     return true;
}

bool SongArray::remove(const string& artist, const string& title, Song** song) {
    int index = 0;
    //we want to find the index of the element to remove
    while (!songs[index]->matches(artist, title) && index < numOfSongs) {
        index++;
    }
    //if we fall off the end of the array
    if (index == numOfSongs) {
        return false;
    } 
    *song = songs[index];

    //copy everything after index left one position
    while (index < numOfSongs - 1){
        songs[index] = songs[index + 1];
        index++;
    }
    numOfSongs--;
    return true;
}

//If the index is valid assign the Song pointer to the output parameter and return true, 
bool SongArray::remove(int index, Song** song) {
    if (get(index, song)) {
        return remove(songs[index]->getArtist(), songs[index]->getTitle(), song);
    }
    return false;
}

int SongArray::size() const {
    return numOfSongs;
}

bool SongArray::isFull() const {
    if (numOfSongs >= MAX_ARRAY) {
        return true;
    }
    return false;
}

//prints all the Songs in the array.
void SongArray::print() const {
    for (int i = 0; i < numOfSongs; i++) {
        songs[i]->print();
    }
}

