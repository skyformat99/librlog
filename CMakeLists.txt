cmake_minimum_required(VERSION 3.5)
project(rlog)

set(CMAKE_CXX_STANDARD 14)
set(CURL_MIN_VERSION "7.28.0")

# Checking for dependencies
find_package(CURL ${CURL_MIN_VERSION} REQUIRED)

# Include the project include directory.
include_directories(${CURL_INCLUDE_DIRS}
        ${RLOG_SOURCE_DIR}/include)

file(GLOB HEADER_LIST "${CMAKE_SOURCE_DIR}/include/*.hpp")
install (FILES ${HEADER_LIST} DESTINATION include)

# Set up source directories
add_subdirectory(src)

set(RLOG_LIB_LOCATION "$<TARGET_FILE:${nvd}>")

configure_file(CMake/nvdConfig.cmake.in
        ${RLOG_BINARY_DIR}/rlogConfig.cmake @ONLY)
