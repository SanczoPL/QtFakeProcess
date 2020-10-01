cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(QtFakeProcess
  VERSION 0.0.1
  DESCRIPTION "Example usage of Broadcaster"
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS_COMMON}")
set(TARGET_NAME "QtFakeProcess")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_PREFIX_PATH /home/gmatczak/opencv/build)
configure_file(config.json ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} COPYONLY)

if (WIN32)
	set (CMAKE_PREFIX_PATH "C:\\repo\\OpenCV\\build")
	list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\vcpkg\\installed\\x64-windows")
	list(APPEND CMAKE_PREFIX_PATH "D:\\Qt\\Qt5.12.8\\5.12.8\\msvc2017_64")
	list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\ConfigReader\\build-cmake")
	list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\ProcessingModules\\build")
	list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\QtCommunicatorPlugin\\build")
	list(APPEND CMAKE_PREFIX_PATH "C:\\repo\\Broadcaster\\build")
	
	find_package(spdlog CONFIG REQUIRED)
	find_package(ConfigReader REQUIRED)
endif (WIN32)

find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED)
#include fix for OpenCV
include_directories(
    ${OpenCV_INCLUDE_DIRS}
)

set(SRC
  src/main.cc
)

set(HEADERS
)

add_executable(${TARGET_NAME}
    ${SRC}
    ${HEADERS}
)


if (UNIX)
	target_link_libraries(${PROJECT_NAME} spdlog::spdlog spdlog::spdlog_header_only)
	target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} Threads::Threads ConfigReader)
	
endif (UNIX)

if (WIN32)
	target_link_libraries(${PROJECT_NAME} spdlog::spdlog spdlog::spdlog_header_only)
	target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${OPENGL_LIBRARIES} ${QT_LIBRARIES})
	target_link_libraries(${PROJECT_NAME} Threads::Threads ConfigReader)
endif (WIN32)


