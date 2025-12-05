# Project name (can be different from directory name)
project(animate)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code

# Include Directories 
include_directories("include")

set(SRC_FILES
    src/main.cpp
)

# executable
set(exec_name animate)
add_executable(${exec_name} ${SRC_FILES})

target_link_libraries(${exec_name}
    PRIVATE SFML::Graphics
)


# copy resource files to binary directories
set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/images")
set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/images")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/images")
file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")