cmake_minimum_required(VERSION 3.25)
project(SpaceCadetPinball VERSION 2.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enforce the modern platform baseline early for clearer errors
if(MSVC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.30)
    message(FATAL_ERROR "Visual Studio 2022 (MSVC 19.30) or newer is required.")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "GCC 13 or newer is required.")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 17)
    message(FATAL_ERROR "Clang 17 or newer is required.")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
    message(FATAL_ERROR "AppleClang 16 (Xcode 16) or newer is required.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules")

# On Windows, set paths to SDL-devel packages here
if(WIN32)
   list(APPEND SDL2_PATH "${CMAKE_CURRENT_LIST_DIR}/Libs/SDL2")
   list(APPEND SDL2_MIXER_PATH "${CMAKE_CURRENT_LIST_DIR}/Libs/SDL2_mixer")
endif()

# Link mingw libs static
if(MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
endif()

if(APPLE)
    set(MACOSX_RPATH)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH true)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
    if(NOT CMAKE_OSX_DEPLOYMENT_TARGET)
        set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")
    endif()
    if(NOT CMAKE_OSX_ARCHITECTURES)
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
    list(APPEND SDL2_PATH "${CMAKE_CURRENT_LIST_DIR}/Libs")
    list(APPEND SDL2_MIXER_PATH "${CMAKE_CURRENT_LIST_DIR}/Libs")
endif()

# SDL2main is not needed
set(SDL2_BUILDING_LIBRARY ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCE_FILES
        src/pch.h

        # Application shell
        src/app/SpaceCadetPinball.cpp
        src/app/winmain.cpp
        src/app/winmain_ui.cpp
        src/app/winmain.h
        src/app/options.cpp
        src/app/options.h
        src/app/fullscrn.cpp
        src/app/fullscrn.h

        # Core game
        src/core/pb.cpp
        src/core/pb.h
        src/core/control.cpp
        src/core/control.h
        src/core/maths.cpp
        src/core/maths.h
        src/core/nudge.cpp
        src/core/nudge.h
        src/core/timer.cpp
        src/core/timer.h
        src/core/TPinballTable.cpp
        src/core/TPinballTable.h
        src/core/TPinballComponent.cpp
        src/core/TPinballComponent.h
        src/core/TCollisionComponent.cpp
        src/core/TCollisionComponent.h
        src/core/TEdgeManager.cpp
        src/core/TEdgeManager.h
        src/core/TEdgeSegment.cpp
        src/core/TEdgeSegment.h
        src/core/TEdgeBox.h
        src/core/TTableLayer.cpp
        src/core/TTableLayer.h

        # Table components
        src/core/components/TBall.cpp
        src/core/components/TBall.h
        src/core/components/TBlocker.cpp
        src/core/components/TBlocker.h
        src/core/components/TBumper.cpp
        src/core/components/TBumper.h
        src/core/components/TCircle.cpp
        src/core/components/TCircle.h
        src/core/components/TComponentGroup.cpp
        src/core/components/TComponentGroup.h
        src/core/components/TDemo.cpp
        src/core/components/TDemo.h
        src/core/components/TDrain.cpp
        src/core/components/TDrain.h
        src/core/components/TFlagSpinner.cpp
        src/core/components/TFlagSpinner.h
        src/core/components/TFlipper.cpp
        src/core/components/TFlipper.h
        src/core/components/TFlipperEdge.cpp
        src/core/components/TFlipperEdge.h
        src/core/components/TGate.cpp
        src/core/components/TGate.h
        src/core/components/THole.cpp
        src/core/components/THole.h
        src/core/components/TKickback.cpp
        src/core/components/TKickback.h
        src/core/components/TKickout.cpp
        src/core/components/TKickout.h
        src/core/components/TLight.cpp
        src/core/components/TLight.h
        src/core/components/TLightBargraph.cpp
        src/core/components/TLightBargraph.h
        src/core/components/TLightGroup.cpp
        src/core/components/TLightGroup.h
        src/core/components/TLightRollover.cpp
        src/core/components/TLightRollover.h
        src/core/components/TLine.cpp
        src/core/components/TLine.h
        src/core/components/TOneway.cpp
        src/core/components/TOneway.h
        src/core/components/TPlunger.cpp
        src/core/components/TPlunger.h
        src/core/components/TPopupTarget.cpp
        src/core/components/TPopupTarget.h
        src/core/components/TRamp.cpp
        src/core/components/TRamp.h
        src/core/components/TRollover.cpp
        src/core/components/TRollover.h
        src/core/components/TSink.cpp
        src/core/components/TSink.h
        src/core/components/TSoloTarget.cpp
        src/core/components/TSoloTarget.h
        src/core/components/TTimer.cpp
        src/core/components/TTimer.h
        src/core/components/TTripwire.cpp
        src/core/components/TTripwire.h
        src/core/components/TWall.cpp
        src/core/components/TWall.h

        # Rendering
        src/render/render.cpp
        src/render/render.h
        src/render/gdrv.cpp
        src/render/gdrv.h
        src/render/zdrv.cpp
        src/render/zdrv.h
        src/render/proj.cpp
        src/render/proj.h

        # Audio
        src/audio/Sound.cpp
        src/audio/Sound.h
        src/audio/midi.cpp
        src/audio/midi.h
        src/audio/TSound.cpp
        src/audio/TSound.h

        # Game data
        src/data/partman.cpp
        src/data/partman.h
        src/data/GroupData.cpp
        src/data/GroupData.h
        src/data/loader.cpp
        src/data/loader.h
        src/data/EmbeddedData.cpp
        src/data/EmbeddedData.h

        # UI and localization
        src/ui/DebugOverlay.cpp
        src/ui/DebugOverlay.h
        src/ui/font_selection.cpp
        src/ui/font_selection.h
        src/ui/high_score.cpp
        src/ui/high_score.h
        src/ui/score.cpp
        src/ui/score.h
        src/ui/translations.cpp
        src/ui/translations_data.cpp
        src/ui/translations.h
        src/ui/TTextBox.cpp
        src/ui/TTextBox.h
        src/ui/TTextBoxMessage.cpp
        src/ui/TTextBoxMessage.h

        # Third-party ImGui
        third_party/imgui/imconfig.h
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui.h
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_internal.h
        third_party/imgui/imgui_sdl.cpp
        third_party/imgui/imgui_sdl.h
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/imgui_impl_sdl.cpp
        third_party/imgui/imgui_impl_sdl.h
        third_party/imgui/imgui_impl_sdlrenderer.cpp
        third_party/imgui/imgui_impl_sdlrenderer.h
        third_party/imgui/imstb_rectpack.h
        third_party/imgui/imstb_textedit.h
        third_party/imgui/imstb_truetype.h
        )

