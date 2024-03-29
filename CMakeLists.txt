cmake_minimum_required(VERSION 3.23)

project(libsocketcanpp LANGUAGES CXX VERSION 0.1)

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_SHARED_LIBS "Build shared libraries instead of static ones" ON)

#set(CMAKE_CXX_STANDARD 11)
#include(GNUInstallDirs)

add_subdirectory(libsocketcanpp)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")



install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    FILE_SET HEADERS
)

install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION lib/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${${PROJECT_NAME}_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(FILES "cmake/${PROJECT_NAME}Config.cmake" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME})


#set(prefix      ${CMAKE_INSTALL_PREFIX})
#set(exec_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR})
#set(includedir  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR})
#set(libdir      ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})

#configure_file(libsockcanpp.pc.in ${CMAKE_BINARY_DIR}/libsockcanpp.pc @ONLY)
# Install pkg-config files
#install(FILES ${CMAKE_BINARY_DIR}/libsockcanpp.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

#include(cmake/cpack.cmake)

###
# Docs target
###
#add_custom_target("docs" COMMENT "Create Doxygen documentation")
#add_custom_command(
#    TARGET "docs"
#    POST_BUILD
#        COMMENT "Generate Doxygen documentation for publication or reading"
#        COMMAND doxygen ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)