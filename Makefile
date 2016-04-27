OBJS = pirouette.o socket_layer.o controller.o
CC = g++
CFLAGS = -Wall -c -std=c++14
WIRING_FLAGS = -lwiringPi -lpthread
LFLAGS = -Wall -std=c++14
COMP = $(CC) $(DEBUG) $(CFLAGS) $<
EXEC = $(CC) $(LFLAGS) $(WIRING_FLAGS) $(OBJS) -o pirouette

pirouette : $(OBJS)
	$(EXEC)

pirouette.o : pirouette.cpp pirouette.h
	$(COMP)

socket_layer.o: socket_layer.cpp socket_layer.h
	$(COMP)

controller.o: controller.cpp controller.h
	$(COMP)

clean:
	rm -r *.o; rm pirouette

run:
	./pirouette

.PHONY: clean debug

