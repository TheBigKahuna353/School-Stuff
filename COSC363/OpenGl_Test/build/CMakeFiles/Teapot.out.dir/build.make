# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build"

# Include any dependencies generated for this target.
include CMakeFiles/Teapot.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Teapot.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Teapot.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Teapot.out.dir/flags.make

CMakeFiles/Teapot.out.dir/Teapot.cpp.obj: CMakeFiles/Teapot.out.dir/flags.make
CMakeFiles/Teapot.out.dir/Teapot.cpp.obj: C:/Users/jorda/Documents/GitHub/School\ Stuff/COSC363/OpenGl_Test/Teapot.cpp
CMakeFiles/Teapot.out.dir/Teapot.cpp.obj: CMakeFiles/Teapot.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Teapot.out.dir/Teapot.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Teapot.out.dir/Teapot.cpp.obj -MF CMakeFiles\Teapot.out.dir\Teapot.cpp.obj.d -o CMakeFiles\Teapot.out.dir\Teapot.cpp.obj -c "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Teapot.cpp"

CMakeFiles/Teapot.out.dir/Teapot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Teapot.out.dir/Teapot.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Teapot.cpp" > CMakeFiles\Teapot.out.dir\Teapot.cpp.i

CMakeFiles/Teapot.out.dir/Teapot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Teapot.out.dir/Teapot.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Teapot.cpp" -o CMakeFiles\Teapot.out.dir\Teapot.cpp.s

# Object files for target Teapot.out
Teapot_out_OBJECTS = \
"CMakeFiles/Teapot.out.dir/Teapot.cpp.obj"

# External object files for target Teapot.out
Teapot_out_EXTERNAL_OBJECTS =

Teapot.out.exe: CMakeFiles/Teapot.out.dir/Teapot.cpp.obj
Teapot.out.exe: CMakeFiles/Teapot.out.dir/build.make
Teapot.out.exe: CMakeFiles/Teapot.out.dir/linkLibs.rsp
Teapot.out.exe: CMakeFiles/Teapot.out.dir/objects1.rsp
Teapot.out.exe: CMakeFiles/Teapot.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Teapot.out.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Teapot.out.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Teapot.out.dir/build: Teapot.out.exe
.PHONY : CMakeFiles/Teapot.out.dir/build

CMakeFiles/Teapot.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Teapot.out.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Teapot.out.dir/clean

CMakeFiles/Teapot.out.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles\Teapot.out.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Teapot.out.dir/depend

