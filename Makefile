CC = g++
CCFLAGS = -std=c++11

huffencode: huffencode.o huffen.o huffen.h
	$(CC) $(CCFLAGS) huffencode.o huffen.o -o huffencode

huffencode.o: huffencode.cpp huffen.h
	$(CC) $(CCFLAGS) -c huffencode.cpp -o huffencode.o

huffen.o: huffen.cpp huffen.h
	$(CC) $(CCFLAGS) -c huffen.cpp -o huffen.o

clean:
	rm *.o