# On Windows, include resource file with the icon
if(WIN32)
    set_source_files_properties(src/platform/windows/SpaceCadetPinball.rc LANGUAGE RC)
    list(APPEND SOURCE_FILES src/platform/windows/SpaceCadetPinball.rc)
endif(WIN32)

add_executable(SpaceCadetPinball ${SOURCE_FILES})

if(MSVC)
    target_sources(SpaceCadetPinball PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/debug/NatvisFile.natvis)
    set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/debug/NatvisFile.natvis PROPERTIES HEADER_FILE_ONLY TRUE)
endif()

target_include_directories(SpaceCadetPinball PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/windows
        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/imgui
        ${SDL2_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        )

# Modern compiler baseline: VS 2022+, GCC 13+, Clang 17+, AppleClang 16+
if(MSVC)
    target_compile_options(SpaceCadetPinball PRIVATE
            /W4
            /permissive-
            /Zc:__cplusplus
            /Zc:preprocessor
            /utf-8
            )
else()
    target_compile_options(SpaceCadetPinball PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            )
endif()

option(SCP_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)
if(SCP_WARNINGS_AS_ERRORS)
    if(MSVC)
        target_compile_options(SpaceCadetPinball PRIVATE /WX)
    else()
        target_compile_options(SpaceCadetPinball PRIVATE -Werror)
    endif()
endif()

option(SCP_SANITIZE "Enable Address/UB sanitizers" OFF)
if(SCP_SANITIZE)
    if(MSVC)
        # /fsanitize=address cannot be combined with the /RTC1 Debug default
        string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
        target_compile_options(SpaceCadetPinball PRIVATE /fsanitize=address)
    else()
        target_compile_options(SpaceCadetPinball PRIVATE
                -fsanitize=address,undefined
                -fno-omit-frame-pointer
                )
        target_link_options(SpaceCadetPinball PRIVATE -fsanitize=address,undefined)
    endif()
endif()

option(SCP_LTO "Enable link-time optimization" OFF)
if(SCP_LTO AND NOT SCP_SANITIZE)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT SCP_IPO_SUPPORTED OUTPUT SCP_IPO_OUTPUT LANGUAGES CXX)
    if(SCP_IPO_SUPPORTED)
        # LTO is only meaningful for release builds; keep Debug editable/debuggable.
        set_property(TARGET SpaceCadetPinball PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
    else()
        message(WARNING "LTO is not supported: ${SCP_IPO_OUTPUT}")
    endif()
endif()

# Skip pch on foreign code
set_source_files_properties(
        third_party/imgui/imgui.cpp
        third_party/imgui/imgui_sdl.cpp
        third_party/imgui/imgui_draw.cpp
        third_party/imgui/imgui_widgets.cpp
        third_party/imgui/imgui_tables.cpp
        third_party/imgui/imgui_demo.cpp
        third_party/imgui/imgui_impl_sdl.cpp
        third_party/imgui/imgui_impl_sdlrenderer.cpp
        PROPERTIES SKIP_PRECOMPILE_HEADERS 1
)

target_precompile_headers(SpaceCadetPinball PRIVATE src/pch.h)

target_link_libraries(SpaceCadetPinball PRIVATE ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY})

