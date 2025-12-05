# Project name (can be different from directory name)
project(GAMEOFLIFE)


# specify binary output directory 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)       # optional: Set to OFF for more portable code 


# Include Directories 
include_directories("include")


# executables
add_executable(gameLife)
target_sources(gameLife PRIVATE src/main.cpp src/gameLife.cpp)

add_executable(testNeighbors)
target_sources(testNeighbors PRIVATE 
    test/main.cpp
    test/neighborTest.cpp 
    src/gameLife.cpp
)


# Link to other libraries (if needed)
target_link_libraries(gameLife PRIVATE SFML::Graphics)
target_link_libraries(testNeighbors PRIVATE SFML::Graphics)


# copy font files to binary directories
set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fonts")
set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/fonts")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/fonts")
file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")

