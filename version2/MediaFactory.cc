
#include "MediaFactory.h"
#include <fstream>
#include <limits>

// retrieve Song data from a file and use it to create a Song object
bool MediaFactory::createSong(const string& a, const string& t, Song** song){
    ifstream mediaFile;
    mediaFile.open("media/songinfo.txt");
    string empty, title, content, category, artist, video;

    // We are assuming there is at least one record.
    // In general not a great assumption to make, but the input
    // file is fixed so we can get away with it
    while( true ){
        cout<<"Searching for songs artist: "<<endl;
        getline(mediaFile, artist);
        cout<<"artist: "<<artist<<endl;
        getline(mediaFile, title);
        cout<<"title: "<<title<<endl;
        getline(mediaFile, category);
        getline(mediaFile, content);

        // originally some songs were going to have a video element
        // (ascii art) but this part was removed to make a4 simpler
        getline(mediaFile, video);

        // if we found the right Media, make a new object and return
        if (t == title && a == artist){
            *song = new Song(artist, title, category, content);
            mediaFile.close();
            return true;
        }

        // either there is an empty line
        // and another record, or we are done
        if(!getline(mediaFile, empty))break;
    }

    mediaFile.close();
    return false;
}

bool MediaFactory::createAlbum(const string& title, const string& owner, Album** alb){
    if (title.empty() || owner.empty()) {
        return false;
    }
    *alb = new Album(owner, title);
    return true;
}

//return an appropriate Criteria object based on which arguments are not empty strings
bool MediaFactory::createCriteria(const string& artist, const string& category, Criteria** crit){
    if (artist.empty()) {
        if (category.empty()) {
            return false;
        } else {
            *crit = new C_Criteria(category);
            return true;
        }
    } else {
        if (category.empty()) {
            *crit = new A_Criteria(artist);
            return true;
        } else {
            *crit = new AorC_Criteria(artist, category);
            return true;
        }
    }
}