# Copy local game data from Resources/ next to the executable.
# The original game assets are not part of this repository.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
    add_custom_command(TARGET SpaceCadetPinball POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
                    "$<TARGET_FILE_DIR:SpaceCadetPinball>"
            COMMENT "Copying game resources to $<TARGET_FILE_DIR:SpaceCadetPinball>"
            )
endif()

# On Windows, copy DLL to output
if(WIN32)
    list(GET SDL2_LIBRARY -1 SDL2_DLL_PATH)
    list(GET SDL2_MIXER_LIBRARY -1 SDL2_MIXER_DLL_PATH)
    get_filename_component(SDL2_DLL_PATH ${SDL2_DLL_PATH} DIRECTORY)
    get_filename_component(SDL2_MIXER_DLL_PATH ${SDL2_MIXER_DLL_PATH} DIRECTORY)
    if(MINGW)
        string(REGEX REPLACE "lib$" "bin" SDL2_DLL_PATH ${SDL2_DLL_PATH})
        string(REGEX REPLACE "lib$" "bin" SDL2_MIXER_DLL_PATH ${SDL2_MIXER_DLL_PATH})
    endif()
    # vcpkg keeps runtime DLLs in ../bin instead of next to the import library
    if(NOT EXISTS "${SDL2_DLL_PATH}/SDL2.dll" AND EXISTS "${SDL2_DLL_PATH}/../bin/SDL2.dll")
        get_filename_component(SDL2_DLL_PATH "${SDL2_DLL_PATH}/../bin" ABSOLUTE)
    endif()
    if(NOT EXISTS "${SDL2_MIXER_DLL_PATH}/SDL2_mixer.dll" AND EXISTS "${SDL2_MIXER_DLL_PATH}/../bin/SDL2_mixer.dll")
        get_filename_component(SDL2_MIXER_DLL_PATH "${SDL2_MIXER_DLL_PATH}/../bin" ABSOLUTE)
    endif()
    message(STATUS "copy paths='${SDL2_DLL_PATH}' '${SDL2_MIXER_DLL_PATH}'") 
    add_custom_command(TARGET SpaceCadetPinball POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_DLL_PATH}/SDL2.dll" $<TARGET_FILE_DIR:SpaceCadetPinball>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SDL2_MIXER_DLL_PATH}/SDL2_mixer.dll" $<TARGET_FILE_DIR:SpaceCadetPinball>
        )
endif()

if(UNIX AND NOT APPLE)
	include(GNUInstallDirs)
	install(TARGETS "${PROJECT_NAME}" RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
	install(FILES "${CMAKE_SOURCE_DIR}/Platform/Linux/${PROJECT_NAME}.desktop" DESTINATION "share/applications")
	install(FILES "${CMAKE_SOURCE_DIR}/Platform/Linux/${PROJECT_NAME}.metainfo.xml" DESTINATION "share/metainfo")
	foreach(S 16 32 48 128 192)
		install(FILES "${CMAKE_SOURCE_DIR}/assets/icons/Icon_${S}x${S}.png" DESTINATION
			"share/icons/hicolor/${S}x${S}/apps" RENAME "${PROJECT_NAME}.png")
	endforeach(S)
endif()
