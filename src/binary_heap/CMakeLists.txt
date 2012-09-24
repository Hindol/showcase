add_library( binary_heap STATIC binary_heap.h )
set_target_properties(binary_heap PROPERTIES LINKER_LANGUAGE CXX)

# CPack
install(
	FILES binary_heap.h
	DESTINATION include/binary_heap
	COMPONENT binary_heap
)
