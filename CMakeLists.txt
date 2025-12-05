# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.28)

# super project name Sandbox
project(Sandbox LANGUAGES CXX)

# add sub-project directories
add_subdirectory(dependencies)
add_subdirectory(project1)
add_subdirectory(project2)
#add_subdirectory(maze_gen_dfs)
#add_subdirectory(gameOfLife)
#add_subdirectory(verlet_integration)
#add_subdirectory(arrow)
#add_subdirectory(animate)