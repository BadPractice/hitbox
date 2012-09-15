GLFLAGS=-lglut -lGLU -lGL -lX11 -lm -lpthread

all: hitbox

hitbox: main.o tga.o rotation.o position.o forward.o actionlist.o backward.o leftward.o rightward.o
	g++ -o hitbox main.o tga.o position.o rotation.o forward.o actionlist.o backward.o leftward.o rightward.o $(GLFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(GLFLAGS)
	
tga.o: tga.cpp
	g++ -c tga.cpp $(GLFLAGS)

forward.o: actions/forward.cpp actions/forward.hpp
	g++ -c actions/forward.cpp $(GLFLAGS)

backward.o:actions/backward.cpp actions/backward.hpp
	g++ -c actions/backward.cpp $(GLFLAGS)
	
leftward.o:actions/leftward.cpp actions/leftward.hpp
	g++ -c actions/leftward.cpp $(GLFLAGS)

rightward.o:actions/rightward.cpp actions/rightward.hpp
	g++ -c actions/rightward.cpp $(GLFLAGS)
	
position.o: dataobjects/position.cpp dataobjects/position.hpp
	g++ -c dataobjects/position.cpp $(GLFLAGS)

rotation.o: dataobjects/rotation.cpp dataobjects/rotation.hpp
	g++ -c dataobjects/rotation.cpp $(GLFLAGS)

actionlist.o: forward.o position.o rotation.o
	g++ -c actionlist.cpp $(GLFLAGS)
	
clean:
	rm main.o tga.o rotation.o position.o forward.o backward.o actionlist.o leftward.o rightward.o hitbox
