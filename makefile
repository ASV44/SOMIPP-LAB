compile: *.cpp
	g++ -std=c++11 -o restaurantSimulation main.cpp Restaurant.cpp Food.cpp OrdersGenerator.cpp RestaurantMenu.cpp Order.cpp RandomUtils.cpp CooksManager.cpp Cook.cpp
# %.o: %.cpp %.h
#
