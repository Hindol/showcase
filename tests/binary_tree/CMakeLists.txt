add_executable(
	binary_tree_test
	binary_tree_test.cpp
	stdafx.h
	stdafx.cpp
	$<TARGET_OBJECTS:gtest_main>
	$<TARGET_OBJECTS:gtest>
)
add_test( NAME "Binary Tree Test" COMMAND binary_tree_test )

# Precompiled headers
IF( MSVC )
	set_target_properties( binary_tree_test PROPERTIES COMPILE_FLAGS "/Yustdafx.h" )
	set_source_files_properties( stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h" )
ENDIF( MSVC )