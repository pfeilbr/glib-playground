cmake_minimum_required(VERSION 3.0.0)
project(glib-playground VERSION 0.1.0)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARY_DIRS})
add_executable (glib-playground main.c)
add_definitions (${GLIB_CFLAGS_OTHER})
target_link_libraries (glib-playground ${GLIB_LIBRARIES})