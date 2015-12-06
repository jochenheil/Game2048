cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME game2048)
project(${PROJECT_NAME})

# Turn off tests with "cmake -Dbuild_test=OFF".
option(build_test "Build all tests." ON)
# Turn off documentation build with "cmake -Dbuild_doc=OFF"
option(build_doc "Build html api documentation with Doxygen" ON)

# Set gcc compiler options.
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11 -g -pedantic)
endif()

add_library(board board.cpp helper.cpp)
add_executable(game2048 main.cpp)
target_link_libraries(game2048 board)
install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} DESTINATION bin)

# Tests.
if(build_test)
  enable_testing()
  find_package(GTest REQUIRED)
  add_executable(runtests tests.cpp)
  target_link_libraries(runtests gtest gtest_main board)
  add_test(NAME testLineObject COMMAND runtests)
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} DESTINATION tests)
endif()

if(build_doc)
    find_package(Doxygen)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()