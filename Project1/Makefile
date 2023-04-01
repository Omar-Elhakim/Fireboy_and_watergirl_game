CFLAGS=-Wall -g

install: FileName.o
	g++ FileName.o -o sfml-app -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
	rm FileName.o
	./sfml-app & 

FileName.o: FileName.cpp
	# make clean
	g++ -c FileName.cpp

clean:
	rm -f FileName.o sfml-app
