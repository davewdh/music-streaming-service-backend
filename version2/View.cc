
#include "View.h"
#include <limits>

View::View(){
}

void View::mainMenu(int& choice)
{
  int numOptions = 7;

  cout << endl;
  cout << "What would you like to do?"<< endl;
  cout << "  (1) Show all Albums" << endl;
  cout << "  (2) Show all songs in Album" << endl;
  cout << "  (3) Get playlist by artist" << endl;
  cout << "  (4) Get playlist by category" << endl;
  cout << "  (5) Get playlist by artist and category" << endl;
  cout << "  (6) Print current playlist" << endl;
  cout << "  (7) Play current playlist" << endl;
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > numOptions) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::printAllAlbums(const Array<Album*>& albums){
  for (int i = 0; i < albums.getSize(); ++i){
    cout <<i+1<<": " << *albums[i] <<endl;
  } 
}

void View::printAlbum(const Album* album){
    album->print(cout);
}

void View::albumMenu(const Array<Album*>& albums, int& choice){
  int numOptions = albums.getSize();

  printAllAlbums(albums);

  cout << endl;
  cout << "Choose an Album"<< endl;
  cout << "or select (0) to exit" << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > numOptions) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
  --choice;
}

void View::songMenu( Album& al, int& choice){
  int numOptions = al.getSize();
  // print out all songs in playlist
  for (int i = 0; i < al.getSize(); ++i){
      cout <<setw(3)<<i+1<<":"<< al[i];
  } 

  cout << endl;
  cout << "Choose a song to play"<< endl;
  cout << "or select 0 to exit" << endl;
  // cout << "  (2) Play a song from Playlist" << endl;
  // cout << "  (0) Back" << endl<<endl;

  choice = -1;

  while (choice < 0 || choice > al.getSize()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
  if (choice == 0)return;
  al[choice-1]->play(cout);
}

void View::promptArtist(string& artist){
    cout <<"Enter artist: ";
    char str[80];
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(str, 80);
    // cin.clear();
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    artist = str;
    //cin >> artist;
}
		
void View::promptCategory(string& category){
    cout <<"Enter category: ";
    cin >> category;
}

// void View::playsong(Array<song*>& song){
//     for (int i = 0; i < song.getSize(); ++i){
//       cout<<*song[i]<<endl;
//     }
// }

void View::printPlaylist(Array<Song*>& song){
  for (int i = 0; i < song.getSize(); ++i){
      cout<<*song[i]<<endl;
  }
}

void View::playPlaylist(Array<Song*>& song){
  cout <<"Playing playlist size "<<song.getSize()<<endl;;
  for (int i = 0; i < song.getSize(); ++i){
      song[i]->play(cout);
      cout<<endl;
  }
}
