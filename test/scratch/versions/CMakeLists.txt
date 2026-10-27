# Manual: link test dependencies. Presence macros are directory-scoped from
# the top-level detection. Do not restore SIS:AUTO_GENERATED.
define_example_program(test.scratch.versions main.cpp)

if(STLSoft_FOUND OR DEFINED STLSOFT_INCLUDE_DIR)

	target_link_STLSoft(test.scratch.versions)
endif()

if(shwild_FOUND)

	target_link_libraries(test.scratch.versions
		PRIVATE
			shwild::core
	)
endif()

if(TARGET xTests::core)

	target_link_libraries(test.scratch.versions
		PRIVATE
			xTests::core
	)
endif()
