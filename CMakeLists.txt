cmake_minimum_required(VERSION 3.20)
project(Marvus-in-Cpp LANGUAGES C CXX)

#
# C++ version
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Warnings
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -pedantic)
endif()

#
# Optimization
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
	set(CMAKE_C_FLAGS_RELEASE "-O3")
	#
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
	set(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")
endif()

#
# ConsoleLib
#
set(CONSOLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ConsoleLib)

# Create an IMPORTED target for the .a file
add_library(ConsoleLib STATIC IMPORTED)

# Point the IMPORTED target to the actual file
# Windows binary is compiled using mingw g++
if (WIN32)
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/windows/libConsoleLib.a
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR})
else()
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/linux/libConsoleLib.a
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR})
endif()

#
# GTK
#
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

#
# Boost
#
set(boost_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/boost_1_89_0)
set(boost_INCLUDE_DIRS ${boost_ROOT})
include_directories(${boost_INCLUDE_DIRS})

#
# Marvus-in-Cpp
#
file(MAKE_DIRECTORY build)

file(GLOB_RECURSE APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

find_program(GLIB_COMPILE_RESOURCES glib-compile-resources REQUIRED)

set(RESOURCE_XML ${CMAKE_CURRENT_SOURCE_DIR}/assets/resources.gresource.xml)
set(RESOURCE_C   ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

add_custom_command(
    OUTPUT ${RESOURCE_C}
    COMMAND ${GLIB_COMPILE_RESOURCES}
	    --generate-source
	    --target=${RESOURCE_C}
	    --c-name marvus
	    --sourcedir=${CMAKE_CURRENT_SOURCE_DIR}/assets
	    ${RESOURCE_XML}
    DEPENDS ${RESOURCE_XML}
	    ${CMAKE_CURRENT_SOURCE_DIR}/assets/hicolor/48x48/apps/marvus.png)

add_executable(Marvus ${APP_SOURCES} ${RESOURCE_C})


# Link everything

target_sources(Marvus PRIVATE ${RESOURCE_C})

target_include_directories(Marvus PRIVATE ${CONSOLE_LIB_DIR}/inc)
target_include_directories(Marvus PRIVATE ${boost_INCLUDE_DIRS})
if (WIN32)
	target_link_libraries(Marvus PRIVATE ws2_32)
endif()
target_include_directories(Marvus PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(Marvus PRIVATE ${GTK_LIBRARY_DIRS})
target_link_libraries(Marvus PRIVATE ${GTK_LIBRARIES})
target_compile_options(Marvus PRIVATE ${GTK_CFLAGS_OTHER})


target_link_libraries(Marvus PRIVATE ConsoleLib)

# Copy assets folder into build directory
file(COPY ${CMAKE_SOURCE_DIR}/sql DESTINATION ${CMAKE_BINARY_DIR})

#
# Documentation
#

# Path to LaTeX source folder
set(LATEX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/latex-doc)
set(MAIN_TEX Marvus-in-Cpp.tex)
set(OUTPUT_PDF ${CMAKE_CURRENT_BINARY_DIR}/Marvus-in-Cpp.pdf)

# Custom target to build docs
add_custom_target(docs
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} makeglossaries Marvus-in-Cpp
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMAND ${CMAKE_COMMAND} -E chdir ${LATEX_DIR} lualatex ${MAIN_TEX}
	COMMENT "Building PDF documentation with lualatex and makeglossaries"
)
