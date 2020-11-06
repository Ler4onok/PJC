# CMake generated Testfile for 
# Source directory: C:/Users/Ler4onok/Desktop/sym/sym
# Build directory: C:/Users/Ler4onok/Desktop/sym/sym/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(direct "C:/Users/Ler4onok/Desktop/sym/sym/cmake-build-debug/tests-direct.exe")
add_test(runner-direct "C:/Users/Ler4onok/Desktop/sym/sym/cmake-build-debug/tests-runner-direct.exe")
add_test(runner-subprocess "C:/Users/Ler4onok/Desktop/sym/sym/cmake-build-debug/tests-runner-subprocess.exe")
set_tests_properties(runner-subprocess PROPERTIES  ENVIRONMENT "TEST_CMD=\"C:/Users/Ler4onok/Desktop/sym/sym/cmake-build-debug/symcalc.exe\"")
