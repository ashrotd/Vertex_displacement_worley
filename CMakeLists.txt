cmake_minimum_required(VERSION 3.0)

project(MyOpenGLProject)

# Define source files for each executable
set(SOURCES_Planetary_motion
    vertex.cpp
    uu.cpp
    camera.cpp
      # The main application entry point
    # Add other source files for the main executable
)

# Create an executable target for the main application
add_executable(main_program ${SOURCES_Planetary_motion})

# Find and link necessary libraries (e.g., GLFW, GLEW, OpenGL, glm)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# Link against GLFW, GLEW, OpenGL, and glm for the main executable
target_link_libraries(main_program PRIVATE ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} GL glm::glm)

# Specify include directories for both executables
target_include_directories(main_program PRIVATE ${PROJECT_SOURCE_DIR})

# Include the SOIL2 library and headers
target_link_libraries(main_program PRIVATE soil2)


# Specify the directory where SOIL2 headers are located
target_include_directories(main_program PRIVATE /usr/local/include/soil2)

# Specify the directory where SOIL2 library is located
target_link_directories(main_program PRIVATE /usr/local/lib)

