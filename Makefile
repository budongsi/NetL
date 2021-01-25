# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\cygwin64\home\traceur\projects\NetL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\cygwin64\home\traceur\projects\NetL

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake\bin\cmake-gui.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\cygwin64\home\traceur\projects\NetL\CMakeFiles C:\cygwin64\home\traceur\projects\NetL\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\cygwin64\home\traceur\projects\NetL\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\main.dir\build.make CMakeFiles/main.dir/build
.PHONY : main/fast

#=============================================================================
# Target rules for targets named md_echo_server

# Build rule for target.
md_echo_server: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 md_echo_server
.PHONY : md_echo_server

# fast build rule for target.
md_echo_server/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_server.dir\build.make CMakeFiles/md_echo_server.dir/build
.PHONY : md_echo_server/fast

#=============================================================================
# Target rules for targets named md_echo_client

# Build rule for target.
md_echo_client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 md_echo_client
.PHONY : md_echo_client

# fast build rule for target.
md_echo_client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_client.dir\build.make CMakeFiles/md_echo_client.dir/build
.PHONY : md_echo_client/fast

main.obj: main.cpp.obj

.PHONY : main.obj

# target to build an object file
main.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\main.dir\build.make CMakeFiles/main.dir/main.cpp.obj
.PHONY : main.cpp.obj

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\main.dir\build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\main.dir\build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

test/md_echo_client.obj: test/md_echo_client.cpp.obj

.PHONY : test/md_echo_client.obj

# target to build an object file
test/md_echo_client.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_client.dir\build.make CMakeFiles/md_echo_client.dir/test/md_echo_client.cpp.obj
.PHONY : test/md_echo_client.cpp.obj

test/md_echo_client.i: test/md_echo_client.cpp.i

.PHONY : test/md_echo_client.i

# target to preprocess a source file
test/md_echo_client.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_client.dir\build.make CMakeFiles/md_echo_client.dir/test/md_echo_client.cpp.i
.PHONY : test/md_echo_client.cpp.i

test/md_echo_client.s: test/md_echo_client.cpp.s

.PHONY : test/md_echo_client.s

# target to generate assembly for a file
test/md_echo_client.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_client.dir\build.make CMakeFiles/md_echo_client.dir/test/md_echo_client.cpp.s
.PHONY : test/md_echo_client.cpp.s

test/md_echo_server.obj: test/md_echo_server.cpp.obj

.PHONY : test/md_echo_server.obj

# target to build an object file
test/md_echo_server.cpp.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_server.dir\build.make CMakeFiles/md_echo_server.dir/test/md_echo_server.cpp.obj
.PHONY : test/md_echo_server.cpp.obj

test/md_echo_server.i: test/md_echo_server.cpp.i

.PHONY : test/md_echo_server.i

# target to preprocess a source file
test/md_echo_server.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_server.dir\build.make CMakeFiles/md_echo_server.dir/test/md_echo_server.cpp.i
.PHONY : test/md_echo_server.cpp.i

test/md_echo_server.s: test/md_echo_server.cpp.s

.PHONY : test/md_echo_server.s

# target to generate assembly for a file
test/md_echo_server.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\md_echo_server.dir\build.make CMakeFiles/md_echo_server.dir/test/md_echo_server.cpp.s
.PHONY : test/md_echo_server.cpp.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... main
	@echo ... md_echo_client
	@echo ... md_echo_server
	@echo ... main.obj
	@echo ... main.i
	@echo ... main.s
	@echo ... test/md_echo_client.obj
	@echo ... test/md_echo_client.i
	@echo ... test/md_echo_client.s
	@echo ... test/md_echo_server.obj
	@echo ... test/md_echo_server.i
	@echo ... test/md_echo_server.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system

