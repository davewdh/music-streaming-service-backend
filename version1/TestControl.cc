
#include "TestControl.h"
#include "TestView.h"
#include "Client.h"

using namespace std;



void TestControl::launch(){
    //make a view, get input, launch the appropriate test
    TestView view;
    int choice = 5;

    while (choice!=0){
        view.showMenu(choice);
        switch(choice){
            case 1: songTest(); break;
            case 2: albumTest(); break;
            case 3: albumArrayTest(); break;
            case 4: songifyTest(); break;
            case 5: clientTest(); break;
        }
    }
}


int TestControl::songTest(){
    Song* songs[12];
    
    unordered_set<int> rartist;  //random artists
    unordered_set<int> rsong;    //random songs
    unordered_set<int> ralbum;   //random albums

    unordered_set<int>::iterator iart, isong, ialb; //iterators for the sets

    int count = 0;

    ran(rartist, 2, 3); //choose 2 out of 3 artists

    for (iart = rartist.begin(); iart != rartist.end(); ++ iart){
        rsong.clear();
        ralbum.clear();
        ran(ralbum, 1, 2); // choose 1 out of 2 albums
        ran(rsong, 2, 5); // choose 2 out of 5 songs
        
        for (isong = rsong.begin(); isong != rsong.end(); ++isong){
            for (ialb = ralbum.begin(); ialb != ralbum.end(); ++ialb){
                songs[count++] = new Song(artists[*iart], songTitles[*iart][*(ialb)][*isong], /*albums[*iart][*ialb],*/ songContent[*iart][*(ialb)][*isong]);
                cout<<endl<<"Adding "<<songTitles[*iart][*(ialb)][*isong]<<" by "<< artists[*iart] <<endl;
            }
        }
    }
    
    cout<<endl<<"Playing Songs:"<<endl<<endl;
    for (int i = 0; i < count; ++i){
        songs[i]->play(); cout<<endl;
        delete songs[i];
    }

    cout <<"**MANUAL MARK** If all songs are printed (should be 4), 2 marks. If there was some mistake, 1 mark, for major mistakes, 0 marks"<<endl;
    return 0;
}
		
