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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv

# Include any dependencies generated for this target.
include samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/compiler_depend.make

# Include the progress variables for this target.
include samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/progress.make

# Include the compile flags for this target's objects.
include samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/flags.make

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/codegen:
.PHONY : samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/codegen

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o: samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/flags.make
samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o: /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/samples/cpp/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp
samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o: samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o"
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o -MF CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o.d -o CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o -c /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/samples/cpp/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.i"
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/samples/cpp/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp > CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.i

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.s"
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/samples/cpp/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp -o CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.s

# Object files for target example_tutorial_porting_anisotropic_image_segmentation_gapi
example_tutorial_porting_anisotropic_image_segmentation_gapi_OBJECTS = \
"CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o"

# External object files for target example_tutorial_porting_anisotropic_image_segmentation_gapi
example_tutorial_porting_anisotropic_image_segmentation_gapi_EXTERNAL_OBJECTS =

bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/tutorial_code/gapi/porting_anisotropic_image_segmentation/porting_anisotropic_image_segmentation_gapi.cpp.o
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/build.make
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_gapi.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_highgui.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_ml.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_objdetect.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_photo.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_stitching.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_video.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_videoio.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_imgcodecs.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_calib3d.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_features2d.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_flann.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_dnn.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_imgproc.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: lib/libopencv_core.4.12.0.dylib
bin/example_tutorial_porting_anisotropic_image_segmentation_gapi: samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/example_tutorial_porting_anisotropic_image_segmentation_gapi"
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/build: bin/example_tutorial_porting_anisotropic_image_segmentation_gapi
.PHONY : samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/build

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/clean:
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp && $(CMAKE_COMMAND) -P CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/cmake_clean.cmake
.PHONY : samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/clean

samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/depend:
	cd /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/samples/cpp /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : samples/cpp/CMakeFiles/example_tutorial_porting_anisotropic_image_segmentation_gapi.dir/depend

