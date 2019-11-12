cmake_minimum_required(VERSION 3.0.0)
project(glib-playground VERSION 0.1.0)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_search_module(LIBSOUP REQUIRED libsoup-2.4)

message(STATUS "LIBSOUP_INCLUDE_DIRS='${LIBSOUP_INCLUDE_DIRS}'")
message(STATUS "LIBSOUP_LIBRARY_DIRS='${LIBSOUP_LIBRARY_DIRS}'")

include_directories (${GLIB_INCLUDE_DIRS})
link_directories (${GLIB_LIBRARY_DIRS})
add_executable (glib-playground main.c)
add_definitions (${GLIB_CFLAGS_OTHER})
target_link_libraries (glib-playground ${GLIB_LIBRARIES})