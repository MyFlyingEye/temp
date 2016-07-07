all:
	g++ conditions.cpp -pthread -std=c++11
	cp /home/box/temp/conditions.cpp /home/box/main.cpp
