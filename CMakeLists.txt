cmake_minimum_required(VERSION 3.14)
project(Airport_Cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system)

add_executable(
        Airport_Cpp
        src/aircraft.cpp
        src/main.cpp
        src/random.cpp
        src/simulation.cpp
        src/aircraft_template.cpp
        src/weight_category.cpp
        src/aircraft_removal_strategy.cpp
        src/wind_indicator.cpp
        src/wind_simulation.cpp
)

file(COPY resources DESTINATION .)
