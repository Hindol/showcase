add_library(
	binary_search_tree STATIC
	binary_search_tree.h
	bits/binary_search_tree_node.h
	bits/binary_search_tree_iterator.h
)
set_target_properties( binary_search_tree PROPERTIES LINKER_LANGUAGE CXX )

# CPack
install(
	FILES binary_search_tree.h
	DESTINATION include/binary_search_tree
	COMPONENT binary_search_tree
)

install(
	FILES bits/binary_search_tree_node.h bits/binary_search_tree_iterator.h
	DESTINATION include/binary_search_tree/bits
	COMPONENT binary_search_tree
)
