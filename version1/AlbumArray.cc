#include "AlbumArray.h"

//constructor
AlbumArray::AlbumArray(){
	albums = new Album*[MAX_ARRAY];
    numOfAlbums = 0;
}

//destructor
AlbumArray::~AlbumArray(){
	delete [] albums;
}

bool AlbumArray::add(Album* album) {
    if (isFull()) {
        return false;
    }
    for (int i = numOfAlbums; i > 0 ; --i){
        if (album->lessThan(*albums[i-1])){
            //keep making space by copying elements
            //one location to the right
            albums[i]=albums[i-1];
        }else{
            //we have found where s should go
            albums[i] = album;
            ++numOfAlbums;
            return true;
        }
    }
    //we went through every location, and s was less than 
    //all of them. Therefore s goes in location 0
    albums[0] = album;
    ++numOfAlbums;
    return true;
}

//Takes an Album pointer as an argument and adds it adds in order as defined by Album::lessThan(Album&)
bool AlbumArray::get(const string& artist, const string& title, Album** album) const {
    for (int i = 0; i < numOfAlbums; i++) {
        if (albums[i]->matches(artist, title)) {
            *album = albums[i];
            return true;
        }
    }
    return false;
}

//Takes an artist and title as arguments and returns the Album pointer as an output parameter and true as a return value if the album exists and false otherwise.
bool AlbumArray::get(int index, Album** album) const {
    if (index < 0 || index >= numOfAlbums) {
        return false;
    }
     *album = albums[index];
     return true;
}

bool AlbumArray::remove(const string& artist, const string& title, Album** album) {
    int index = 0;
    //we want to find the index of the element to remove
    while (!albums[index]->matches(artist, title) && index < numOfAlbums) {
        index++;
    }
    //if we fall off the end of the array
    if (index == numOfAlbums) {
        return false;
    } 
    *album = albums[index];

    //copy everything after index left one position
    while (index < numOfAlbums - 1){
        albums[index] = albums[index + 1];
        index++;
    }
    numOfAlbums--;
    return true;
}

//Takes an index as an argument and removes and returns the Album as an output parameter and true as a return value if the index is valid and false otherwise.
bool AlbumArray::remove(int index, Album** album) {
    if (get(index, album)) {
        return remove(albums[index]->getArtist(), albums[index]->getTitle(), album);
    }
    return false;
}

int AlbumArray::size() const {
    return numOfAlbums;
}

bool AlbumArray::isFull() const {
    if (numOfAlbums >= MAX_ARRAY) {
        return true;
    }
    return false;
}

void AlbumArray::printShort() const {
    for (int i = 0; i < numOfAlbums; i++) {
        albums[i]->printShort();
    }
}