int TestControl::albumTest(){
    unordered_set<int> rartist;  //random artist
    unordered_set<int> rsong;    //random song
    Album* albs[2];
    unordered_set<int>::iterator iart, isong; //iterators for the sets

    
    ran(rartist, 2, 3); //choose 2 out of 3 artists 
    ran(rsong, 2, 5); // choose 2 out of 5 songs
    iart = rartist.begin();
    for (int i = 0; i < 2; ++i){
        int alb = ran(0,1);  // choose a random album
        cout<<endl<<"Adding Album  "<<albums[*iart][alb]<<" by "<<artists[*iart]<<endl;
        albs[i] = new Album(artists[*iart], albums[*iart][alb]);
        for (isong = rsong.begin(); isong != rsong.end(); ++isong){ 
                cout<<"Adding Song to Album: "<<songTitles[*iart][alb][*isong]<<" by "<<artists[*iart]<<endl;
                albs[i]->addSong(new Song(artists[*iart], songTitles[*iart][alb][*isong], /*albums[*iart][alb],*/ songContent[*iart][alb][*isong]));
        }
        ++iart;
    }

    cout<<endl<<"Printing albums with songs (should be 2 albums and 2 songs each album):"<<endl;
    for (int i = 0; i < 2; ++i){
        albs[i]->print();
    }

    cout<<endl<<"**MANUAL MARK** If all songs print, 2 marks"<<endl;

    Song* song = new Song("The Backstreet Boys", "I Want It That Way", songContent[0][0][0] );

    cout<<endl<<"Attempting to add songs with wrong artist to albums:"<<endl;
    song->print();
    for (int i = 0; i < 2; ++i){
        albs[i]->addSong(song);
    }

    cout<<endl<<"Printing albums with songs:"<<endl;
    for (int i = 0; i < 2; ++i){
        albs[i]->print();
    }

    cout<<endl<<"**MANUAL MARK** If there is no Backstreet Boys, 1 mark, otherwise 0"<<endl;

    for (int i = 0; i < 2; ++i){
        delete albs[i];
    }
    delete song;

    
    cout<<"Testing add Song at index"<<endl;
    Album* album = new Album(artists[0], albums[0][0]);
    Song* songs[3];
    for (int i = 0; i < 3; ++i){
        songs[i] = new Song(artists[0], songTitles[0][0][i], songContent[0][0][i]);
    }
    cout<<endl<<"Adding song at bad index"<<endl;
    album->addSong(2, songs[0]);
    album->print();
    cout<<"**MANUAL MARK** If song "<< songTitles[0][0][0] <<" did not print, 1 mark"<<endl;
    cout<<endl<<"Adding songs at good indices"<<endl;
    album->addSong(0, songs[0]);
    album->addSong(0, songs[1]);
    album->addSong(1, songs[2]);
    album->print();

    int marks = 6;
    bool correct = true;

    cout<<"Getting songs in order:"<<endl;
    album->getSong(0, &song);
    if (song != songs[1]){
        cout<<"Wrong song at index 0"<<endl;
        correct = false;
    }
    album->getSong(1, &song);
    if (song != songs[2]){
        cout<<"Wrong song at index 1"<<endl;
        correct = false;
    }
    album->getSong(2, &song);
    if (song != songs[0]){
        cout<<"Wrong song at index 2"<<endl;
        correct = false;
    }

    if (!correct)marks -= 2;
    correct = true;

    cout<<"Testing remove song at index 1 (2 songs left):"<<endl;
    album->removeSong(1, &song);
    album->print();
    album->getSong(0, &song);
    if (song != songs[1]){
        cout<<"Wrong song at index 0"<<endl;
        correct = false;
    }
    album->getSong(1, &song);
    if (song != songs[0]){
        cout<<"Wrong song at index 1"<<endl;
        correct = false;
    }

    if (!correct)marks -= 2;
    correct = true;

    cout<<"Testing remove song at index 0 (1 song left):"<<endl;
    album->removeSong(0, &song);
    album->print();
    album->getSong(0, &song);
    if (song != songs[0]){
        cout<<"Wrong song at index 0"<<endl;
        correct = false;
    }

    if (!correct)marks -= 1;
    correct = true;

    cout<<"Testing remove song at index 1 (should not remove anything):"<<endl;
    album->removeSong(1, &song);
    cout<<"Printing album (should be 1 song):"<<endl;
    album->print();
    album->getSong(0, &song);
    if (song != songs[0]){
        cout<<"Wrong song at index 0"<<endl;
        marks -= 1;
    }

    cout<<"Testing remove song at index 0 (0 songs left):"<<endl;
    album->removeSong(0, &song);
    if (song != songs[0]){
        cout<<"Wrong song at index 0"<<endl;
        marks -= 1;
    }
    cout<<"Printing album (should be 0 songs), if any songs print deduct 1 mark:"<<endl;
    album->print();

    cout<<"Testing remove song at index 0 (should fail):"<<endl;
    song = NULL;
    if (album->getSong(0, &song)){
        cout<<"***ERROR**** getSong returned true, printing song"<<endl;
        song->print();
        marks -= 1;
    }
   
    delete album;
    for (int i = 0; i < 3; ++i){
        delete songs[i];
    }
    cout<<"Marks earned: "<<(marks>0?marks:0)<<" out of 6, plus 4 manual marks (inspecting the print statements in the first 3 tests). Divide this mark by 2 for a mark out of 5."<<endl;
    return 0;
}
		
