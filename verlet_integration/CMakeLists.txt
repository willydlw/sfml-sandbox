# Project name (can be different from directory name)
project(VerletIntegration)

# Include Directories 
include_directories("include")

# create executable
add_executable(verlet)
target_sources(verlet PRIVATE src/main.cpp src/particle.cpp)



# Link to other libraries (if needed)
target_link_libraries(verlet PRIVATE SFML::Graphics)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

