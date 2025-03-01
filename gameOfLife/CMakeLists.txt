# Project name (can be different from directory name)
project(GAMEOFLIFE)

# Source files 
#file(GLOB GAMELIFE_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")

# create executable or library 
#add_executable(gamelife ${GAMELIFE_SOURCES})

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fonts")

file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/bin/fonts")