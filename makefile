GLFLAGS=-lglut -lGLU -lGL -lX11 -lm -lpthread

all: hitbox

hitbox: main.o tga.o rotation.o position.o forward.o
	g++ -o hitbox main.o tga.o position.o rotation.o forward.o $(GLFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(GLFLAGS)
	
tga.o: tga.cpp
	g++ -c tga.cpp $(GLFLAGS)

forward.o: actions/forward.cpp actions/forward.hpp
	g++ -c actions/forward.cpp $(GLFLAGS)
	
position.o: dataobjects/position.cpp dataobjects/position.hpp
	g++ -c dataobjects/position.cpp $(GLFLAGS)

rotation.o: dataobjects/rotation.cpp dataobjects/rotation.hpp
	g++ -c dataobjects/rotation.cpp $(GLFLAGS)
	
clean:
	rm main.o tga.o rotation.o position.o forward.o hitbox
