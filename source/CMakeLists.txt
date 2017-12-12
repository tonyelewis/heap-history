include( ./auto_generated_file_list.cmake )

add_executable(
	heap-benchmark
		${NORMSOURCES_BM}
		${NORMSOURCES_COMMON}
)

target_include_directories( heap-benchmark PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> )

add_executable(
	heap-history
		${NORMSOURCES_PART}
		${NORMSOURCES_COMMON}
)

target_include_directories( heap-history   PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> )
