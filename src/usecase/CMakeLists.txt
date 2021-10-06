cmake_minimum_required(VERSION 3.12)

add_executable(usecase)
target_sources(usecase
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    )

target_link_libraries(usecase PUBLIC flat)
