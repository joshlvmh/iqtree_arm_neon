# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /sto2/sw/tools/cmake/3.14.1/bin/cmake

# The command to remove a file.
RM = /sto2/sw/tools/cmake/3.14.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE

# Include any dependencies generated for this target.
include lbfgsb/CMakeFiles/lbfgsb.dir/depend.make

# Include the progress variables for this target.
include lbfgsb/CMakeFiles/lbfgsb.dir/progress.make

# Include the compile flags for this target's objects.
include lbfgsb/CMakeFiles/lbfgsb.dir/flags.make

lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o: lbfgsb/CMakeFiles/lbfgsb.dir/flags.make
lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o: lbfgsb/lbfgsb_new.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o"
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && /home/jm17923/Software/arm/compiler/20.2/gcc-9.3.0_Generic-AArch64_SLES-12_aarch64-linux/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o -c /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb/lbfgsb_new.cpp

lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.i"
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && /home/jm17923/Software/arm/compiler/20.2/gcc-9.3.0_Generic-AArch64_SLES-12_aarch64-linux/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb/lbfgsb_new.cpp > CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.i

lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.s"
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && /home/jm17923/Software/arm/compiler/20.2/gcc-9.3.0_Generic-AArch64_SLES-12_aarch64-linux/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb/lbfgsb_new.cpp -o CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.s

# Object files for target lbfgsb
lbfgsb_OBJECTS = \
"CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o"

# External object files for target lbfgsb
lbfgsb_EXTERNAL_OBJECTS =

lbfgsb/liblbfgsb.a: lbfgsb/CMakeFiles/lbfgsb.dir/lbfgsb_new.cpp.o
lbfgsb/liblbfgsb.a: lbfgsb/CMakeFiles/lbfgsb.dir/build.make
lbfgsb/liblbfgsb.a: lbfgsb/CMakeFiles/lbfgsb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblbfgsb.a"
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && $(CMAKE_COMMAND) -P CMakeFiles/lbfgsb.dir/cmake_clean_target.cmake
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lbfgsb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lbfgsb/CMakeFiles/lbfgsb.dir/build: lbfgsb/liblbfgsb.a

.PHONY : lbfgsb/CMakeFiles/lbfgsb.dir/build

lbfgsb/CMakeFiles/lbfgsb.dir/clean:
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb && $(CMAKE_COMMAND) -P CMakeFiles/lbfgsb.dir/cmake_clean.cmake
.PHONY : lbfgsb/CMakeFiles/lbfgsb.dir/clean

lbfgsb/CMakeFiles/lbfgsb.dir/depend:
	cd /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb /home/jm17923/acrc_internship/summer20/iqtree/IQ-TREE/lbfgsb/CMakeFiles/lbfgsb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lbfgsb/CMakeFiles/lbfgsb.dir/depend
