
#include "Controller.h"
#include "View.h"
#include <fstream>
#include <vector>

void Controller::launch(){
    initFromFile();
    int choice = -1;

    // This is what the View shows:
    // cout << "What would you like to do?"<< endl;
    // cout << "  (1) Show all Albums" << endl;
    // cout << "  (2) Show single Album" << endl;
    // cout << "  (3) Get playlist by artist" << endl;
    // cout << "  (4) Get playlist by category" << endl;
    // cout << "  (5) Get playlist by artist and category" << endl;
    // cout << "  (6) Print current Song list" << endl;
    // cout << "  (7) Play current Song list" << endl;
    // cout << "  (0) Exit" << endl<<endl;

    while (true){
        choice = -1;
        view.mainMenu(choice);
        if (choice == 0)break;
        switch (choice)
        {
            case 1: showAllAlbums(); break;
            case 2: showSingleAlbum(); break;
            case 3: getSongByA(); break;
            case 4: getSongByC(); break;
            case 5: getSongByAandC(); break;
            case 6: printCurrentSong(); break;
            case 7: playCurrentSong(); break;
        }
        
    }

    cout << "Good-bye!"<<endl;
}


/*
Normally something like this would be in your SongFactory class, 
so that all this complexity does not have to be hard-coded in
your program. We are keeping it simple, and I wrote it for you. 
*/
void Controller::initFromFile(){
    ifstream songFile;
    songFile.open("media/media.txt");
    string album, temp;
    string title, artist;
    int numSongs = 0;
    Song* song;
    while( true ){
        if(!getline(songFile, album))break;
        getline(songFile, artist);

        getline(songFile, temp);
        numSongs = stoi(temp);
        //this one should be an integer representing the 
        //number of Songs on this Album
        av.addAlbum(artist, album);
        for (int i = 0; i < numSongs; ++i){
            getline(songFile, artist);
            getline(songFile, title);
            av.addSong(artist, title, album);
        }
    }

    songFile.close();

}

void Controller::showAllAlbums(){
    cout<<"Showing all Albums: "<<endl;
    view.printAllAlbums(av.getAlbums());
}

void Controller::showSingleAlbum(){
    int choice = - 1;
    view.albumMenu(av.getAlbums(), choice);
    Album* album;
    av.getAlbum(choice, &album);
    view.printAlbum(album);
}

void Controller::getSongByA(){
    string artist;
    view.promptArtist(artist);
    playlist.clear();
    av.getPlaylist(artist, "", playlist);
} 

void Controller::getSongByC(){
    string cat;
    view.promptCategory(cat);
    playlist.clear();
    av.getPlaylist("", cat, playlist);
} 

void Controller::getSongByAandC(){
    string artist, cat;
    view.promptArtist(artist);
    view.promptCategory(cat);
    playlist.clear();
    av.getPlaylist(artist, cat, playlist);
}

void Controller::printCurrentSong(){
    cout<<"Playlist size: "<<playlist.getSize()<<endl;
    view.printPlaylist(playlist);
} 

void Controller::playCurrentSong(){
    view.playPlaylist(playlist);
}
