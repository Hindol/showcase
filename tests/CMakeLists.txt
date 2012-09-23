include_directories( ../src/binary_heap )

add_executable( binary_heap_test binary_heap_test.cpp $<TARGET_OBJECTS:gtest_main> $<TARGET_OBJECTS:gtest> )
add_test( NAME "Binary Haep Test" COMMAND binary_heap_test )