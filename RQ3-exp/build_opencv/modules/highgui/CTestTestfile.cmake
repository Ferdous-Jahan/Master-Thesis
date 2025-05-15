# CMake generated Testfile for 
# Source directory: /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/modules/highgui
# Build directory: /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/modules/highgui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(opencv_test_highgui "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/bin/opencv_test_highgui" "--gtest_output=xml:opencv_test_highgui.xml")
set_tests_properties(opencv_test_highgui PROPERTIES  LABELS "Main;opencv_highgui;Accuracy" WORKING_DIRECTORY "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/test-reports/accuracy" _BACKTRACE_TRIPLES "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/cmake/OpenCVUtils.cmake;1799;add_test;/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/cmake/OpenCVModule.cmake;1365;ocv_add_test_from_target;/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/modules/highgui/CMakeLists.txt;311;ocv_add_accuracy_tests;/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/modules/highgui/CMakeLists.txt;0;")
