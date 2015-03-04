CC = g++

drawtri : main.o mainframe.o dialogs.o openglcanvas.o
	$(CC) -o drawtri main.o mainframe.o dialogs.o openglcanvas.o `wx-config --libs --gl-libs` -lGL -lglut

main.o : main.cpp 
	$(CC) `wx-config --cxxflags` -c main.cpp -o main.o

mainframe.o : mainframe.cpp
	$(CC) `wx-config --cxxflags` -c mainframe.cpp -o mainframe.o

dialogs.o : dialogs.cpp
	$(CC) `wx-config --cxxflags` -c dialogs.cpp -o dialogs.o

openglcanvas.o : openglcanvas.cpp
	$(CC) `wx-config --cxxflags` -c openglcanvas.cpp -o openglcanvas.o

clean : 
	rm -f *.o drawtri

run :
	make
	./drawtri
