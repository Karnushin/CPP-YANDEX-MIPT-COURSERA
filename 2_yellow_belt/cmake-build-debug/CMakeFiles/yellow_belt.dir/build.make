# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Barnett/CLionProjects/yellow_belt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/yellow_belt.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/yellow_belt.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/yellow_belt.dir/flags.make

CMakeFiles/yellow_belt.dir/main.cpp.o: CMakeFiles/yellow_belt.dir/flags.make
CMakeFiles/yellow_belt.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/yellow_belt.dir/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yellow_belt.dir/main.cpp.o -c /Users/Barnett/CLionProjects/yellow_belt/main.cpp

CMakeFiles/yellow_belt.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yellow_belt.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Barnett/CLionProjects/yellow_belt/main.cpp > CMakeFiles/yellow_belt.dir/main.cpp.i

CMakeFiles/yellow_belt.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yellow_belt.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Barnett/CLionProjects/yellow_belt/main.cpp -o CMakeFiles/yellow_belt.dir/main.cpp.s

# Object files for target yellow_belt
yellow_belt_OBJECTS = \
"CMakeFiles/yellow_belt.dir/main.cpp.o"

# External object files for target yellow_belt
yellow_belt_EXTERNAL_OBJECTS =

yellow_belt: CMakeFiles/yellow_belt.dir/main.cpp.o
yellow_belt: CMakeFiles/yellow_belt.dir/build.make
yellow_belt: CMakeFiles/yellow_belt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable yellow_belt"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yellow_belt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/yellow_belt.dir/build: yellow_belt

.PHONY : CMakeFiles/yellow_belt.dir/build

CMakeFiles/yellow_belt.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/yellow_belt.dir/cmake_clean.cmake
.PHONY : CMakeFiles/yellow_belt.dir/clean

CMakeFiles/yellow_belt.dir/depend:
	cd /Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Barnett/CLionProjects/yellow_belt /Users/Barnett/CLionProjects/yellow_belt /Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug /Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug /Users/Barnett/CLionProjects/yellow_belt/cmake-build-debug/CMakeFiles/yellow_belt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/yellow_belt.dir/depend

