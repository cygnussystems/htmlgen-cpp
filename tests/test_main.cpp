/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

// Enable memory leak detection for MSVC Debug builds
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <catch2/catch_session.hpp>

int main(int argc, char* argv[]) {
#ifdef _MSC_VER
    // Enable memory leak detection on program exit (Debug builds only)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    return Catch::Session().run(argc, argv);
}

/*
  How to see leak reports:
  When you run the tests in Visual Studio or CLion (Debug
  build), if there are any memory leaks, you'll see output like:
  Detected memory leaks!
  Dumping objects ->
  {142} normal block at 0x00000123456789AB, 64 bytes long.
   Data: <                > CD CD CD CD CD CD CD CD
  Object dump complete.
 */