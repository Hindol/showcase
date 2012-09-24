add_executable( binary_heap_test binary_heap_test.cpp stdafx.cpp $<TARGET_OBJECTS:gtest_main> $<TARGET_OBJECTS:gtest> )
add_test( NAME "Binary Haep Test" COMMAND binary_heap_test )

# Precompiled headers
IF( MSVC )
	set_target_properties( binary_heap_test PROPERTIES COMPILE_FLAGS "/Yustdafx.h" )
	set_source_files_properties( stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h" )
ENDIF( MSVC )