compile: *.cpp
	g++ -std=c++11 -o restaurantSimulation main.cpp Restaurant.cpp Food.cpp OrdersGenerator.cpp FoodSpecification.cpp Order.cpp RandomUtils.cpp
# %.o: %.cpp %.h
#
