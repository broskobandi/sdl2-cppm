cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB MOD ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm)

if(UNIX AND NOT APPLE)

	message("[STATUS] Building on Linux")

	# Set stdlib to libc++ 
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -stdlib=libc++)

	# Check if clang++ is being used.
	if(NOT CMAKE_CXX_COMPILER)
		message(FATAL_ERROR
			"[ERROR] Please specify the c++ compiler."
		)
	endif()
	get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
	message("[STATUS] Compiler: ${COMPILER_NAME}")
	if(NOT COMPILER_NAME STREQUAL clang++)
		message(FATAL_ERROR
			"[ERROR] Must use clang++ because the project uses c++23 modules"
		)
	endif()

	# Check if ninja is being used.
	if(NOT CMAKE_GENERATOR STREQUAL Ninja)
		message(FATAL_ERROR
			"[ERROR] Must use Ninja because the project uses c++23 modules"
		)
	endif()
	
	# Make sure libc++ is found
	if (NOT STD_CPPM)
		message(FATAL_ERROR
			"[ERROR] Please specify the path to std.cppm with -DSTD_CPPM=[path]"
		)
	endif()
	file(GLOB STD ${STD_CPPM})
	if (STD)
		message("[STATUS] std.cppm found.")
	else()
		message("[ERROR] std.cppm not found.")
	endif()
	# Set STD_DIR for later use
	get_filename_component(STD_DIR ${STD_CPPM} DIRECTORY)

	# Set project name
	project(sdl2-cppm)

	# Make sure SDL2 is available
	find_package(SDL2 2.32.8 QUIET)
	if(NOT SDL2_FOUND)
		message("[STATUS] Downloading SDL2...")
		include(FetchContent)
		FetchContent_Declare(
			SDL2
			GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
			GIT_SHALLOW TRUE
			GIT_TAG release-2.32.x
		)
		FetchContent_MakeAvailable(SDL2) 
	else()
		message("[STATUS] SDL2 found.")
	endif()
	
	# Add std.cppm to the MOD variable
	file(GLOB MOD ${MOD} ${STD})

	# Set test target
	add_executable(${PROJECT_NAME}-test test/test.cpp ${SRC})
	set(TARGETS ${TARGETS} ${PROJECT_NAME}-test)
	# Add testing command
	add_custom_target(
		${PROJECT_NAME}-run_test
		COMMAND $<TARGET_FILE:${PROJECT_NAME}-test>)

	# Set example target
	add_executable(
		${PROJECT_NAME}-example EXCLUDE_FROM_ALL example/example.cpp ${SRC}
	)
	set(TARGETS ${TARGETS} ${PROJECT_NAME}-example)
	add_dependencies(${PROJECT_NAME}-example ${PROJECT_NAME}-run_test)

	# Set shared library target
	add_library(${PROJECT_NAME} SHARED ${SRC})
	set(TARGETS ${TARGETS} ${PROJECT_NAME})
	add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-run_test)

	# Set static library target
	add_library(${PROJECT_NAME}-static STATIC ${SRC})
	set(TARGETS ${TARGETS} ${PROJECT_NAME}-static)
	set_target_properties(
		${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
	)

	# Set shared target settings
	foreach(T IN LISTS TARGETS)
		target_link_libraries(${T} PRIVATE SDL2)
		target_include_directories(${T} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
		target_sources(
			${T} PRIVATE
			FILE_SET modules TYPE CXX_MODULES
			BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${STD_DIR}
			FILES ${MOD}
		)
	endforeach()

endif()

if(WIN32)

	message("Building on Window.")

	# Set project name
	project(sdl2-cppm)

endif()