int TestControl::albumArrayTest(){
    int points = 0;

    unordered_set<int> rartist;  //random artist
    unordered_set<int> rsong;    //random song
    Album* albs[4];
    unordered_set<int>::iterator iart, isong; //iterators for the sets

    
    ran(rartist, 2, 3); //choose 2 out of 3 artists 
    ran(rsong, 2, 5); // choose 2 out of 5 songs
    int count = 0;
    for (iart = rartist.begin(); iart != rartist.end(); ++iart){
        for (int alb = 0; alb < 2; ++alb){
            albs[count] = new Album(artists[*iart], albums[*iart][alb]);
            for (isong = rsong.begin(); isong != rsong.end(); ++isong){ 
                    albs[count]->addSong(new Song(artists[*iart], songTitles[*iart][alb][*isong], /*albums[*iart][alb],*/ songContent[*iart][alb][*isong]));
            }
            ++count;
        }
    }

    cout<<"Adding Albums to AlbumArray"<<endl;

    AlbumArray* aa = new AlbumArray();
    for (int i = 0; i < 4; ++i){
        aa->add(albs[i]);
    }

    cout<<"AlbumArray size (should be 4): "<<aa->size()<<endl;

    if (aa->size() ==4){
        cout<<"Correct size, +1 mark"<<endl;
        points += 1;
    }
    
    Album* alb;
    
    
    cout<<endl<<"Test get(string, string, Album**):   "<<endl<<endl;
    bool foundall = true;
    for (int i = 0; i < aa->size(); ++i){
        aa->get(albs[i]->getArtist(), albs[i]->getTitle(), &alb);
        if (alb != albs[i]){
            cout <<"Could not find "<<endl;
            albs[i]->print();
            foundall = false;
        }else{
            cout<<"Found "<<endl;
            alb->print();
        }
    }

    if (foundall){
        cout<<"Found all albums, +1 mark"<<endl<<endl;
        points += 1;
    }
    if(aa->get("Foo Fighters", "Learn to Fly", &alb)){
        cout<<"****ERROR**** Found non-existent Foo Fighters album, attempting to print:"<<endl;
        alb->print();
    }else{
        cout<<"Success: Did not find the (non-existent) Foo Fighters album, +1 marks"<<endl;
        points += 1;
    }
    
    cout<<endl<<"Test get(int, Album**) (proper order): "<<endl<<endl;
    bool inorder = true;
    
    Album *a1, *a2;
    for (int i = 1; i < aa->size(); ++i){
        if (!aa->get(i-1, &a1)){
            cout<<"Error, album at index "<<i-1<<" not found"<<endl;
            inorder = false;
        }
        if (!aa->get(i, &a2)){
            cout<<"Error, album at index "<<i<<" not found"<<endl;
            inorder = false;
        }

        if (inorder && a2->lessThan(*a1)){
            a1->printShort();
            a2->printShort();
            inorder = false;
            cout<<endl<<"Previous two albums are out of order"<<endl;
        }
    }

    for (int i = 0; i < aa->size(); ++i){
        aa->get(i, &a1);
        a1->printShort();
    }

    cout<<endl<<(inorder ? "In correct order, +2 marks": "Not in correct order")<<endl;
    if (inorder){points+=2;}

    int num = ran(0,4);
    cout << "Removing "<<endl;
    albs[num]->printShort();
    if (!aa->remove(albs[num]->getArtist(), albs[num]->getTitle(), &alb)){
        cout<<"***ERROR*** Could not find the above album, deducting 1 mark"<<endl;
        points -= 1;
    }

    if (aa->size() != 3){
        cout<<"AlbumArray size error, should be 3, instead: "<<aa->size()<<endl;
    }else{
        cout<<"Size is correct +1 mark" <<endl;
        points += 1;
    }

    cout<<endl<<"Test proper order: "<<endl<<endl;
    inorder = true;
    for (int i = 1; i < aa->size(); ++i){
        aa->get(i-1, &a1);
        aa->get(i, &a2);
        if (a2->lessThan(*a1)){
            a1->printShort();
            a2->printShort();
            inorder = false;
            cout<<endl<<"Previous two albums are out of order"<<endl;
        }
        if (albs[num]==a1 || albs[num]==a2){
            cout<<"Deleted album found"<<endl;
            inorder = false;
        }
    }

    for (int i = 0; i < aa->size(); ++i){
        aa->get(i, &a1);
        a1->printShort();
    }
    
    cout<<endl<<(inorder ? "In correct order": "Not in correct order")<<endl<<endl;
    if (inorder){cout<<"Delete successfull, +1 mark"<<endl; points += 1;}

    cout<<"Removing all albums from AlbumArray..."<<endl;
    while (aa->size()>0){
        aa->remove(0, &alb);
        cout<<"Removed: "<<endl;
        alb->printShort();
    }

    cout<<"AlbumArray size (should be 0): "<<aa->size()<<endl;
    if (aa->size() == 0){
       cout<<"Success, +1 mark"<<endl;
        points += 1;
    }
    cout<<"**MANUAL MARK** Printing all albums (should be nothing, else manually deduct 1 mark):"<<endl;
    aa->printShort();

    cout<<endl<<"Adding album back: "<<endl;
    albs[2]->printShort();
    aa->add(albs[2]);
    cout<<"Printing all albums (should be same as above):"<<endl;
    for (int i = 0; i < aa->size(); ++i){
        aa->get(i, &a1);
        a1->printShort();
        if (a1 != albs[2]){
            cout<<"Wrong album added"<<endl;
        }else{
            cout<<"Delete all then add test passed, +2 marks"<<endl;
            points += 2;
        }
    }

    cout<<"Deleting AlbumArray..."<<endl;
    delete aa;
    cout<<"**MANUAL MARK** If an error occurs in the next step, student may have deleted Album with AlbumArray, deduct 4 marks"<<endl<<endl;

    cout<<"Deleting albums..."<<endl;
    for (int i = 0; i < 4; ++i){
        delete albs[i];
    }

    cout<<"All albums deleted"<<endl;
    cout<<"Marks earned: "<<points<<endl;
    cout<<"Check above for manual deductions. Divide marks earned minus the deduction by 2 for a mark out of 5"<<endl;

    return points;
}

