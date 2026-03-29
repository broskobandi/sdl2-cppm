cmake_minimum_required(VERSION 3.30)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	find_file(STD_CPPM NAMES std.cppm PATHS
		/usr/lib/llvm/*/share/libc++/v1
		/usr/lib/*/share/libc++/v1
		/opt/homebrew/opt/llvm/share/libc++/v1
	)
	if(NOT STD_CPPM)
		message(FATAL_ERROR "[ERROR] Failed to find std.cppm")
	else()
		message("[SUCCESS] std.cppm found at ${STD_CPPM}")
	endif()
	cmake_path(GET STD_CPPM PARENT_PATH STD_DIR)
endif()
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS OFF)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
file(GLOB_RECURSE MOD src/*.cppm)
set(SRC src/sdl2.cpp)

project(sdl2-cppm LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-2.32.10
	GIT_SHALLOW TRUE
	SYSTEM
)
FetchContent_MakeAvailable(SDL2)

add_executable(${PROJECT_NAME}-test src/test.cpp)

add_library(${PROJECT_NAME}-static STATIC src/sdl2.cpp)
add_library(${PROJECT_NAME} SHARED src/sdl2.cpp)

if(UNIX)
	target_compile_options(${PROJECT_NAME}-test PRIVATE
		-Wall -Wextra -Werror -Wconversion -Wunused-result -Wno-reserved-module-identifier)
	target_compile_options(${PROJECT_NAME} PRIVATE
		-Wall -Wextra -Werror -Wconversion -Wunused-result -Wno-reserved-module-identifier)
	target_compile_options(${PROJECT_NAME}-static PRIVATE
		-Wall -Wextra -Werror -Wconversion -Wunused-result -Wno-reserved-module-identifier)
endif()

target_compile_definitions(${PROJECT_NAME}-test PRIVATE SDL_MAIN_HANDLED)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)
target_compile_definitions(${PROJECT_NAME}-static PRIVATE SDL_MAIN_HANDLED)

target_link_libraries(${PROJECT_NAME}-test PRIVATE SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME}-static PRIVATE SDL2::SDL2-static)

if(UNIX)
	target_sources(${PROJECT_NAME}-test PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${STD_CPPM} ${MOD}
	)
	target_sources(${PROJECT_NAME} PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${STD_CPPM} ${MOD}
	)
	target_sources(${PROJECT_NAME}-static PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${STD_CPPM} ${MOD}
	)
else()
	target_sources(${PROJECT_NAME}-test PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${MOD}
	)
	target_sources(${PROJECT_NAME} PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${MOD}
	)
	target_sources(${PROJECT_NAME}-static PUBLIC FILE_SET modules TYPE CXX_MODULES
		BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${MOD}
	)
endif()

enable_testing()

add_test(NAME test COMMAND ${PROJECT_NAME}-test)
