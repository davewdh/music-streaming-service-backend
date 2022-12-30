objects = main.o View.o Controller.o Songify.o MediaFactory.o Criteria.o Album.o Song.o

a4: $(objects)
	g++ -o a4 $(objects)

main.o: main.cc
	g++ -c main.cc 

View.o: View.h View.cc 
	g++ -c View.cc

Controller.o: Controller.h Controller.cc 
	g++ -c Controller.cc


Songify.o: Songify.h Songify.cc Array.h
	g++ -c Songify.cc

MediaFactory.o: MediaFactory.h MediaFactory.cc
	g++ -c MediaFactory.cc

Criteria.o: Criteria.cc Criteria.h
	g++ -c Criteria.cc

Album.o: Album.cc Album.h Array.h
	g++ -c Album.cc
	
Song.o: Song.cc Song.h 
	g++ -c Song.cc

clean:
	rm -f a4 *.o	