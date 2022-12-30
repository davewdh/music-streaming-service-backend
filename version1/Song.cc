#include "Song.h"

//constructor
Song::Song(const string& artist, const string& title, const string& content) {
	this->artist = artist;
    this->title = title;
    this->content = content;
}

//getters
string Song::getArtist() const {
    return this->artist;
}

string Song::getTitle() const {
    return this->title;
}

//returns true if the given artist and title are equal to the artist and title member variables of this Song
bool Song::matches(const string& artist, const string& title) const {
    return ((this->artist == artist) && (this->title == title));
}

//print out the song metadata (not including the content).
void Song::print() const {
    cout << "Song: " << this->title << " by " << this->artist << endl;
}

void Song::play() const {
    print();
    cout << "Content: " << this->content << endl;
}