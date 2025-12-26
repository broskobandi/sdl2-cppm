cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if(UNIX AND NOT APPLE)

	message("[STATUS] Building on Linux")

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
	

endif()

if(WIN32)

	project(sdl2-cppm)

endif()
