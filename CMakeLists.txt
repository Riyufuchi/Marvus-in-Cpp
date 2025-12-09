cmake_minimum_required(VERSION 3.20)
project(Marvus-in-Cpp LANGUAGES C CXX)

#
# C++ version
#
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
# Default build type
#
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

#
# Warnings
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_definitions(NOMINMAX)
	add_compile_options(/W4)
endif()

#
# Optimization
#
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2")
endif()

#
# My static libraries
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
# WxWidgets
#

if (WIN32)
	set(wx_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/wxWidgets)

	set(wxWidgets_INCLUDE_DIRS ${wx_ROOT})
	set(wxWidgets_LIB_DIR ${wx_ROOT}/vc_x64_lib)

	# Collect ALL .lib files
	file(GLOB wxWidgets_LIBRARIES "${wxWidgets_LIB_DIR}/*.lib")

	# Include wxWidgets headers
	include_directories(${wxWidgets_INCLUDE_DIRS})
else()
	find_package(wxWidgets REQUIRED COMPONENTS core base)
	include(${wxWidgets_USE_FILE})
endif() 

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


if (WIN32)
	add_executable(Marvus WIN32
		${APP_SOURCES} 
		src/MainSource.cpp
)

	# Link manifest
	set_target_properties(Marvus PROPERTIES
		WIN32_EXECUTABLE TRUE
	LINK_FLAGS "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\""
	# Optional: explicitly specify manifest file
	RESOURCE app.manifest
    )
else()
	add_executable(Marvus ${APP_SOURCES})
endif() 


# Link everything
target_include_directories(Marvus PRIVATE ${CONSOLE_LIB_DIR}/inc)
target_include_directories(Marvus PRIVATE ${boost_INCLUDE_DIRS})

target_link_libraries(Marvus PRIVATE ConsoleLib)
target_link_libraries(Marvus PRIVATE ${wxWidgets_LIBRARIES})
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
