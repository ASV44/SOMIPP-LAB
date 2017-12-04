compile: *.cpp
	g++ -std=c++11 -o restaurantSimulation main.cpp Restaurant.cpp Food.cpp OrdersGenerator.cpp
# %.o: %.cpp %.h
#
