# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gflib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gflib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gflib.dir/flags.make

CMakeFiles/gflib.dir/content.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/content.c.o: ../content.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gflib.dir/content.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/content.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/content.c

CMakeFiles/gflib.dir/content.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/content.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/content.c > CMakeFiles/gflib.dir/content.c.i

CMakeFiles/gflib.dir/content.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/content.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/content.c -o CMakeFiles/gflib.dir/content.c.s

CMakeFiles/gflib.dir/content.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/content.c.o.requires

CMakeFiles/gflib.dir/content.c.o.provides: CMakeFiles/gflib.dir/content.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/content.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/content.c.o.provides

CMakeFiles/gflib.dir/content.c.o.provides.build: CMakeFiles/gflib.dir/content.c.o


CMakeFiles/gflib.dir/gfclient.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/gfclient.c.o: ../gfclient.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gflib.dir/gfclient.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/gfclient.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient.c

CMakeFiles/gflib.dir/gfclient.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/gfclient.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient.c > CMakeFiles/gflib.dir/gfclient.c.i

CMakeFiles/gflib.dir/gfclient.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/gfclient.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient.c -o CMakeFiles/gflib.dir/gfclient.c.s

CMakeFiles/gflib.dir/gfclient.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/gfclient.c.o.requires

CMakeFiles/gflib.dir/gfclient.c.o.provides: CMakeFiles/gflib.dir/gfclient.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/gfclient.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/gfclient.c.o.provides

CMakeFiles/gflib.dir/gfclient.c.o.provides.build: CMakeFiles/gflib.dir/gfclient.c.o


CMakeFiles/gflib.dir/gfclient_download.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/gfclient_download.c.o: ../gfclient_download.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gflib.dir/gfclient_download.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/gfclient_download.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient_download.c

CMakeFiles/gflib.dir/gfclient_download.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/gfclient_download.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient_download.c > CMakeFiles/gflib.dir/gfclient_download.c.i

CMakeFiles/gflib.dir/gfclient_download.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/gfclient_download.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfclient_download.c -o CMakeFiles/gflib.dir/gfclient_download.c.s

CMakeFiles/gflib.dir/gfclient_download.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/gfclient_download.c.o.requires

CMakeFiles/gflib.dir/gfclient_download.c.o.provides: CMakeFiles/gflib.dir/gfclient_download.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/gfclient_download.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/gfclient_download.c.o.provides

CMakeFiles/gflib.dir/gfclient_download.c.o.provides.build: CMakeFiles/gflib.dir/gfclient_download.c.o


CMakeFiles/gflib.dir/gfserver.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/gfserver.c.o: ../gfserver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/gflib.dir/gfserver.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/gfserver.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver.c

CMakeFiles/gflib.dir/gfserver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/gfserver.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver.c > CMakeFiles/gflib.dir/gfserver.c.i

CMakeFiles/gflib.dir/gfserver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/gfserver.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver.c -o CMakeFiles/gflib.dir/gfserver.c.s

CMakeFiles/gflib.dir/gfserver.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/gfserver.c.o.requires

CMakeFiles/gflib.dir/gfserver.c.o.provides: CMakeFiles/gflib.dir/gfserver.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/gfserver.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/gfserver.c.o.provides

CMakeFiles/gflib.dir/gfserver.c.o.provides.build: CMakeFiles/gflib.dir/gfserver.c.o


CMakeFiles/gflib.dir/gfserver_main.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/gfserver_main.c.o: ../gfserver_main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gflib.dir/gfserver_main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/gfserver_main.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver_main.c

CMakeFiles/gflib.dir/gfserver_main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/gfserver_main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver_main.c > CMakeFiles/gflib.dir/gfserver_main.c.i

CMakeFiles/gflib.dir/gfserver_main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/gfserver_main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/gfserver_main.c -o CMakeFiles/gflib.dir/gfserver_main.c.s

CMakeFiles/gflib.dir/gfserver_main.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/gfserver_main.c.o.requires

CMakeFiles/gflib.dir/gfserver_main.c.o.provides: CMakeFiles/gflib.dir/gfserver_main.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/gfserver_main.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/gfserver_main.c.o.provides

CMakeFiles/gflib.dir/gfserver_main.c.o.provides.build: CMakeFiles/gflib.dir/gfserver_main.c.o


CMakeFiles/gflib.dir/workload.c.o: CMakeFiles/gflib.dir/flags.make
CMakeFiles/gflib.dir/workload.c.o: ../workload.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/gflib.dir/workload.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gflib.dir/workload.c.o   -c /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/workload.c

CMakeFiles/gflib.dir/workload.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gflib.dir/workload.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/workload.c > CMakeFiles/gflib.dir/workload.c.i

CMakeFiles/gflib.dir/workload.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gflib.dir/workload.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/workload.c -o CMakeFiles/gflib.dir/workload.c.s

CMakeFiles/gflib.dir/workload.c.o.requires:

.PHONY : CMakeFiles/gflib.dir/workload.c.o.requires

CMakeFiles/gflib.dir/workload.c.o.provides: CMakeFiles/gflib.dir/workload.c.o.requires
	$(MAKE) -f CMakeFiles/gflib.dir/build.make CMakeFiles/gflib.dir/workload.c.o.provides.build
.PHONY : CMakeFiles/gflib.dir/workload.c.o.provides

CMakeFiles/gflib.dir/workload.c.o.provides.build: CMakeFiles/gflib.dir/workload.c.o


# Object files for target gflib
gflib_OBJECTS = \
"CMakeFiles/gflib.dir/content.c.o" \
"CMakeFiles/gflib.dir/gfclient.c.o" \
"CMakeFiles/gflib.dir/gfclient_download.c.o" \
"CMakeFiles/gflib.dir/gfserver.c.o" \
"CMakeFiles/gflib.dir/gfserver_main.c.o" \
"CMakeFiles/gflib.dir/workload.c.o"

# External object files for target gflib
gflib_EXTERNAL_OBJECTS = \
"/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/handler.o" \
"/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/handler_noasan.o"

gflib: CMakeFiles/gflib.dir/content.c.o
gflib: CMakeFiles/gflib.dir/gfclient.c.o
gflib: CMakeFiles/gflib.dir/gfclient_download.c.o
gflib: CMakeFiles/gflib.dir/gfserver.c.o
gflib: CMakeFiles/gflib.dir/gfserver_main.c.o
gflib: CMakeFiles/gflib.dir/workload.c.o
gflib: ../handler.o
gflib: ../handler_noasan.o
gflib: CMakeFiles/gflib.dir/build.make
gflib: CMakeFiles/gflib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable gflib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gflib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gflib.dir/build: gflib

.PHONY : CMakeFiles/gflib.dir/build

CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/content.c.o.requires
CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/gfclient.c.o.requires
CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/gfclient_download.c.o.requires
CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/gfserver.c.o.requires
CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/gfserver_main.c.o.requires
CMakeFiles/gflib.dir/requires: CMakeFiles/gflib.dir/workload.c.o.requires

.PHONY : CMakeFiles/gflib.dir/requires

CMakeFiles/gflib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gflib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gflib.dir/clean

CMakeFiles/gflib.dir/depend:
	cd /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug /Users/abhisheksurya/CS6200_GIOS/gios-spr-2018-pr1/gflib/cmake-build-debug/CMakeFiles/gflib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gflib.dir/depend

