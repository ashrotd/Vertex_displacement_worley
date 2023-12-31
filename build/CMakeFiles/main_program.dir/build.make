# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rd238422/OpenGL/Bezier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rd238422/OpenGL/Bezier/build

# Include any dependencies generated for this target.
include CMakeFiles/main_program.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main_program.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_program.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main_program.dir/flags.make

CMakeFiles/main_program.dir/vertex.cpp.o: CMakeFiles/main_program.dir/flags.make
CMakeFiles/main_program.dir/vertex.cpp.o: ../vertex.cpp
CMakeFiles/main_program.dir/vertex.cpp.o: CMakeFiles/main_program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rd238422/OpenGL/Bezier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main_program.dir/vertex.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_program.dir/vertex.cpp.o -MF CMakeFiles/main_program.dir/vertex.cpp.o.d -o CMakeFiles/main_program.dir/vertex.cpp.o -c /home/rd238422/OpenGL/Bezier/vertex.cpp

CMakeFiles/main_program.dir/vertex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_program.dir/vertex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rd238422/OpenGL/Bezier/vertex.cpp > CMakeFiles/main_program.dir/vertex.cpp.i

CMakeFiles/main_program.dir/vertex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_program.dir/vertex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rd238422/OpenGL/Bezier/vertex.cpp -o CMakeFiles/main_program.dir/vertex.cpp.s

CMakeFiles/main_program.dir/uu.cpp.o: CMakeFiles/main_program.dir/flags.make
CMakeFiles/main_program.dir/uu.cpp.o: ../uu.cpp
CMakeFiles/main_program.dir/uu.cpp.o: CMakeFiles/main_program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rd238422/OpenGL/Bezier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main_program.dir/uu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_program.dir/uu.cpp.o -MF CMakeFiles/main_program.dir/uu.cpp.o.d -o CMakeFiles/main_program.dir/uu.cpp.o -c /home/rd238422/OpenGL/Bezier/uu.cpp

CMakeFiles/main_program.dir/uu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_program.dir/uu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rd238422/OpenGL/Bezier/uu.cpp > CMakeFiles/main_program.dir/uu.cpp.i

CMakeFiles/main_program.dir/uu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_program.dir/uu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rd238422/OpenGL/Bezier/uu.cpp -o CMakeFiles/main_program.dir/uu.cpp.s

CMakeFiles/main_program.dir/camera.cpp.o: CMakeFiles/main_program.dir/flags.make
CMakeFiles/main_program.dir/camera.cpp.o: ../camera.cpp
CMakeFiles/main_program.dir/camera.cpp.o: CMakeFiles/main_program.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rd238422/OpenGL/Bezier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main_program.dir/camera.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_program.dir/camera.cpp.o -MF CMakeFiles/main_program.dir/camera.cpp.o.d -o CMakeFiles/main_program.dir/camera.cpp.o -c /home/rd238422/OpenGL/Bezier/camera.cpp

CMakeFiles/main_program.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main_program.dir/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rd238422/OpenGL/Bezier/camera.cpp > CMakeFiles/main_program.dir/camera.cpp.i

CMakeFiles/main_program.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main_program.dir/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rd238422/OpenGL/Bezier/camera.cpp -o CMakeFiles/main_program.dir/camera.cpp.s

# Object files for target main_program
main_program_OBJECTS = \
"CMakeFiles/main_program.dir/vertex.cpp.o" \
"CMakeFiles/main_program.dir/uu.cpp.o" \
"CMakeFiles/main_program.dir/camera.cpp.o"

# External object files for target main_program
main_program_EXTERNAL_OBJECTS =

main_program: CMakeFiles/main_program.dir/vertex.cpp.o
main_program: CMakeFiles/main_program.dir/uu.cpp.o
main_program: CMakeFiles/main_program.dir/camera.cpp.o
main_program: CMakeFiles/main_program.dir/build.make
main_program: /usr/lib/x86_64-linux-gnu/libGLEW.so
main_program: CMakeFiles/main_program.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rd238422/OpenGL/Bezier/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable main_program"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main_program.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main_program.dir/build: main_program
.PHONY : CMakeFiles/main_program.dir/build

CMakeFiles/main_program.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_program.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_program.dir/clean

CMakeFiles/main_program.dir/depend:
	cd /home/rd238422/OpenGL/Bezier/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rd238422/OpenGL/Bezier /home/rd238422/OpenGL/Bezier /home/rd238422/OpenGL/Bezier/build /home/rd238422/OpenGL/Bezier/build /home/rd238422/OpenGL/Bezier/build/CMakeFiles/main_program.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main_program.dir/depend

