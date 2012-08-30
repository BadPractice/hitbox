GLFLAGS=-lglut -lGLU -lGL -lX11 -lm -lpthread

all: hitbox

hitbox: main.o tga.o rotation.o
	g++ -o hitbox main.o tga.o rotation.o $(GLFLAGS)

main.o: 
	g++ -c main.cpp $(GLFLAGS)
	
tga.o:
	g++ -c tga.cpp $(GLFLAGS)

rotation.o:
	g++ -c dataobjects/rotation.cpp $(GLFLAGS)
	
clean:
	rm main.o tga.o rotation.o hitbox
