#include "Album.h"

//constructor
Album::Album(const string& artist, const string& title) {
	this->artist = artist;
    this->title = title;
}

//destructor
Album::~Album() {
    for (int i = 0; i < songArray.getSize(); i++) {
        delete songArray[i];
    }
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

//add the Song* to the back of Array
bool Album::addSong(Song* song) {
    if (songArray.isFull()) {
        return false;
    }
    songArray+=song;
    return true;
}

//Takes a title as an argument and returns the Song as an output parameter and true as a return value if the song exists and false otherwise.
bool Album::getSong(const string& title, Song** song) const {
    for (int i = 0; i < getSize(); ++i) {
        if (songArray[i]->matches(this->artist, title)) {
            *song = songArray[i];
            return true;
        }
    }
    *song = NULL;
    return false;
}

Song* Album::operator[](int index) {
	if (index < 0 || index >= getSize()) {
		cerr<<"Array index out of bounds"<<endl;
		exit(1);
	}
	return songArray[index];
}

Song* Album::operator[](int index) const{
	if (index < 0 || index >= getSize()) {
		cerr<<"Array index out of bounds"<<endl;
		exit(1);
	}
	return songArray[index];
}

//Takes a title as an argument, removes and returns the Song as an output parameter and true as a return value if the song exists and false otherwise.
bool Album::removeSong(const string& title, Song** song) {
    for (int i = 0; i < getSize(); ++i) {
        if (songArray[i]->matches(this->artist, title)) {
            *song = songArray[i];
            songArray-=songArray[i];
            return true;
        }
    }
    *song = NULL;
    return false;
}

//Takes an index as an argument and removes and returns the Song as an output parameter and true as a return value if the index is valid and false otherwise
bool Album::removeSong(int index, Song** song) {
    if (index < 0 || index >= getSize()) {
		*song = NULL;
        return false;
	}
	*song = songArray[index];
    songArray-=songArray[index];
    return true;
}

int Album::getSize() const {
    return songArray.getSize();
}

//Prints out all the metadata for this Album along with the songs.
void Album::print(ostream& ost) const {
    printShort(ost);
    for (int i = 0; i < songArray.getSize(); ++i) {
        songArray[i]->print(ost);
    }
    
}

//Prints the metadata for this Album, but not the songs.
void Album::printShort(ostream& ost) const {
    ost << "Album: " << this->title << ". Artist: " << this->artist << endl;
}

ostream& operator<<(ostream& ost, const Album& alb) {
	alb.printShort(ost);
	return ost;
}