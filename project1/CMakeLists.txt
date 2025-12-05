# project name can be different from executable name
project(project1)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code

include_directories("include")

set(SRC_FILES
    src/main.cpp
)

# executable
set(exec_name project1)
add_executable(${exec_name} ${SRC_FILES})

target_link_libraries(${exec_name}
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC  m
)


# copy resource files to binary directories
#set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
#set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/resources")

#file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/resources")
#file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")
