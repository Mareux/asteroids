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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mareux/task2020_linux_mac/Framework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mareux/task2020_linux_mac/Framework

# Include any dependencies generated for this target.
include CMakeFiles/FrameworkRelease.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FrameworkRelease.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FrameworkRelease.dir/flags.make

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o: CMakeFiles/FrameworkRelease.dir/flags.make
CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o: src/launch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mareux/task2020_linux_mac/Framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o -c /Users/mareux/task2020_linux_mac/Framework/src/launch.cpp

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mareux/task2020_linux_mac/Framework/src/launch.cpp > CMakeFiles/FrameworkRelease.dir/src/launch.cpp.i

CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mareux/task2020_linux_mac/Framework/src/launch.cpp -o CMakeFiles/FrameworkRelease.dir/src/launch.cpp.s

# Object files for target FrameworkRelease
FrameworkRelease_OBJECTS = \
"CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o"

# External object files for target FrameworkRelease
FrameworkRelease_EXTERNAL_OBJECTS =

libFrameworkRelease.0.0.1.dylib: CMakeFiles/FrameworkRelease.dir/src/launch.cpp.o
libFrameworkRelease.0.0.1.dylib: CMakeFiles/FrameworkRelease.dir/build.make
libFrameworkRelease.0.0.1.dylib: /usr/local/lib/libSDL2.dylib
libFrameworkRelease.0.0.1.dylib: /usr/local/lib/libSDL2main.a
libFrameworkRelease.0.0.1.dylib: /usr/local/lib/libSDL2_image.dylib
libFrameworkRelease.0.0.1.dylib: CMakeFiles/FrameworkRelease.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mareux/task2020_linux_mac/Framework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libFrameworkRelease.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FrameworkRelease.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libFrameworkRelease.0.0.1.dylib libFrameworkRelease.0.0.1.dylib libFrameworkRelease.dylib

libFrameworkRelease.dylib: libFrameworkRelease.0.0.1.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libFrameworkRelease.dylib

# Rule to build all files generated by this target.
CMakeFiles/FrameworkRelease.dir/build: libFrameworkRelease.dylib

.PHONY : CMakeFiles/FrameworkRelease.dir/build

CMakeFiles/FrameworkRelease.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FrameworkRelease.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FrameworkRelease.dir/clean

CMakeFiles/FrameworkRelease.dir/depend:
	cd /Users/mareux/task2020_linux_mac/Framework && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mareux/task2020_linux_mac/Framework /Users/mareux/task2020_linux_mac/Framework /Users/mareux/task2020_linux_mac/Framework /Users/mareux/task2020_linux_mac/Framework /Users/mareux/task2020_linux_mac/Framework/CMakeFiles/FrameworkRelease.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FrameworkRelease.dir/depend

