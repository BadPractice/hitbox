GLFLAGS=-lglut -lGLU -lGL -lXi -lXmu -lX11 -lm -lpthread

all: hitbox

hitbox: main.o tga.o
	g++ -o hitbox main.o tga.o $(GLFLAGS)

main.o: 
	g++ -c main.cpp $(GLFLAGS)
	
tga.o:
	g++ -c tga.cpp $(GLFLAGS)
	
clean:
	rm main.o tga.o hitbox
