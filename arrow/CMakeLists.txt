# Project name (can be different from directory name)
project(arrow)

# specify binary output directory 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS_OFF)       # optional: Set to OFF for more portable code 

# Include Directories
include_directories("include")


set(SRC_FILES 
    src/main.cpp
    src/arrow.cpp
)

# executable
set(exec_name arrow)
add_executable(${exec_name} ${SRC_FILES})

target_link_libraries(${exec_name}
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
)


# copy font files to binary directories
set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fonts")
set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/fonts")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/fonts")
file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")