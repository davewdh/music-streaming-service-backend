#include "Song.h"

//constructor
Song::Song(const string& artist, const string& title, const string& category, const string& content) {
	this->artist = artist;
    this->title = title;
    this->category = category;
    this->content = content;
}

//getters
string Song::getArtist() const {
    return this->artist;
}

string Song::getTitle() const {
    return this->title;
}

string Song::getCategory() const {
    return this->category;
}

//returns true if the given artist and title are equal to the artist and title member variables of this Song
bool Song::matches(const string& artist, const string& title) const {
    return ((this->artist == artist) && (this->title == title));
}

//print out the song metadata (not including the content).
void Song::print(ostream& ost) const {
    ost << "Song: " << this->title << ". Artist: " << this->artist << ". Category: "<< this->category << endl;
}

void Song::play(ostream& ost) const {
    print(ost);
    ost << "Content: " << this->content << endl;
}

ostream& operator<<(ostream& ost, const Song& song){
    song.print(ost);
    return ost;
}