int TestControl::songifyTest(){
    int points = 5;
    Songify sify;
    cout<<"Initializing with Albums and Songs"<<endl;
    initialize(&sify);

    cout<<"Printing all albums (should be 3 artists, 2 albums each artist) "<<endl<<endl;
    sify.printAlbums();
    cout<<"**MANUAL MARK** If all albums print (without songs) 1 mark, otherwise 0 marks"<<endl;
    cout<<endl<<"Printing all songs (should be 3 artists, 2 albums each artist, 5 songs each album): "<<endl;
    sify.printSongs();
    cout<<"**MANUAL MARK** If all albums print (with songs) 1 mark, otherwise 0 marks"<<endl;

    cout<<endl<<"Testing find albums and songs..."<<endl;
    Album* album;
    Song* song;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 2; ++j){
            if (!sify.downloadAlbum(artists[i], albums[i][j], &album)){
                cout <<"Album "<< albums[i][j] <<" by "<< artists[i]<< " not found using function uploadAlbum, -1 point"<<endl;
                --points;
            }else{
                cout<<endl<<"Album "<<albums[i][j]<<" by "<<artists[i]<<" found using function uploadAlbum, attempting to stream all songs:"<<endl;
                for (int k = 0; k < 5; ++k){
                    if (!sify.streamSong(artists[i], albums[i][j], songTitles[i][j][k], &song)){
                        cout << "Song "<<songTitles[i][j]<<" from "<<albums[i][j]<<" by "<<artists[i]<<" not found, -1 point"<<endl;
                        --points;
                    }else{
                        cout<<"Song found: "<<endl;
                        song->print();
                    }
                }
            }
        }
    }

    

    int songIndex = ran(0,5);
    int artistIndex = ran(0,3);
    int albumIndex = ran(0,2);
    cout <<endl<<"Testing removeSong...removing song "<<songTitles[artistIndex][albumIndex][songIndex]
         <<" from "<<albums[artistIndex][albumIndex]<<" by "<<artists[artistIndex]<<endl;
    if (!sify.removeSong(artists[artistIndex], albums[artistIndex][albumIndex], songTitles[artistIndex][albumIndex][songIndex])){
        cout << "Song not found (or did you forget to return true?), -1 point"<<endl;
        --points;
    }else{
        cout<<"Song successfully(?) removed, attempting to stream:"<<endl;
        song = NULL;
        if (sify.streamSong(artists[artistIndex], albums[artistIndex][albumIndex], songTitles[artistIndex][albumIndex][songIndex], &song)){
            cout << "Song found after removal (or did you return true by accident?), -1 point, attempting to print..."<<endl;
            song->print();
            --points;
        }else{
            cout<<songTitles[artistIndex][albumIndex][songIndex]<<" successfully removed"<<endl<<endl;;
        }
    }
    artistIndex = ran(0,3);
    albumIndex = ran(0,2);
    cout <<"Testing removeAlbum...removing album "<<albums[artistIndex][albumIndex]<<" by "<<artists[artistIndex]<<endl;
    if (!sify.removeAlbum(artists[artistIndex], albums[artistIndex][albumIndex])){
        cout << "Album not found (or did you forget to return true?), -1 point"<<endl;
        --points;
    }else{
        cout<<"Album successfully(?) removed, attempting to upload:"<<endl;
        if (sify.downloadAlbum(artists[artistIndex], albums[artistIndex][albumIndex], &album)){
            cout << "Album found after removal (or did you return true by accident?), -1 point, attempting to print..."<<endl;
            album->print();
            --points;
        }else{
            cout<<"Album "<<albums[artistIndex][albumIndex]<<" successfully removed"<<endl;
        }
    }
    cout<<endl<<"Points earned: "<<(points>0?points:0)<<" out of 7\n-add 1 if all albums printed correctly in the first test\n-add 1 if all albums and songs printed correctly in the second test"<<endl;
    return (points>0?points:0);
}


