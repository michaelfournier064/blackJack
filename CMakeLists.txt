cmake_minimum_required(VERSION 3.10)
project(blackjack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library sources
set(SOURCES
    src/assistingFunctions.cpp
    src/cardDrawing.cpp
    src/gameStart.cpp
    src/errorHandler.cpp
)

set(HEADERS
    include/assistingFunctions.h
    include/cardDrawing.h
    include/errorHandler.h
    include/gameStart.h
)

add_library(blackjack STATIC ${SOURCES})
target_include_directories(blackjack PUBLIC include)

add_executable(blackjack_cli main.cpp)
target_link_libraries(blackjack_cli PRIVATE blackjack)
