CC=g++
main: main.o Data.o displayData.o Scene2D.o Scene2DElement.o VerticalKnotBar.o HorizontalKnotBar.o TMesh.o
	$(CC) -o main main.o Data.o displayData.o Scene2D.o Scene2DElement.o VerticalKnotBar.o HorizontalKnotBar.o TMesh.o -lGL -lGLU -lglut -O2 -larmadillo
	rm *.o
	./main