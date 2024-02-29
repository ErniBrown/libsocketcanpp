add_executable(CanRaw CanRaw.cpp)
target_link_libraries(CanRaw libsocketcanpp)

add_executable(CanFactory CanFactory.cpp)
target_link_libraries(CanFactory libsocketcanpp)
