# Project name (can be different from directory name)
project(DFSMAZE LANGUAGES CXX)

# Source files 
file(GLOB DFSMAZE_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")

# create executable or library 
add_executable(dfsmaze ${DFSMAZE_SOURCES})

target_compile_features(dfsmaze PRIVATE cxx_std_20)

# Link to other libraries (if needed)
target_link_libraries(dfsmaze PRIVATE SFML::Graphics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")