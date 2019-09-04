cmake_minimum_required(VERSION 3.14)
project(Airport_Cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system)

add_executable(Airport_Cpp
        include/aircraft.hpp
        include/random.hpp
        include/simulation.hpp
        src/aircraft.cpp
        src/main.cpp
        src/random.cpp
        src/simulation.cpp include/aircraft_template.hpp src/aircraft_template.cpp include/weight_category.hpp src/weight_category.cpp include/aircraft_base.hpp include/aircraft_removal_strategy.hpp src/aircraft_removal_strategy.cpp)

file(COPY resources DESTINATION .)
