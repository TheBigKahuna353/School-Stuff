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
include CMakeFiles/Model3d.out.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Model3d.out.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Model3d.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Model3d.out.dir/flags.make

CMakeFiles/Model3d.out.dir/Model3D.cpp.obj: CMakeFiles/Model3d.out.dir/flags.make
CMakeFiles/Model3d.out.dir/Model3D.cpp.obj: C:/Users/jorda/Documents/GitHub/School\ Stuff/COSC363/OpenGl_Test/Model3D.cpp
CMakeFiles/Model3d.out.dir/Model3D.cpp.obj: CMakeFiles/Model3d.out.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Model3d.out.dir/Model3D.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Model3d.out.dir/Model3D.cpp.obj -MF CMakeFiles\Model3d.out.dir\Model3D.cpp.obj.d -o CMakeFiles\Model3d.out.dir\Model3D.cpp.obj -c "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Model3D.cpp"

CMakeFiles/Model3d.out.dir/Model3D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Model3d.out.dir/Model3D.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Model3D.cpp" > CMakeFiles\Model3d.out.dir\Model3D.cpp.i

CMakeFiles/Model3d.out.dir/Model3D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Model3d.out.dir/Model3D.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\Model3D.cpp" -o CMakeFiles\Model3d.out.dir\Model3D.cpp.s

# Object files for target Model3d.out
Model3d_out_OBJECTS = \
"CMakeFiles/Model3d.out.dir/Model3D.cpp.obj"

# External object files for target Model3d.out
Model3d_out_EXTERNAL_OBJECTS =

Model3d.out.exe: CMakeFiles/Model3d.out.dir/Model3D.cpp.obj
Model3d.out.exe: CMakeFiles/Model3d.out.dir/build.make
Model3d.out.exe: CMakeFiles/Model3d.out.dir/linkLibs.rsp
Model3d.out.exe: CMakeFiles/Model3d.out.dir/objects1.rsp
Model3d.out.exe: CMakeFiles/Model3d.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Model3d.out.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Model3d.out.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Model3d.out.dir/build: Model3d.out.exe
.PHONY : CMakeFiles/Model3d.out.dir/build

CMakeFiles/Model3d.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Model3d.out.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Model3d.out.dir/clean

CMakeFiles/Model3d.out.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build" "C:\Users\jorda\Documents\GitHub\School Stuff\COSC363\OpenGl_Test\build\CMakeFiles\Model3d.out.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Model3d.out.dir/depend

