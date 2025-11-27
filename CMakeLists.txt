cmake_minimum_required(VERSION 3.20)
project(MyApp LANGUAGES C CXX)

# --- C++ Standard ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Default build type ---
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# --- Warnings ---
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# --- Optimization ---
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# My static libraries

set(CONSOLE_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/ConsoleLib)

# Create an IMPORTED target for the .a file
add_library(ConsoleLib STATIC IMPORTED)

# Point the IMPORTED target to the actual file
if (WIN32)
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/libConsoleLib.lib
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
else()
	set_target_properties(ConsoleLib PROPERTIES
	IMPORTED_LOCATION ${CONSOLE_LIB_DIR}/libConsoleLib.a
	INTERFACE_INCLUDE_DIRECTORIES ${CONSOLE_LIB_DIR}/inc)
endif()


# WxWidgets

if (WIN32)
	# Windows: use built wxWidgets (must be built beforehand)
	set(wxWidgets_ROOT_DIR "C:/wxWidgets")  # <-- change to your path
	set(wxWidgets_LIB_DIR  "C:/wxWidgets/lib/vc_x64_dll") # if using dll/debug libs
else()
	find_package(wxWidgets REQUIRED COMPONENTS core base)
endif() 

include(${wxWidgets_USE_FILE})

# SQLite

if (WIN32)
	#
	# Windows: using sqlite3.lib + sqlite3.dll from downloaded package
	#
	set(SQLITE3_INCLUDE_DIR "C:/sqlite")       # <-- change if needed
	set(SQLITE3_LIBRARY     "C:/sqlite/sqlite3.lib")
else()
	#
	# Linux: system-provided SQLite
	#
	find_package(SQLite3 REQUIRED)
endif()

# Marvus-in-Cpp
file(MAKE_DIRECTORY build)

file(GLOB_RECURSE APP_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(Marvus ${APP_SOURCES})

# Link everything
target_include_directories(Marvus PRIVATE ${CONSOLE_LIB_DIR}/inc)

target_link_libraries(Marvus PRIVATE ConsoleLib)

# wxWidgets
target_link_libraries(Marvus PRIVATE ${wxWidgets_LIBRARIES})

# SQLite
if (WIN32)
	target_include_directories(Marvus PRIVATE ${SQLITE3_INCLUDE_DIR})
	target_link_libraries(Marvus PRIVATE ${SQLITE3_LIBRARY})
else()
	target_link_libraries(Marvus PRIVATE SQLite::SQLite3)
endif()

# Copy assets folder into build directory
file(COPY ${CMAKE_SOURCE_DIR}/sql DESTINATION ${CMAKE_BINARY_DIR})


# Documentation

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
