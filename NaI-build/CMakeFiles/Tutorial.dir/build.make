# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jack/Documents/geant4/NaI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jack/Documents/geant4/NaI/NaI-build

# Utility rule file for Tutorial.

# Include the progress variables for this target.
include CMakeFiles/Tutorial.dir/progress.make

CMakeFiles/Tutorial: NaI


Tutorial: CMakeFiles/Tutorial
Tutorial: CMakeFiles/Tutorial.dir/build.make

.PHONY : Tutorial

# Rule to build all files generated by this target.
CMakeFiles/Tutorial.dir/build: Tutorial

.PHONY : CMakeFiles/Tutorial.dir/build

CMakeFiles/Tutorial.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Tutorial.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Tutorial.dir/clean

CMakeFiles/Tutorial.dir/depend:
	cd /home/jack/Documents/geant4/NaI/NaI-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jack/Documents/geant4/NaI /home/jack/Documents/geant4/NaI /home/jack/Documents/geant4/NaI/NaI-build /home/jack/Documents/geant4/NaI/NaI-build /home/jack/Documents/geant4/NaI/NaI-build/CMakeFiles/Tutorial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tutorial.dir/depend

