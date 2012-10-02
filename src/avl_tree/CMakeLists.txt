add_library( avl_tree STATIC avl_tree.h )
set_target_properties( avl_tree PROPERTIES LINKER_LANGUAGE CXX )

# CPack
install(
	FILES avl_tree.h
	DESTINATION include/avl_tree
	COMPONENT avl_tree
)
