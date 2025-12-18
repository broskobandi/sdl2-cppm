cmake_minimum_required(VERSION 3.30)

if (UNIX AND NOT APPLE)
	message("Building on Linux.")

	get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
	message("Compiler being used: ${COMPILER_NAME}")
	if (NOT COMPILER_NAME STREQUAL clang++)
		message(FATAL_ERROR
			"Must use clang as the project uses modules, libc++, and 'import std;'")
	endif()
	if (NOT CMAKE_GENERATOR STREQUAL Ninja)
		message(FATAL_ERROR
			"Must use ninja as the project is built using c++20 modules.")
	endif()

	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_CXX_FLAGS -stdlib=libc++)
	file(GLOB MOD
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
		${CMAKE_CURRENT_SOURCE_DIR}/std/std.cppm
	)
	file(GLOB SRC
		${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	)

	project(sdl2-cppm)

	add_executable(sdl2-cppm-test test/test.cpp ${SRC})
	target_link_libraries(sdl2-cppm-test PRIVATE SDL2)
	target_sources(sdl2-cppm-test PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	add_custom_target(sdl2-cppm-run_test COMMAND $<TARGET_FILE:sdl2-cppm-test>)

	add_library(${PROJECT_NAME} SHARED ${SRC})
	add_library(${PROJECT_NAME}-static STATIC ${SRC})
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
	target_link_libraries(${PROJECT_NAME}-static PRIVATE SDL2)
	add_dependencies(${PROJECT_NAME} sdl2-cppm-run_test)
	set_target_properties(
		${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

	add_executable(sdl2-cppm-example EXCLUDE_FROM_ALL example/example.cpp ${SRC})
	target_link_libraries(sdl2-cppm-example PRIVATE SDL2)
	target_sources(sdl2-cppm-example PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	add_dependencies(sdl2-cppm-example sdl2-cppm-run_test)

	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(
			${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
		target_compile_options(
			${PROJECT_NAME}-static PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
		target_compile_options(
			sdl2-cppm-example PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
	endif()

	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		target_compile_options(
			${PROJECT_NAME} PRIVATE -O3 -march=native)
		target_compile_options(
			${PROJECT_NAME}-static PRIVATE -O3 -march=native)
		target_compile_options(
			sdl2-cppm-example PRIVATE -O3 -march=native)
	endif()

	target_sources(${PROJECT_NAME} PRIVATE FILE_SET modules
		TYPE CXX_MODULES FILES ${MOD})
	target_sources(${PROJECT_NAME}-static PRIVATE FILE_SET modules
		TYPE CXX_MODULES FILES ${MOD})

endif()

if (WIN32)
	message("Building on Windows.")

	set(CMAKE_CXX_STANDARD 23)
	set(CMAKE_CXX_EXTENSIONS OFF)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	file(GLOB MOD ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)
	file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
	project(sdl2-cppm)
	
	add_executable(sdl2-cppm-test test/test.cpp ${SRC})
	target_link_directories(sdl2-cppm-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x64)
	target_link_libraries(sdl2-cppm-test PRIVATE SDL2 SDL2main)
	add_custom_target(sdl2-cppm-run_test COMMAND $<TARGET_FILE:sdl2-cppm-test>)
	
	add_custom_command(TARGET sdl2-cppm-test PRE_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x64/SDL2.dll
		${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
	)

	add_library(${PROJECT_NAME} SHARED ${SRC})
	add_library(${PROJECT_NAME}-static STATIC ${SRC})
	add_executable(sdl2-cppm-example EXCLUDE_FROM_ALL example/example.cpp ${SRC})
	set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
	target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x64)
	target_link_directories(${PROJECT_NAME}-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x64)
	target_link_directories(sdl2-cppm-example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x64)
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2 SDL2main)
	target_link_libraries(${PROJECT_NAME}-static PRIVATE SDL2 SDL2main)
	target_link_libraries(sdl2-cppm-example PRIVATE SDL2 SDL2main)
	add_dependencies(${PROJECT_NAME} sdl2-cppm-run_test)
	add_dependencies(${PROJECT_NAME}-static sdl2-cppm-run_test)
	add_dependencies(sdl2-cppm-example sdl2-cppm-run_test)
	target_sources(sdl2-cppm-test PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	target_sources(${PROJECT_NAME} PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	target_sources(${PROJECT_NAME}-static PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	target_sources(sdl2-cppm-example PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	target_include_directories(sdl2-cppm-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/include)
	target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/include)
	target_include_directories(${PROJECT_NAME}-static PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/include)
	target_include_directories(sdl2-cppm-example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/include)

	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		target_compile_options(${PROJECT_NAME} PRIVATE NDEBUG)
		target_compile_options(${PROJECT_NAME}-static PRIVATE NDEBUG)
	endif()
	
endif()
