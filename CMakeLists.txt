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
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/W4)
endif()

#
# Other settings
#
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_definitions(NOMINMAX)
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
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
	set(CMAKE_C_FLAGS_RELEASE "/O2")
	#
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /Zi /DDEBUG")
	set(CMAKE_C_FLAGS_DEBUG "/Od /Zi /DDEBUG")
endif()

#
# ConsoleLib
#
set(CONSOLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ConsoleLib)

# Create an IMPORTED target for the .a file
add_library(ConsoleLib STATIC IMPORTED)

# Point the IMPORTED target to the actual file
if (WIN32)
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/ConsoleLib.lib
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
else()
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/libConsoleLib.a
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
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
if (WIN32)
	set(boost_LIB_DIR ${boost_ROOT}/windows)
	file(GLOB boost_LIBRARIES "${boost_LIB_DIR}/*.lib")
else()
	set(boost_LIB_DIR ${boost_ROOT}/linux)
	file(GLOB boost_LIBRARIES "${boost_LIB_DIR}/*.a")
	include_directories(${boost_INCLUDE_DIRS})
endif() 

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

target_include_directories(Marvus PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(Marvus PRIVATE ${GTK_LIBRARY_DIRS})
target_link_libraries(Marvus PRIVATE ${GTK_LIBRARIES})
target_compile_options(Marvus PRIVATE ${GTK_CFLAGS_OTHER})


target_link_libraries(Marvus PRIVATE ConsoleLib)
#target_link_libraries(Marvus PRIVATE ${wxWidgets_LIBRARIES})
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
target_link_libraries(Marvus PRIVATE ${boost_LIBRARIES})

if (WIN32)
	target_link_libraries(Marvus PRIVATE
		comctl32
		rpcrt4
		uxtheme      # recommended, not required
)
endif()

# Copy assets folder into build directory
if (WIN32)
	file(COPY ${CMAKE_SOURCE_DIR}/sql DESTINATION "${CMAKE_BINARY_DIR}/Release")
else()
	file(COPY ${CMAKE_SOURCE_DIR}/sql DESTINATION ${CMAKE_BINARY_DIR})
endif() 

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
