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
CMAKE_COMMAND = /home/segfault/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/segfault/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/183.4588.63/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/segfault/Desktop/RType

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/segfault/Desktop/RType/cmake-build-debug

# Include any dependencies generated for this target.
include Client/CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include Client/CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include Client/CMakeFiles/client.dir/flags.make

Client/CMakeFiles/client.dir/Src/Commands.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Commands.cpp.o: ../Client/Src/Commands.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Client/CMakeFiles/client.dir/Src/Commands.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Commands.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Commands.cpp

Client/CMakeFiles/client.dir/Src/Commands.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Commands.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Commands.cpp > CMakeFiles/client.dir/Src/Commands.cpp.i

Client/CMakeFiles/client.dir/Src/Commands.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Commands.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Commands.cpp -o CMakeFiles/client.dir/Src/Commands.cpp.s

Client/CMakeFiles/client.dir/Src/Core.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Core.cpp.o: ../Client/Src/Core.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Client/CMakeFiles/client.dir/Src/Core.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Core.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Core.cpp

Client/CMakeFiles/client.dir/Src/Core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Core.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Core.cpp > CMakeFiles/client.dir/Src/Core.cpp.i

Client/CMakeFiles/client.dir/Src/Core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Core.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Core.cpp -o CMakeFiles/client.dir/Src/Core.cpp.s

Client/CMakeFiles/client.dir/Src/Game.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Game.cpp.o: ../Client/Src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Client/CMakeFiles/client.dir/Src/Game.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Game.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Game.cpp

Client/CMakeFiles/client.dir/Src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Game.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Game.cpp > CMakeFiles/client.dir/Src/Game.cpp.i

Client/CMakeFiles/client.dir/Src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Game.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Game.cpp -o CMakeFiles/client.dir/Src/Game.cpp.s

Client/CMakeFiles/client.dir/Src/Main.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Main.cpp.o: ../Client/Src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Client/CMakeFiles/client.dir/Src/Main.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Main.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Main.cpp

Client/CMakeFiles/client.dir/Src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Main.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Main.cpp > CMakeFiles/client.dir/Src/Main.cpp.i

Client/CMakeFiles/client.dir/Src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Main.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Main.cpp -o CMakeFiles/client.dir/Src/Main.cpp.s

Client/CMakeFiles/client.dir/Src/Menu.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Menu.cpp.o: ../Client/Src/Menu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Client/CMakeFiles/client.dir/Src/Menu.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Menu.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Menu.cpp

Client/CMakeFiles/client.dir/Src/Menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Menu.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Menu.cpp > CMakeFiles/client.dir/Src/Menu.cpp.i

Client/CMakeFiles/client.dir/Src/Menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Menu.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Menu.cpp -o CMakeFiles/client.dir/Src/Menu.cpp.s

Client/CMakeFiles/client.dir/Src/Textures.cpp.o: Client/CMakeFiles/client.dir/flags.make
Client/CMakeFiles/client.dir/Src/Textures.cpp.o: ../Client/Src/Textures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Client/CMakeFiles/client.dir/Src/Textures.cpp.o"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/Src/Textures.cpp.o -c /home/segfault/Desktop/RType/Client/Src/Textures.cpp

Client/CMakeFiles/client.dir/Src/Textures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/Src/Textures.cpp.i"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/segfault/Desktop/RType/Client/Src/Textures.cpp > CMakeFiles/client.dir/Src/Textures.cpp.i

Client/CMakeFiles/client.dir/Src/Textures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/Src/Textures.cpp.s"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/segfault/Desktop/RType/Client/Src/Textures.cpp -o CMakeFiles/client.dir/Src/Textures.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/Src/Commands.cpp.o" \
"CMakeFiles/client.dir/Src/Core.cpp.o" \
"CMakeFiles/client.dir/Src/Game.cpp.o" \
"CMakeFiles/client.dir/Src/Main.cpp.o" \
"CMakeFiles/client.dir/Src/Menu.cpp.o" \
"CMakeFiles/client.dir/Src/Textures.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

Client/bin/client: Client/CMakeFiles/client.dir/Src/Commands.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/Src/Core.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/Src/Game.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/Src/Main.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/Src/Menu.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/Src/Textures.cpp.o
Client/bin/client: Client/CMakeFiles/client.dir/build.make
Client/bin/client: Client/CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/segfault/Desktop/RType/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable bin/client"
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Client/CMakeFiles/client.dir/build: Client/bin/client

.PHONY : Client/CMakeFiles/client.dir/build

Client/CMakeFiles/client.dir/clean:
	cd /home/segfault/Desktop/RType/cmake-build-debug/Client && $(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : Client/CMakeFiles/client.dir/clean

Client/CMakeFiles/client.dir/depend:
	cd /home/segfault/Desktop/RType/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/segfault/Desktop/RType /home/segfault/Desktop/RType/Client /home/segfault/Desktop/RType/cmake-build-debug /home/segfault/Desktop/RType/cmake-build-debug/Client /home/segfault/Desktop/RType/cmake-build-debug/Client/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Client/CMakeFiles/client.dir/depend

