add_library(Gta2Dll SHARED dllmain.cpp)

target_include_directories(Gta2Dll PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_compile_features(Gta2Dll
    PRIVATE cxx_auto_type
    PRIVATE cxx_variadic_templates)

if (MSVC)
    set_target_properties(Gta2Dll PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /functionpadmin:16 /MAP")
    set_target_properties(Gta2Dll PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS /functionpadmin:16 /MAP")
endif()

target_compile_definitions(Gta2Dll PRIVATE "_CRT_SECURE_NO_WARNINGS")

target_link_libraries(Gta2Dll Framework)

if (WIN32 AND CMAKE_SIZEOF_VOID_P EQUAL 4)
   target_link_libraries(Gta2Dll Detours ${SDL2_LIBRARIES})
endif()

export(TARGETS Gta2Dll FILE Gta2Dll.cmake)
install(TARGETS Gta2Dll DESTINATION .)
