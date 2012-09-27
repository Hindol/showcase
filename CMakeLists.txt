cmake_minimum_required( VERSION 2.8 )
project( showcase )

# Project-wide configurations
include_directories( ${CMAKE_SOURCE_DIR}/src )

IF( WIN32 )
    include_directories( "C:\\Program Files\\boost\\boost_1_51" )
ELSEIF( UNIX )
    include_directories( "/home/hindol/Workspace/lib/boost/include" )
ENDIF( WIN32 )

# Modules
add_subdirectory( src/binary_heap )
add_subdirectory( src/binary_tree )
add_subdirectory( src/binary_search_tree )

# GTest
IF( MSVC_VERSION EQUAL 1700 )
	add_definitions( -D_VARIADIC_MAX=10 )
ENDIF( MSVC_VERSION EQUAL 1700 )

include_directories( ${CMAKE_SOURCE_DIR}/contrib/gtest-1.6.0/include )

add_library( gtest OBJECT ${CMAKE_SOURCE_DIR}/contrib/gtest-1.6.0/src/gtest-all.cc )
set_property(
	TARGET gtest PROPERTY INCLUDE_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/contrib/gtest-1.6.0
    ${CMAKE_SOURCE_DIR}/contrib/gtest-1.6.0/include
)

add_library( gtest_main OBJECT ${CMAKE_SOURCE_DIR}/contrib/gtest-1.6.0/src/gtest_main.cc )

# All tests
add_subdirectory( tests )

# CPack
IF( WIN32 )
	set( CPACK_GENERATOR "NSIS" )
ELSEIF( UNIX )
    set( CPACK_GENERATOR "DEB" )
	set( CPACK_PACKAGING_INSTALL_PREFIX /opt )
ENDIF( WIN32 )

set( CPACK_PACKAGE_VERSION_MAJOR "1" )
set( CPACK_PACKAGE_VERSION_MINOR "0" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )
set( CPACK_PACKAGE_DESCRIPTION "Binary tree C++ headers." )
set( CPACK_PACKAGE_CONTACT "Hindol Adhya <hindol.adhya@gmail.com>" )
set( CPACK_PACKAGE_INSTALL_DIRECTORY "Libraries" )

set( CPACK_COMPONENTS_ALL binary_heap binary_tree )
set( CPACK_COMPONENT_BINARY_HEAP_DISPLAY_NAME "Binary Heap" )
set( CPACK_COMPONENT_BINARY_TREE_DISPLAY_NAME "Binary Tree" )

include( CPack )
