cmake_minimum_required(VERSION 3.23)

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_LIST_DIR}
    FILES 
        Can.hpp
        CanMessage.hpp
)