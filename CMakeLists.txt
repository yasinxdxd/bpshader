cmake_minimum_required(VERSION 3.10)
project(bpshader VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(-DCMAKE_GENERATOR_PLATFORM=x64)
#set(CMAKE_STATIC_LINKER_FLAGS  "-static-libgcc")
#set_target_properties(${PROJECT_NAME} ./build/)
set(EXTERN_DIR "extern")

include_directories(
    ${EXTERN_DIR}/glad/include
    ${EXTERN_DIR}/glfw/include
    ${EXTERN_DIR}/imgui/include
    ${EXTERN_DIR}/imguifiledialog/include
    ${EXTERN_DIR}/stb_image
    ${EXTERN_DIR}/mini
                    "include")

if(CMAKE_BUILD_TYPE MATCHES Release)
    if(MSVC)
        message("MSVC-RELEASE")
        set(LINK_LIBS
        "glfw3.lib"
        )
    else()
        message("G++-RELEASE")
        set(LINK_LIBS 
        "libglfw3.a"
        )
    endif()
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
    if(MSVC)
        message("MSVC-DEBUG")
        set(LINK_LIBS
        "glfw3.lib"
    )
    else()
        message("G++-DEBUG")
        set(LINK_LIBS 
        "libglfw3.a"
        )
    endif()
endif()


link_directories(
    ${EXTERN_DIR}/glfw/lib
)

file(GLOB SOURCES "src/*.cpp" "src/*.c" "src/*.cc"
${EXTERN_DIR}/glad/src/glad.c
${EXTERN_DIR}/imgui/src/*.cpp
${EXTERN_DIR}/imguifiledialog/src/*.cpp)



add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})