int TestControl::clientTest(){
    int points = 5;
    Songify sify;
    Client client;

    initialize(&sify);

    int songIndex = ran(0,5);
    int artistIndex = ran(0,3);
    int albumIndex = ran(0,2);
    cout <<"Testing stream...streaming Song "<<songTitles[artistIndex][albumIndex][songIndex]
         <<" from "<<albums[artistIndex][albumIndex]<<" by "<<artists[artistIndex]<<endl<<endl;
    if (!client.stream(&sify, artists[artistIndex], albums[artistIndex][albumIndex], songTitles[artistIndex][albumIndex][songIndex])){
        cout << "Stream unsuccessful (or did you forget to return true?), -1 point"<<endl;
        --points;
    }

    cout <<"Testing download...downloading Album "<<albums[artistIndex][albumIndex]<<" by "<<artists[artistIndex]<<endl<<endl;

    if(!client.download(&sify,artists[artistIndex], albums[artistIndex][albumIndex])){
        cout << "Download unsuccessful (or did you forget to return true?), -3 points, test aborted."<<endl;
        points-=3;
        cout<<endl<<"Marks earned: "<<(points>0?points:0)<<" out of 5"<<endl;
        return points;
    }
    

    cout<<endl<<"Testing playLocal "<<songTitles[artistIndex][albumIndex][songIndex]
         <<" from "<<albums[artistIndex][albumIndex]<<" by "<<artists[artistIndex]<<endl<<endl;

    if (!client.playLocal(artists[artistIndex], albums[artistIndex][albumIndex], songTitles[artistIndex][albumIndex][songIndex])){
        cout << "PlayLocal unsuccessful (or did you forget to return true?), -1 mark"<<endl;
        --points;
    }

    cout<<endl<<"Removing original album from Songify, then testing playLocal again"<<endl<<endl;
    if(!sify.removeAlbum(artists[artistIndex], albums[artistIndex][albumIndex])){
        cout<<"Remove album failed (or did you forget to return true?), -2 marks, test aborted."<<endl;
        points-=2;
        cout<<endl<<"Marks earned: "<<(points>0?points:0)<<" out of 5"<<endl;
        return points;
    }

    if (!client.playLocal(artists[artistIndex], albums[artistIndex][albumIndex], songTitles[artistIndex][albumIndex][songIndex])){
        cout << "PlayLocal unsuccessful (or did you forget to return true?), -1 point"<<endl;
        --points;
    }
    cout<<"**MANUAL MARK** Printing all albums, no songs (should be 1 album):"<<endl;
    client.printAlbums();
    cout<<endl<<"**MANUAL MARK** Printing all songs (should be 1 album): "<<endl;
    client.printSongs();
    cout<<"Deduct 1 mark for each print function (immediately before this line) that does not work"<<endl;
    cout<<endl<<"Marks earned: "<<(points>0?points:0)<<" out of 5"<<endl;
    return points;

}

void TestControl::initialize(Songify* sify){
    //artist loop
    for (int i = 0; i < 3; ++i){
        //album loop
        for (int j = 0; j < 2; ++j){
            sify->addAlbum(artists[i], albums[i][j]);
            //song loop
            for (int k = 0; k < 5; ++k){
                sify->addSong(albums[i][j], Song(artists[i], songTitles[i][j][k],/* albums[i][j],*/songContent[i][j][k]));
            }
        }
    }
}

// s is the set to store count random numbers from 0 to range - 1
void TestControl::ran(unordered_set<int>& s, int count, int range){
    const int range_from  = 0;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range-1);

    while (s.size() < count){
        s.insert(distr(generator));
    }
}

// generate and return a single random number in the range range_from to range_to - 1
int TestControl::ran(int range_from, int range_to){
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to-1);
    return distr(generator);
}


