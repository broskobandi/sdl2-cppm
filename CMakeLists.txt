cmake_minimum_required(VERSION 3.30)

if (UNIX AND NOT APPLE)
	message("Building on Linux.")

	if (NOT CMAKE_CXX_COMPILER STREQUAL clang++)
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

	add_executable(test test/test.cpp ${SRC})
	target_link_libraries(test PRIVATE SDL2)
	target_sources(test PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	add_custom_target(run_test COMMAND $<TARGET_FILE:test>)

	add_library(${PROJECT_NAME} SHARED ${SRC})
	add_library(${PROJECT_NAME}-static STATIC ${SRC})
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)
	target_link_libraries(${PROJECT_NAME}-static PRIVATE SDL2)
	add_dependencies(${PROJECT_NAME} run_test)
	set_target_properties(
		${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

	add_executable(example EXCLUDE_FROM_ALL example/example.cpp ${SRC})
	target_link_libraries(example PRIVATE SDL2)
	target_sources(example PRIVATE FILE_SET modules TYPE CXX_MODULES FILES ${MOD})
	add_dependencies(example run_test)

	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_compile_options(
			${PROJECT_NAME} PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
		target_compile_options(
			${PROJECT_NAME}-static PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
		target_compile_options(
			example PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
	endif()

	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		target_compile_options(
			${PROJECT_NAME} PRIVATE -O3 -march=native)
		target_compile_options(
			${PROJECT_NAME}-static PRIVATE -O3 -march=native)
		target_compile_options(
			example PRIVATE -O3 -march=native)
	endif()

	target_sources(${PROJECT_NAME} PRIVATE FILE_SET modules
		TYPE CXX_MODULES FILES ${MOD})
	target_sources(${PROJECT_NAME}-static PRIVATE FILE_SET modules
		TYPE CXX_MODULES FILES ${MOD})

endif()

if (WIN32)
	message(FATAL_ERROR "Windows build script is not ready.")
	#
	# cmake_minimum_required(VERSION 3.30)
	#
	# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
	# set(CMAKE_CXX_STANDARD 23)
	# set(CMAKE_CXX_EXTENSIONS OFF)
	# set(CMAKE_CXX_STANDARD_REQUIRED ON)
	# project()


	project(sdl2-cppm)
	
endif()

project(sdl2-cppm)

# cmake_minimum_required(VERSION 3.30)
#
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# if (UNIX AND NOT APPLE)
# 	if (NOT CMAKE_CXX_COMPILER STREQUAL "clang++")
# 		message(FATAL_ERROR "Make sure you are using clang++.")
# 	endif()
# 	set(CMAKE_CXX_FLAGS -stdlib=libc++)
# 	file(GLOB MOD ${STD} src/*.cppm std/std.cppm)
# endif()
# if (WIN32)
# 	file(GLOB MOD src/*.cppm)
# endif()
# file(GLOB SRC src/*.cpp)
#
# project(sdl2-cppm LANGUAGES CXX)
#
# add_executable(exe ${SRC})
#
# if (WIN32)
# 	add_custom_command(TARGET exe PRE_BUILD
# 		COMMAND ${CMAKE_COMMAND} -E copy
# 		${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x86/SDL2.dll
# 		${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll
# 	)
# endif()
#
# add_executable(test test/test.cpp ${SRC})
# if (UNIX AND NOT APPLE)
# 	target_sources(test PRIVATE FILE_SET modules TYPE CXX_MODULES
# 	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
# 	FILES ${MOD})
# endif()
# if (WIN32)
# 	target_link_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x86)
# endif()
# target_link_libraries(test PRIVATE SDL2)
# if (WIN32)
# 	target_link_libraries(test PRIVATE SDL2main)
# endif()
# add_custom_target(run_test COMMAND $<TARGET_FILE:test>)
#
# add_executable(example EXCLUDE_FROM_ALL example/example.cpp ${SRC})
# if (UNIX AND NOT APPLE)
# 	target_sources(example PRIVATE FILE_SET modules TYPE CXX_MODULES
# 	BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
# 	FILES ${MOD})
# endif()
# if (WIN32)
# 	target_link_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/WIN/lib/x86)
# endif()
# target_link_libraries(example PRIVATE SDL2)
# if (WIN32)
# 	target_link_libraries(example PRIVATE SDL2main)
# endif()
#
# add_library(${PROJECT_NAME} SHARED ${SRC})
# add_library(${PROJECT_NAME}-static STATIC ${SRC})
# set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
# add_dependencies(${PROJECT_NAME} run_test)
# add_dependencies(${PROJECT_NAME}-static run_test)
#
# if (CMAKE_BUILD_TYPE STREQUAL "Release")
# 	if (UNIX AND NOT APPLE)
# 		target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)
# 		target_compile_options(${PROJECT_NAME}-static PRIVATE -O3 -march=native)
# 		target_compile_definitions(${PROJECT_NAME} PRIVATE NDEBUG)
# 		target_compile_definitions(${PROJECT_NAME}-static PRIVATE NDEBUG)
# 	endif()
# endif()
#
# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
# 	if (UNIX AND NOT APPLE)
# 		target_compile_options(${PROJECT_NAME}
# 			PRIVATE -Wall -Wextra -Wconversion -Wunused-result)
# 		target_compile_options(${PROJECT_NAME}-static
# 			PRIVATE -Wall -Wextra -Wconversion -Wunused-result)
# 	endif()
# endif()
