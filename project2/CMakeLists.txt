# Project name (can be different from directory name)
project(Project2)

# Source files 
file(GLOB PROJECT2_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")
#include_directories("../utils/include")

# create executable or library 
add_executable(project2 ${PROJECT2_SOURCES})
#add_library(project1_lib ${PROJECT1_SOURCES})

# Link to other libraries (if needed)
#target_link_libraries(project2 utils_lib)
target_link_libraries(main PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)