// 3 artists
const string TestControl::artists[3] = {"Wierd Al", "Nirvana", "Dirty Nil"};
// each artist has 2 albums
const string TestControl::albums[3][2] = {"Mandatory Fun", "Even Worse", "Nevermind", "MTV Unplugged", "Master Volume", "Minimum R&B"};
// each album has 5 songs 
const string TestControl::songTitles[3][2][5] =
{"Handy", "Foil", "Word Crimes", "Tacky", "First World Problems", 
"Lasagna", "Melanie", "Alimony", "Velvet Elvis", "Twister", 
"In Bloom", "Drain You", "Lounge Act", "On a Plain", "Lithium", 
"About a Girl", "The Man Who Sold the World", "Dumb", "All Apologies", "Where Did You Sleep Last Night?", 
"Pain of Infinity", "Bathed in Light", "Always High", "Hit the Lights", "Please, Please Me", 
"F***in Up Young", "Little Metal Baby Fist", "Nicotine", "Verona Lung", "Beat"};

const string TestControl::songContent[3][2][5] = {"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero.",

"Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris.",

"Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla.",

"Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. ",
  
"Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor.",

"Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa.",

"Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh.",

"Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.",
  
"Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis.",

"Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien.",

"Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus.",

"Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam.",

"Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam.",

"In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet.",

"Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim.",

"Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi.",

"Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam.",

"Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo.",

"Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque.",

"Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet.",

"Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit.",

"Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet.",

"Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta.Mauris massa. Vestibulum lacinia arcu eget nulla.",

"Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc.",

"Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem.",

"Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa.",

"Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh.",


"Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.",

"Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis.",

"Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet."};

/*
"Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. ",

"Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. ",

"Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. ",

"Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. ",

"Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. ",

"Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. ",

"Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. ",

"Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. ",

"Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales. Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. ",

"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. ",

"Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. ",

"Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna.",

"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. ",
  
"Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos.",
  
"Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus.",

"Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper.",

"Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. Proin sodales libero eget ante. Nulla quam. Aenean laoreet. Vestibulum nisi lectus, commodo ac, facilisis ac, ultricies eu, pede. Ut orci risus, accumsan porttitor, cursus quis, aliquet eget, justo. Sed pretium blandit orci. Ut eu diam at pede suscipit sodales.",

"Aenean lectus elit, fermentum non, convallis id, sagittis at, neque. Nullam mauris orci, aliquet et, iaculis et, viverra vitae, ligula. Nulla ut felis in purus aliquam imperdiet. Maecenas aliquet mollis lectus. Vivamus consectetuer risus et tortor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta.",

"Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. Sed dignissim lacinia nunc. Curabitur tortor. Pellentesque nibh. Aenean quam. In scelerisque sem at dolor. Maecenas mattis. Sed convallis tristique sem. Proin ut ligula vel nunc egestas porttitor. ",

"Morbi lectus risus, iaculis vel, suscipit quis, luctus non, massa. Fusce ac turpis quis ligula lacinia aliquet. Mauris ipsum. Nulla metus metus, ullamcorper vel, tincidunt sed, euismod in, nibh. Quisque volutpat condimentum velit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nam nec ante. Sed lacinia, urna non tincidunt mattis, tortor neque adipiscing diam, a cursus ipsum ante quis turpis. Nulla facilisi. Ut fringilla. Suspendisse potenti. Nunc feugiat mi a tellus consequat imperdiet. ",

"Vestibulum sapien. Proin quam. Etiam ultrices. Suspendisse in justo eu magna luctus suscipit. Sed lectus. Integer euismod lacus luctus magna. Quisque cursus, metus vitae pharetra auctor, sem massa mattis sem, at interdum magna augue eget diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi lacinia molestie dui. Praesent blandit dolor. Sed non quam. In vel mi sit amet augue congue elementum. Morbi in ipsum sit amet pede facilisis laoreet. ",

"Donec lacus nunc, viverra nec, blandit vel, egestas et, augue. Vestibulum tincidunt malesuada tellus. Ut ultrices ultrices enim. Curabitur sit amet mauris. Morbi in dui quis est pulvinar ullamcorper. Nulla facilisi. Integer lacinia sollicitudin massa. Cras metus. Sed aliquet risus a tortor. Integer id quam. Morbi mi. Quisque nisl felis, venenatis tristique, dignissim in, ultrices sit amet, augue. "

};*/
