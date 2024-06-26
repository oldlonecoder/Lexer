cmake_minimum_required(VERSION 3.13..3.27 FATAL_ERROR)
## Project name

project(Lexer VERSION 0.1.0 LANGUAGES CXX)

message("Entering ${PROJECT_NAME} project configuration:")

include(GNUInstallDirs)

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set(TargetName ${PROJECT_NAME})


SET(FRAMEWORK_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_library(

    ${TargetName}
    SHARED
    include/${TargetName}/Interface.h                              #global framework-wide macros definitions and dll export and import macros for MSVC.
    include/${TargetName}/Components.h Impl/Components.cxx
    include/${TargetName}/Token.h Impl/Token.cxx
    include/${TargetName}/TokenTable.h Impl/TokenTable.cxx
    Impl/Lexer.cxx
    include/Lexer/Lexer.h
)


target_compile_definitions(${TargetName} PUBLIC "${TargetName}_DEBUG=$<CONFIG:Debug>")
target_compile_features(${TargetName} PUBLIC cxx_std_20)

include(GenerateExportHeader)
generate_export_header(${TargetName} EXPORT_FILE_NAME ${${TargetName}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
    EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF()

target_include_directories(${TargetName} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           $<INSTALL_INTERFACE:include/${TargetName}>
)

target_link_libraries(${TargetName} ${CMAKE_DL_LIBS} AppBook)

add_executable(Test.xApp Test.cxx Test.h)
target_link_libraries(Test.xApp Lexer)




install(DIRECTORY
        include/${TargetName}/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${TargetName}"
)

install(TARGETS ${TargetName}
        EXPORT ${TargetName}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
    install_manifest.txt to be uninstalled!
)


