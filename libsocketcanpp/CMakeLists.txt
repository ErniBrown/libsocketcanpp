add_library(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

add_subdirectory(include)
add_subdirectory(src)
