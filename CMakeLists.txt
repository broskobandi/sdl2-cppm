set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -stdlib=libc++)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()
message("[CMAKE_BUILD_TYPE]: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(STD_DIR /usr/lib/llvm/21/share/libc++/v1)
set(STD ${STD_DIR}/std.cppm)
file(GLOB MODULES ${STD} src/*.cppm)
file(GLOB SOURCES src/*.cpp src/sdl2/*.cpp)

cmake_minimum_required(VERSION 3.30)
project(sdl2-cppm)

add_executable(test EXCLUDE_FROM_ALL test/test.cpp ${SOURCES})
target_link_libraries(test PRIVATE SDL2)
target_compile_options(test PRIVATE -Wall -Wextra -Wconversion -Wunused-result)

add_executable(example EXCLUDE_FROM_ALL example/example.cpp ${SOURCES})
target_link_libraries(example PRIVATE SDL2)
target_compile_options(example PRIVATE -Wall -Wextra -Wconversion -Wunused-result)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES})
set_target_properties(${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

set(TARGETS test example ${PROJECT_NAME} ${PROJECT_NAME}-static)
foreach(TGT IN LISTS TARGETS)
	target_sources(${TGT} PRIVATE FILE_SET modules TYPE CXX_MODULES BASE_DIRS
		${STD_DIR} ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MODULES}
	)
endforeach()
