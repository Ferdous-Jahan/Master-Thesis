# Install script for directory: /Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libs" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv4/haarcascades" TYPE FILE FILES
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_eye.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalcatface.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalcatface_extended.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalface_alt.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_frontalface_default.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_fullbody.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_lefteye_2splits.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_license_plate_rus_16stages.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_lowerbody.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_profileface.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_righteye_2splits.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_russian_plate_number.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_smile.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/haarcascades/haarcascade_upperbody.xml"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libs" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv4/lbpcascades" TYPE FILE FILES
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/lbpcascades/lbpcascade_frontalcatface.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/lbpcascades/lbpcascade_frontalface.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/lbpcascades/lbpcascade_frontalface_improved.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/lbpcascades/lbpcascade_profileface.xml"
    "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/data/lbpcascades/lbpcascade_silverware.xml"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/build_opencv/data/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
