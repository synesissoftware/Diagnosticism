# Manual: conditional HAS_STLSoft / shwild link for the versions reporter
# (generator cannot preserve these). Do not restore SIS:AUTO_GENERATED.
define_example_program(test.scratch.versions main.cpp)

if(STLSoft_FOUND OR DEFINED STLSOFT_INCLUDE_DIR)

	target_compile_definitions(test.scratch.versions
		PRIVATE
			HAS_STLSoft
	)

	target_link_STLSoft(test.scratch.versions)
endif()

if(shwild_FOUND)

	target_link_libraries(test.scratch.versions
		PRIVATE
			shwild::core
	)
endif()
