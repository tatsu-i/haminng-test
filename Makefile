SRC=main.c encode.c
TARGET=main
CC=gcc
CFLAGS=-g -O2 -w
OBJS=main.o encode.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCDIR) $(LIBDIR) -o $@ $^ $(LIBS) 

clean:
	@rm -fr $(TARGET) $(OBJS) *~ *.swp
