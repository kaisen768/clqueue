cmake_minimum_required(VERSION 3.0.0)

project(clqueue C)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wno-unused-function")

aux_source_directory(src COMMON_SRC)

option(ENABLE_CLQUEUE_EXAMPLE "Enable building clqueue example" ON)
if (ENABLE_CLQUEUE_EXAMPLE)

set(CLQUEUE_EXAMPLE_PATH "${CMAKE_SOURCE_DIR}/example")

#--------------------------
# sample_bqueue_single_thread
#--------------------------
add_executable(sample_bqueue_single_thread ${CLQUEUE_EXAMPLE_PATH}/sample_bqueue_single_thread.c ${COMMON_SRC})
target_link_libraries(sample_bqueue_single_thread pthread)
target_include_directories(sample_bqueue_single_thread PRIVATE ${CMAKE_SOURCE_DIR}/src)

#--------------------------
# sample_bqueue_multi_thread_noblock
#--------------------------
add_executable(sample_bqueue_multi_thread_noblock ${CLQUEUE_EXAMPLE_PATH}/sample_bqueue_multi_thread_noblock.c ${COMMON_SRC})
target_link_libraries(sample_bqueue_multi_thread_noblock pthread)
target_include_directories(sample_bqueue_multi_thread_noblock PRIVATE ${CMAKE_SOURCE_DIR}/src)

#--------------------------
# sample_bqueue_multi_thread_block
#--------------------------
add_executable(sample_bqueue_multi_thread_block ${CLQUEUE_EXAMPLE_PATH}/sample_bqueue_multi_thread_block.c ${COMMON_SRC})
target_link_libraries(sample_bqueue_multi_thread_block pthread)
target_include_directories(sample_bqueue_multi_thread_block PRIVATE ${CMAKE_SOURCE_DIR}/src)

#--------------------------
# sample_pqueue
#--------------------------
add_executable(sample_pqueue ${CLQUEUE_EXAMPLE_PATH}/sample_pqueue.c ${COMMON_SRC})
target_link_libraries(sample_pqueue pthread)
target_include_directories(sample_pqueue PRIVATE ${CMAKE_SOURCE_DIR}/src)

endif()


