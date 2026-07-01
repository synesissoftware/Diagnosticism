
add_executable(tracing
	main.c
)

target_link_libraries(tracing
	PRIVATE
		core
)

define_target_compile_options(tracing)
