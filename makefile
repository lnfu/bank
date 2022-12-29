all: build server client

build:
	mkdir build

server: src/server*.cpp src/utility.cpp
	g++ -std=c++17 src/server*.cpp src/utility.cpp -o build/server

client: src/client.cpp src/utility.cpp
	g++ -std=c++17 src/client.cpp src/utility.cpp -o build/client