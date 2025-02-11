# Project name (can be different from directory name)
project(DFSMAZE)

# Source files 
file(GLOB DFSMAZE_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")

# create executable or library 
add_executable(dfsmaze ${DFSMAZE_SOURCES})

# Link to other libraries (if needed)
target_link_libraries(dfsmaze PRIVATE SFML::Graphics)