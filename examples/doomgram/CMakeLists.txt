
add_executable(doomgram
	main.c
)

target_link_libraries(doomgram
	PRIVATE
		core
)

define_target_compile_options(doomgram)
