# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/CG/CG_2025_HW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/CG/CG_2025_HW1/build

# Include any dependencies generated for this target.
include src/CMakeFiles/CG_2025_HW1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/CG_2025_HW1.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CG_2025_HW1.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CG_2025_HW1.dir/flags.make

src/CMakeFiles/CG_2025_HW1.dir/codegen:
.PHONY : src/CMakeFiles/CG_2025_HW1.dir/codegen

src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/flags.make
src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/includes_CXX.rsp
src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj: C:/CG/CG_2025_HW1/src/main.cpp
src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/CG/CG_2025_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj -MF CMakeFiles/CG_2025_HW1.dir/main.cpp.obj.d -o CMakeFiles/CG_2025_HW1.dir/main.cpp.obj -c C:/CG/CG_2025_HW1/src/main.cpp

src/CMakeFiles/CG_2025_HW1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CG_2025_HW1.dir/main.cpp.i"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/CG/CG_2025_HW1/src/main.cpp > CMakeFiles/CG_2025_HW1.dir/main.cpp.i

src/CMakeFiles/CG_2025_HW1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CG_2025_HW1.dir/main.cpp.s"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/CG/CG_2025_HW1/src/main.cpp -o CMakeFiles/CG_2025_HW1.dir/main.cpp.s

src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/flags.make
src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/includes_CXX.rsp
src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj: C:/CG/CG_2025_HW1/src/stb_image.cpp
src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj: src/CMakeFiles/CG_2025_HW1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/CG/CG_2025_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj -MF CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj.d -o CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj -c C:/CG/CG_2025_HW1/src/stb_image.cpp

src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.i"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/CG/CG_2025_HW1/src/stb_image.cpp > CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.i

src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.s"
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/CG/CG_2025_HW1/src/stb_image.cpp -o CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.s

# Object files for target CG_2025_HW1
CG_2025_HW1_OBJECTS = \
"CMakeFiles/CG_2025_HW1.dir/main.cpp.obj" \
"CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj"

# External object files for target CG_2025_HW1
CG_2025_HW1_EXTERNAL_OBJECTS =

src/CG_2025_HW1.exe: src/CMakeFiles/CG_2025_HW1.dir/main.cpp.obj
src/CG_2025_HW1.exe: src/CMakeFiles/CG_2025_HW1.dir/stb_image.cpp.obj
src/CG_2025_HW1.exe: src/CMakeFiles/CG_2025_HW1.dir/build.make
src/CG_2025_HW1.exe: extern/glfw/src/libglfw3.a
src/CG_2025_HW1.exe: extern/glm/glm/libglm.a
src/CG_2025_HW1.exe: extern/glad/libglad.a
src/CG_2025_HW1.exe: src/CMakeFiles/CG_2025_HW1.dir/linkLibs.rsp
src/CG_2025_HW1.exe: src/CMakeFiles/CG_2025_HW1.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/CG/CG_2025_HW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CG_2025_HW1.exe"
	cd C:/CG/CG_2025_HW1/build/src && "C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/CG_2025_HW1.dir/objects.a
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/ar.exe qc CMakeFiles/CG_2025_HW1.dir/objects.a @CMakeFiles/CG_2025_HW1.dir/objects1.rsp
	cd C:/CG/CG_2025_HW1/build/src && C:/w64devkit/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/CG_2025_HW1.dir/objects.a -Wl,--no-whole-archive -o CG_2025_HW1.exe -Wl,--out-implib,libCG_2025_HW1.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/CG_2025_HW1.dir/linkLibs.rsp

# Rule to build all files generated by this target.
src/CMakeFiles/CG_2025_HW1.dir/build: src/CG_2025_HW1.exe
.PHONY : src/CMakeFiles/CG_2025_HW1.dir/build

src/CMakeFiles/CG_2025_HW1.dir/clean:
	cd C:/CG/CG_2025_HW1/build/src && $(CMAKE_COMMAND) -P CMakeFiles/CG_2025_HW1.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/CG_2025_HW1.dir/clean

src/CMakeFiles/CG_2025_HW1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/CG/CG_2025_HW1 C:/CG/CG_2025_HW1/src C:/CG/CG_2025_HW1/build C:/CG/CG_2025_HW1/build/src C:/CG/CG_2025_HW1/build/src/CMakeFiles/CG_2025_HW1.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/CG_2025_HW1.dir/depend

