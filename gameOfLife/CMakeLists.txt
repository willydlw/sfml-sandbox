# Project name (can be different from directory name)
project(GAMEOFLIFE)

# Source files 
file(GLOB GAMELIFE_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")

# create executable or library 
add_executable(gamelife ${GAMELIFE_SOURCES})

# Link to other libraries (if needed)
target_link_libraries(gamelife PRIVATE SFML::Graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")