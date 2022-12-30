objects = main.o TestView.o TestControl.o Client.o Songify.o AlbumArray.o Album.o SongArray.o Song.o

a2: $(objects)
	g++ -o a2 $(objects)

main.o: main.cc
	g++ -c main.cc 

TestView.o: TestView.h TestView.cc 
	g++ -c TestView.cc

TestControl.o: TestControl.h TestControl.cc 
	g++ -c TestControl.cc

Client.o: Client.h Client.cc 
	g++ -c Client.cc

Songify.o: Songify.h Songify.cc
	g++ -c Songify.cc

AlbumArray.o: AlbumArray.h AlbumArray.cc
	g++ -c AlbumArray.cc

Album.o: Album.cc Album.h
	g++ -c Album.cc

SongArray.o: SongArray.cc SongArray.h
	g++ -c SongArray.cc
	
Song.o: Song.cc Song.h 
	g++ -c Song.cc

clean:
	rm -f a2 *.o	