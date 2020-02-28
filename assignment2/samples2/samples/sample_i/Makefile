CC = g++
CFLAGS = -g -Wall	#Supressing the warnings

default: secure_house

secure_house: secure_house.o
	$(CC) $(CFLAGS) -o secure_house secure_house.o

secure_house.o: secure_house.cpp secure_house.h
	$(CC) $(CFLAGS) -c secure_house.cpp

clean:
	$(RM) secure_house *.o *-
