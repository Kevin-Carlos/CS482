# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam"

# Include any dependencies generated for this target.
include CMakeFiles/classify.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/classify.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/classify.dir/flags.make

CMakeFiles/classify.dir/src/classify.cc.o: CMakeFiles/classify.dir/flags.make
CMakeFiles/classify.dir/src/classify.cc.o: src/classify.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/classify.dir/src/classify.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/classify.dir/src/classify.cc.o -c "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/src/classify.cc"

CMakeFiles/classify.dir/src/classify.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/classify.dir/src/classify.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/src/classify.cc" > CMakeFiles/classify.dir/src/classify.cc.i

CMakeFiles/classify.dir/src/classify.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/classify.dir/src/classify.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/src/classify.cc" -o CMakeFiles/classify.dir/src/classify.cc.s

CMakeFiles/classify.dir/src/classify.cc.o.requires:

.PHONY : CMakeFiles/classify.dir/src/classify.cc.o.requires

CMakeFiles/classify.dir/src/classify.cc.o.provides: CMakeFiles/classify.dir/src/classify.cc.o.requires
	$(MAKE) -f CMakeFiles/classify.dir/build.make CMakeFiles/classify.dir/src/classify.cc.o.provides.build
.PHONY : CMakeFiles/classify.dir/src/classify.cc.o.provides

CMakeFiles/classify.dir/src/classify.cc.o.provides.build: CMakeFiles/classify.dir/src/classify.cc.o


# Object files for target classify
classify_OBJECTS = \
"CMakeFiles/classify.dir/src/classify.cc.o"

# External object files for target classify
classify_EXTERNAL_OBJECTS =

classify: CMakeFiles/classify.dir/src/classify.cc.o
classify: CMakeFiles/classify.dir/build.make
classify: CMakeFiles/classify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable classify"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/classify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/classify.dir/build: classify

.PHONY : CMakeFiles/classify.dir/build

CMakeFiles/classify.dir/requires: CMakeFiles/classify.dir/src/classify.cc.o.requires

.PHONY : CMakeFiles/classify.dir/requires

CMakeFiles/classify.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/classify.dir/cmake_clean.cmake
.PHONY : CMakeFiles/classify.dir/clean

CMakeFiles/classify.dir/depend:
	cd "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam" "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam" "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam" "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam" "/mnt/c/Users/mrtk8/Google Drive/UNR/CS482/Spam/CMakeFiles/classify.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/classify.dir/depend

