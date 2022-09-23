CC = g++
TARGET = main
OBJ = main.o fib.o

$(TARGET) : $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

main.o: main.cpp
	$(CC) -c main.cpp

fib.o: fib.cpp
	$(CC) -c fib.cpp

.PHONY: clean
clean:
	rm -f *.o $(TARGET)