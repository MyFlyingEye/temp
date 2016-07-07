all:
	g++ mutex.cpp -pthread -std=c++11
	cp /home/box/temp/mutex.cpp /home/box/main.cpp
