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
CMAKE_SOURCE_DIR = /home/nby9hc/Learning/cpp/5thWeek/ChattingTool

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build

# Include any dependencies generated for this target.
include src/CMakeFiles/SocketClient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/SocketClient.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/SocketClient.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/SocketClient.dir/flags.make

src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o: src/CMakeFiles/SocketClient.dir/flags.make
src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o: ../src/SocketClient.cpp
src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o: src/CMakeFiles/SocketClient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o"
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o -MF CMakeFiles/SocketClient.dir/SocketClient.cpp.o.d -o CMakeFiles/SocketClient.dir/SocketClient.cpp.o -c /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/src/SocketClient.cpp

src/CMakeFiles/SocketClient.dir/SocketClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SocketClient.dir/SocketClient.cpp.i"
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/src/SocketClient.cpp > CMakeFiles/SocketClient.dir/SocketClient.cpp.i

src/CMakeFiles/SocketClient.dir/SocketClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SocketClient.dir/SocketClient.cpp.s"
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/src/SocketClient.cpp -o CMakeFiles/SocketClient.dir/SocketClient.cpp.s

# Object files for target SocketClient
SocketClient_OBJECTS = \
"CMakeFiles/SocketClient.dir/SocketClient.cpp.o"

# External object files for target SocketClient
SocketClient_EXTERNAL_OBJECTS =

../release/lib/libSocketClient.so: src/CMakeFiles/SocketClient.dir/SocketClient.cpp.o
../release/lib/libSocketClient.so: src/CMakeFiles/SocketClient.dir/build.make
../release/lib/libSocketClient.so: src/CMakeFiles/SocketClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library ../../release/lib/libSocketClient.so"
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SocketClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/SocketClient.dir/build: ../release/lib/libSocketClient.so
.PHONY : src/CMakeFiles/SocketClient.dir/build

src/CMakeFiles/SocketClient.dir/clean:
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src && $(CMAKE_COMMAND) -P CMakeFiles/SocketClient.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/SocketClient.dir/clean

src/CMakeFiles/SocketClient.dir/depend:
	cd /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nby9hc/Learning/cpp/5thWeek/ChattingTool /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/src /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src /home/nby9hc/Learning/cpp/5thWeek/ChattingTool/build/src/CMakeFiles/SocketClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/SocketClient.dir/depend
