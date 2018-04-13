set(RLOG_SOURCE
        client.cpp
        stream.cpp
        option.cpp
        kvp.cpp)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

add_library(rlog ${RLOG_SOURCE})

target_link_libraries(rlog ${CURL_LIBRARY})

install (TARGETS rlog LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)