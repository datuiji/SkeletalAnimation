#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build
  make -f /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build
  make -f /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build
  make -f /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build
  make -f /Users/tuijida/Desktop/OpenGL_Course/Hw3/SkeletalAnimation/build/CMakeScripts/ReRunCMake.make
fi

