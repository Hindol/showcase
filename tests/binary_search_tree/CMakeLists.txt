IF( UNIX )
    find_package( Threads REQUIRED )
    set( LINUX_EXTRA_LIBS "${CMAKE_THREAD_LIBS_INIT}" )
ENDIF( UNIX )

add_executable(
	binary_search_tree_test
	binary_search_tree_test.cpp
	stdafx.h
	stdafx.cpp
	$<TARGET_OBJECTS:gtest_main>
	$<TARGET_OBJECTS:gtest>
)
target_link_libraries( binary_search_tree_test ${LINUX_EXTRA_LIBS} )
add_test( NAME "Binary Search Tree Test" COMMAND binary_search_tree_test )

# Precompiled headers
IF( MSVC )
	set_target_properties( binary_search_tree_test PROPERTIES COMPILE_FLAGS "/Yustdafx.h" )
	set_source_files_properties( stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h" )
ENDIF( MSVC )
