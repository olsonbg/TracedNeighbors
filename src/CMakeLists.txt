ADD_EXECUTABLE(TracedNeighbors TracedNeighbors.cpp ReadData.cpp
               SimpleMath.cpp Print.cpp main.cpp)

# Link the executable to a library.
FIND_PACKAGE( Boost REQUIRED COMPONENTS iostreams REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )
TARGET_LINK_LIBRARIES(TracedNeighbors ${Boost_LIBRARIES} )

#
# If I use bzip2 for zlib, I have to put the corresponding
# dlls on windows.
#
if( NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
	FIND_PACKAGE( BZip2 )
	IF( BZIP2_FOUND )
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_BZIP2")
		INCLUDE_DIRECTORIES( ${BZIP2_INCLUDE_DIR} )
		TARGET_LINK_LIBRARIES(TracedNeighbors ${BZIP2_LIBRARIES} )
	endif()

	FIND_PACKAGE( ZLIB )
	IF( ZLIB_FOUND )
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_ZLIB")
		INCLUDE_DIRECTORIES( ${ZLIB_INCLUDE_DIRS} )
		TARGET_LINK_LIBRARIES(TracedNeighbors ${ZLIB_LIBRARIES} )
	endif()

	# Boost does not support lzma (XZ), so not going to use this.
	#	FIND_PACKAGE( LibLZMA )
	#IF( LIBLZMA_FOUND )
	#	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUSE_XZ")
	#	INCLUDE_DIRECTORIES( ${LIBLZMA_INCLUDE_DIRS} )
	#	TARGET_LINK_LIBRARIES(TracedNeighbors ${LIBLZMA_LIBRARIES} )
	#endif()
endif()

