CC = g++
OPENCV = -I /usr/include/opencv4 -g
CFLAGS = -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -std=c++11
BIN = bin/app

main: src/main.cpp
	${CC} $(OPENCV) -lc -o bin/app src/main.cpp $(CFLAGS)
	@./$(BIN)

clean:
	rm -f *.o bin/app
