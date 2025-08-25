
macro(define_target_compile_options target_name)

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${target_name}
		PRIVATE
			$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
				-Werror -Wall -Wextra -pedantic

			${X_GCC_CUSTOM_WARNINGS_}
		>
		$<$<CXX_COMPILER_ID:MSVC>:
			/WX /W4

			${X_MSVC_CUSTOM_WARNINGS_}
		>
	)
endmacro(define_target_compile_options)

macro(target_link_CLASP target_name)

	target_link_libraries(${target_name}
		PRIVATE
			CLASP::core
	)
endmacro(target_link_CLASP)

macro(target_link_STLSoft target_name)

	target_link_libraries(${target_name}
		PRIVATE
			$<$<BOOL:${STLSoft_FOUND}>:STLSoft::STLSoft>
	)
endmacro(target_link_STLSoft)

macro(target_link_shwild_ target_name)

	# NOTE: the following generator expression is somewhat moot (since
	# target_link_shwild_() should never be called directly, and
	# target_link_shwild_if_found() performs the requisite checks), but is
	# left in as a documentation of the technique.
	target_link_libraries(${target_name}
		PRIVATE
			$<${shwild_FOUND}:shwild::core>
	)
endmacro(target_link_shwild_)

macro(target_link_shwild_if_found target_name)

	if(shwild_FOUND)

		target_link_shwild_(${program_name})
	endif(shwild_FOUND)
endmacro(target_link_shwild_if_found)

macro(target_link_xTests target_name)

	target_link_libraries(${target_name}
		PRIVATE
			$<IF:$<VERSION_LESS:${xTests_VERSION},"0.23">,xTests::xTests.core,xTests::core>
	)
endmacro(target_link_xTests)

function(define_simple_console_example_c program_and_main_source_stem)

	add_executable(${program_and_main_source_stem}
		${program_and_main_source_stem}.c
	)

	target_link_STLSoft(${program_and_main_source_stem})

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${program_and_main_source_stem}
		PRIVATE
			$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
				-Werror -Wall -Wextra -pedantic

				${X_GCC_CUSTOM_WARNINGS_}
			>
			$<$<CXX_COMPILER_ID:MSVC>:
				/WX /W4

				${X_MSVC_CUSTOM_WARNINGS_}
			>
	)
endfunction(define_simple_console_example_c)

function(define_simple_console_example_cpp program_and_main_source_stem)

	add_executable(${program_and_main_source_stem}
		${program_and_main_source_stem}.cpp
	)

	target_link_STLSoft(${program_and_main_source_stem})

	set(X_GCC_CUSTOM_WARNINGS_ "")

	if(X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
		foreach(warning ${X_GCC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

			list(APPEND X_GCC_CUSTOM_WARNINGS_ "-Wno-${warning}")
		endforeach()
	endif()

	set(X_MSVC_CUSTOM_WARNINGS_ "")

	if(X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED)
			foreach(warning ${X_MSVC_CUSTOM_WARNINGS_TO_BE_SUPPRESSED})

					list(APPEND X_MSVC_CUSTOM_WARNINGS_ "/wd${warning}")
			endforeach()
	endif()

	target_compile_options(${program_and_main_source_stem}
		PRIVATE
			$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
				-Werror -Wall -Wextra -pedantic

				${X_GCC_CUSTOM_WARNINGS_}
			>
			$<$<CXX_COMPILER_ID:MSVC>:
				/WX /W4

				${X_MSVC_CUSTOM_WARNINGS_}
			>
	)
endfunction(define_simple_console_example_cpp)

macro(install_file subdir file_list)

	install(
		FILES
			${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME_LOWER}/${subdir}/${file_list}
		DESTINATION include/${PROJECT_NAME_LOWER}/${subdir}/
	)
endmacro(install_file)


function(define_automated_test_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	target_link_libraries(${program_name}
		PRIVATE
			core
	)

	target_link_shwild_if_found(${program_name})

	target_link_xTests(${program_name})

	define_target_compile_options(${program_name})
endfunction(define_automated_test_program)


function(define_example_program program_name entry_point_source_name)

	add_executable(${program_name}
		${entry_point_source_name}
	)

	target_link_libraries(${program_name}
		PRIVATE
			core
	)

	target_link_CLASP(${program_name})

	define_target_compile_options(${program_name})
endfunction(define_example_program)


# ############################## end of file ############################# #

