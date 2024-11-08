cmake_minimum_required(VERSION 3.10)

project(SolarSystem)

set(CMAKE_CXX_STANDARD 14)

# # Include directories
# include_directories(
#     src
#     include/KHR
#     include/glad
#     include/GLFW
# )

# Find GLFW library
find_package(GLFW3 REQUIRED)

# Set bin directory
set(BIN_DIR bin)

# Set include directory
set(INC_DIR include)

# Set source directory
set(SRC_DIR src)

# Recursively find all source files
file(GLOB_RECURSE CPP_SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE C_SOURCES "${SRC_DIR}/*.c")

# Recursively find all header files
file(GLOB_RECURSE HPP_HEADERS "${SRC_DIR}/*.hpp")

# Find all header files in include directorys
file(GLOB_RECURSE INC_HEADERS "${INC_DIR}/*.h")

# Add all source files to the project
include_directories(${SRC_DIR})

# Add all header files to the project
include_directories(${INC_DIR})

add_executable(${PROJECT_NAME} ${CPP_SOURCES} ${C_SOURCES} ${HPP_HEADERS} ${H_HEADERS} ${INC_HEADERS})

# Link GLFW and GLAD libraries
target_link_libraries(${PROJECT_NAME} ${GLFW3_LIBRARIES})

# Link required frameworks
target_link_libraries(${PROJECT_NAME}
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)

# Link libglfw.3.4.dylib
target_link_libraries(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/lib/libglfw.3.4.dylib
)

# # Set the output directory
# set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

# # Install the executable
# install(TARGETS ${PROJECT_NAME} DESTINATION ${BIN_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})