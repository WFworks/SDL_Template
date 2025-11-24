cmake_minimum_required(VERSION 3.15)
project(game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#find_package(OpenGL REQUIRED)

# ソースファイル収集
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# 内部ファイル除去
foreach(source ${SOURCES})
    if(${source} MATCHES ".*/CMakeFiles/.*")
        list(REMOVE_ITEM SOURCES ${source})
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)

#========================
# プラットフォーム別設定
#========================
if(WIN32)
    message(STATUS "Configuring for Windows build")

    find_package(SDL2 CONFIG REQUIRED)
    find_package(SDL2_image CONFIG REQUIRED)

    target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2
        SDL2_image::SDL2_image
    )

    # SDLのエントリポイント無効化
    target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)

    # MSVC専用設定（Visual Studio系コンパイラ）
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /utf-8 /MP)
        target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:CONSOLE)
    endif()


    # vcpkg の DLL 置き場（自分の環境に合わせてここだけ調整）
    set(VCPKG_BIN_DIR "C:/tools/vcpkg/installed/x64-windows/bin")

    set(DLL_FILES
        "${VCPKG_BIN_DIR}/SDL2.dll"
        "${VCPKG_BIN_DIR}/SDL2_image.dll"
        "${VCPKG_BIN_DIR}/jpeg62.dll"
        "${VCPKG_BIN_DIR}/libpng16.dll"
        "${VCPKG_BIN_DIR}/zlib1.dll"

    )

    # 実行ファイルと同じディレクトリに DLL をコピー
    foreach(dll ${DLL_FILES})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${dll}"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            COMMENT "Copying ${dll} to $<TARGET_FILE_DIR:${PROJECT_NAME}>"
        )
    endforeach()

elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux build")

    find_package(OpenGL REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

    include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${SDL2_LIBRARIES} 
        ${SDL2_IMAGE_LIBRARIES}
    )

elseif(APPLE)
    message(STATUS "Configuring for macOS build")

    find_package(SDL2 REQUIRED HINTS /opt/homebrew/opt/sdl2)
    find_package(SDL2_image REQUIRED HINTS /opt/homebrew/opt/sdl2_image)

    include_directories(
        /opt/homebrew/include
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
    )

    target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2
        SDL2_image::SDL2_image
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@executable_path/../lib;/opt/homebrew/lib"
    )
endif()

