# Project name (can be different from directory name)
project(Project1)

# Source files 
file(GLOB PROJECT1_SOURCES "src/*.cpp")

# Include Directories 
include_directories("include")
#include_directories("../utils/include")

# create executable or library 
add_executable(project1 ${PROJECT1_SOURCES})
#add_library(project1_lib ${PROJECT1_SOURCES})

# Link to other libraries (if needed)
#target_link_libraries(project1 utils_lib)
target_link_libraries(project1 PRIVATE SFML::Graphics ImGui-SFML::ImGui-SFML)