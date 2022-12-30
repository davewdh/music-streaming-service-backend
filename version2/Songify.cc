#include "Songify.h"

//constructor
Songify::Songify() {
    
}

//destructor
Songify::~Songify() {
    for (int i = 0; i < albumArray.getSize(); ++i) {
        delete albumArray[i];
    }

}

// If there is room in the AlbumArray create a new Album and add it to the AlbumArray and return true
bool Songify::addAlbum(const string& artist, const string& albumTitle) {
    if (albumArray.isFull()) {
        return false;
    }
    Album* album;
    if (mediafactory.createAlbum(albumTitle, artist, &album)) {
        albumArray+=album;
        return true;
    }
    return false;
    
}

//If there is an Album that matches the arguments remove it from the AlbumArray and return true. 
bool Songify::removeAlbum(const string& artist, const string& albumTitle) {
    for (int i = 0; i < albumArray.getSize(); ++i) {
        if (albumArray[i]->matches(artist, albumTitle)) {
            albumArray-=albumArray[i];
            delete albumArray[i];
            return true;
        }
    }
    return false;
}

//add the Song to the given Album
bool Songify::addSong (const string& artist , const string& songTitle , const string& albumTitle) {
    for (int i = 0; i < albumArray.getSize(); ++i) {
        if (albumArray[i]->matches(artist, albumTitle)) {
            Song* song;
            if (mediafactory.createSong(artist, songTitle, &song)) {
                albumArray[i]->addSong(song);
                return true;
            }
        }
    }
    return false;
}

// If there is a Song with the given title by the given artist in the given Album, remove the Song and return true
bool Songify::removeSong(const string& artist, const string& songTitle, const string& albumTitle) {
    for (int i = 0; i < albumArray.getSize(); ++i) {
        if (albumArray[i]->matches(artist, albumTitle)) {
            Song* song;
            if (albumArray[i]->removeSong(songTitle, &song)) {
                delete song;
                return true;
            }  
        }
    }
    return false;
}

// return the Album at the given index, or return false if the index is out of bounds.
bool Songify::getAlbum(int index, Album** album) const {
    if (index < 0 || index >= albumArray.getSize()) {
        return false;
    }
    *album = albumArray[index];
    return true;
}


//return a constant reference to the Array of Albums
const Array<Album*>& Songify::getAlbums() const {
    return albumArray;
}

//populate playlist with every Song in Songify that matches the given artist and category as defined by the Criteria class and its derived classes
bool Songify::getPlaylist(const string& artist , const string& category,  Array<Song*>& playlist) {
    Criteria* criteria;
    if (mediafactory.createCriteria(artist, category, &criteria)) {
        for (int i = 0; i < albumArray.getSize(); ++i) {
            for (int j = 0; j < albumArray[i]->getSize(); ++j) {
                if (criteria->matches(*(*albumArray[i])[j])) {
                    playlist+=(*albumArray[i])[j];
                }
            }
        }
        delete criteria;
        return true;
    }
    return false;
}

