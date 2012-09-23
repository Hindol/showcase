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
