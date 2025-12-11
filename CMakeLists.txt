set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -stdlib=libc++)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STD_DIR /usr/lib/llvm/21/share/libc++/v1)
set(MODULES src/sdl2.cppm ${STD_DIR}/std.cppm)

cmake_minimum_required(VERSION 3.30)
project(sdl2-cpp)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE SDL2)
target_compile_options(test PRIVATE -Wall -Wextra -Wunused-result -Wconversion)
target_sources(
	test PRIVATE FILE_SET CXX_MODULES
	BASE_DIRS ${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
	FILES ${MODULES})
target_include_directories(test PRIVATE src)

install(FILES src/sdl2.cppm src/enums.inc DESTINATION /usr/lib/cmake/sdl2-cpp/src)
