# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check

# Include any dependencies generated for this target.
include duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/depend.make

# Include the progress variables for this target.
include duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/progress.make

# Include the compile flags for this target's objects.
include duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/flags.make

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/flags.make
duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o: duck_duck_goose_tests/basic_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o"
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o -c /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests/basic_tests.cpp

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.i"
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests/basic_tests.cpp > CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.i

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.s"
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests/basic_tests.cpp -o CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.s

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.requires:

.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.requires

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.provides: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.requires
	$(MAKE) -f duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/build.make duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.provides.build
.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.provides

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.provides.build: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o


# Object files for target duck_duck_goose_test
duck_duck_goose_test_OBJECTS = \
"CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o"

# External object files for target duck_duck_goose_test
duck_duck_goose_test_EXTERNAL_OBJECTS =

duck_duck_goose_tests/duck_duck_goose_test: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o
duck_duck_goose_tests/duck_duck_goose_test: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/build.make
duck_duck_goose_tests/duck_duck_goose_test: testing_utils/libtesting_utils.a
duck_duck_goose_tests/duck_duck_goose_test: libhw2_user_code.a
duck_duck_goose_tests/duck_duck_goose_test: /usr/lib/libgtest.a
duck_duck_goose_tests/duck_duck_goose_test: testing_utils/kwsys/libkwsys.a
duck_duck_goose_tests/duck_duck_goose_test: /usr/lib/libgtest_main.a
duck_duck_goose_tests/duck_duck_goose_test: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable duck_duck_goose_test"
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/duck_duck_goose_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/build: duck_duck_goose_tests/duck_duck_goose_test

.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/build

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/requires: duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/basic_tests.cpp.o.requires

.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/requires

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/clean:
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests && $(CMAKE_COMMAND) -P CMakeFiles/duck_duck_goose_test.dir/cmake_clean.cmake
.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/clean

duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/depend:
	cd /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests /home/cs104/Desktop/homework/hw-alfonsar/hw2/hw2-check/duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : duck_duck_goose_tests/CMakeFiles/duck_duck_goose_test.dir/depend

