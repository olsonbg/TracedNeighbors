find_package(Threads REQUIRED)
set(GTEST_ROOT "/home/bgo/Projects/gtest-svn")
find_package(GTest REQUIRED)
if ( GTEST_FOUND )

	set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
	file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
	add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})

	include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)
	target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES})
	target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
	add_test(NAME test1
	         COMMAND ${PROJECT_TEST_NAME})
endif(GTEST_FOUND)


