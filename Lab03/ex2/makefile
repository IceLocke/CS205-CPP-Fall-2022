CC = g++
TARGET = main
OBJ = main.o fac.o

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

main.o: fac.cpp
	$(CC) -c main.cpp

fib.o: fac.cpp
	$(CC) -c fib.cpp

.PHONY: clean
clean:
	rm -f *.o $(TARGET)