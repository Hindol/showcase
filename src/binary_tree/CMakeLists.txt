add_library(
	binary_tree STATIC
	binary_tree.h
	bits/binary_tree_node.h
	bits/binary_tree_iterator.h
)
set_target_properties( binary_tree PROPERTIES LINKER_LANGUAGE CXX )

# CPack
install(
	FILES binary_tree.h
	DESTINATION include/binary_tree
	COMPONENT binary_tree
)

install(
	FILES bits/binary_tree_node.h bits/binary_tree_iterator.h
	DESTINATION include/binary_tree/bits
	COMPONENT binary_tree
)
