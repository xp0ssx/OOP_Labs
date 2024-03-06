cmake_minimum_required(VERSION 3.11.1)
project(gtest)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    main main.cpp 
    src/Knight.cpp src/Dragon.cpp src/Pegasus.cpp 
    src/Battle.cpp src/FactoryHeroes.cpp src/Heroes.cpp src/Observer.cpp src/FightManager.cpp
)

enable_testing()

add_executable(testing tests/tests.cpp 
    src/Knight.cpp src/Dragon.cpp src/Pegasus.cpp
    src/Battle.cpp src/FactoryHeroes.cpp src/Heroes.cpp src/Observer.cpp src/FightManager.cpp
)
target_link_libraries(testing ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND testing)
