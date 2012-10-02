add_library(
	binary_search_tree STATIC
	binary_search_tree.h
)
set_target_properties( binary_search_tree PROPERTIES LINKER_LANGUAGE CXX )

# CPack
install(
	FILES binary_search_tree.h
	DESTINATION include/binary_search_tree
	COMPONENT binary_search_tree
)
