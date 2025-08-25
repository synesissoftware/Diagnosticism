
# ######################################################################## #
# File:     /src/CMakeLists.txt
#
# Purpose:  CMake lists file for Diagnosticsm core library
#
# Created:  23rd November 2024
# Updated:  25th August 2025
#
# ######################################################################## #


# ##########################################################
# platform-specifics

if(UNIX)

	add_definitions(-DUNIX)
	add_definitions(-Dunix)
endif(UNIX)

if(WIN32)

	if(CMAKE_SIZEOF_VOID_P EQUAL 8)

		message (STATUS "Compiling for 64-bit Windows")

		add_definitions(-DWIN64)
	else()

		message (STATUS "Compiling for 32-bit Windows")

		add_definitions(-DWIN32)
	endif()
endif(WIN32)

if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))

	add_compile_options("/Zc:__cplusplus")
endif()


# ##########################################################
# target

set(TARGET_NAME core)

set(CORE_SRCS
	api.c
	doomgram.c
	ev.c
	tracing.c
	version_string.c
)

add_library(${TARGET_NAME}
	${CORE_SRCS}
)

# specify the primary public headers for the library, which controls whether
# they'll be installed
#
# NOTE: it is not yet known (to me, at least) how to include additional
# header files from sub-directories, so this is done below in an additional
# `install()` step
set(CORE_PUBLIC_HEADERS
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${PROJECT_NAME_LOWER}.h"
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/doomgram.h"
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/ev.h"
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/tracing.h"
	"${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/version_string.h"
)

set_target_properties(${TARGET_NAME} PROPERTIES
	OUTPUT_NAME "diagnosticism.${TARGET_NAME}"
	PUBLIC_HEADER "${CORE_PUBLIC_HEADERS}"
)

target_include_directories(${TARGET_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(${TARGET_NAME}
	PUBLIC
		$<$<BOOL:${STLSoft_FOUND}>:STLSoft::STLSoft>
)

target_compile_options(${TARGET_NAME}
	PRIVATE
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
			-Werror -Wall -Wextra -pedantic
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX /W4
		>
)


# ##########################################################
# install

install(TARGETS ${TARGET_NAME}
	EXPORT project-targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER}
)

# additional headers into specific sub-directories

install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/util
	DESTINATION include/${PROJECT_NAME_LOWER}
	FILES_MATCHING
	PATTERN "*.h*"
)

install(
	DIRECTORY ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/test/util
	DESTINATION include/${PROJECT_NAME_LOWER}/test
	FILES_MATCHING
	PATTERN "*.h*"
)


# ############################## end of file ############################# #

