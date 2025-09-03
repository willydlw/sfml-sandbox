# Project name (can be different from directory name)
project(ARROW)



# Include Directories 
include_directories("include")

# create executable or library 
add_executable(arrow)
target_sources(arrow PRIVATE 
    src/main.cpp
    src/arrow.cpp
)


# Link to other libraries (if needed)
# PUBLIC m links math library
target_link_libraries(arrow PRIVATE SFML::Graphics PUBLIC m)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fonts")
file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/bin/fonts")