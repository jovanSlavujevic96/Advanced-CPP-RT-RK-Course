add_executable(primer1
	example.cc
	is_void_1.h
)
target_compile_definitions(primer1 PRIVATE -DINCLUDE_PATH="is_void_1.h" -DTARGET="void")

add_executable(primer2
	example.cc
	is_void_2.h
)
target_compile_definitions(primer2 PRIVATE -DINCLUDE_PATH="is_void_2.h" -DTARGET="void")

add_executable(primer3
	example.cc
	is_void_3.h
)
target_compile_definitions(primer3 PRIVATE -DINCLUDE_PATH="is_void_3.h" -DTARGET="void")

add_executable(primer4
	example.cc
	is_void_4.h
)
target_compile_definitions(primer4 PRIVATE -DINCLUDE_PATH="is_void_4.h" -DTARGET="void")

add_executable(primer5
	example.cc
	is_pointer.h
)
target_compile_definitions(primer5 PRIVATE -DINCLUDE_PATH="is_pointer.h" -DTARGET="pointer")

add_executable(primer6
	example.cc
	is_same_1.h
)
target_compile_definitions(primer6 PRIVATE -DINCLUDE_PATH="is_same_1.h" -DTARGET="void")

add_executable(primer7
	example.cc
	is_same_2.h
)
target_compile_definitions(primer7 PRIVATE -DINCLUDE_PATH="is_same_2.h" -DTARGET="const void")

add_executable(primer8
	example.cc
	is_function.h
)
target_compile_definitions(primer8 PRIVATE -DINCLUDE_PATH="is_function.h" -DTARGET="function")

add_executable(Tad Tad.cc)
target_compile_definitions(Tad PRIVATE -DEX3)

add_executable(Something Something.cc)
