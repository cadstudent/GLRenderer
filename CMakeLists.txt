# 指定 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(GLRender VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
#添加外部库
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)


# 添加可执行文件（指定源文件）
add_executable(GLRender
    main.cpp
    glad.c
    src/Window.cpp
    src/Shader.cpp
    src/Model.cpp
    src/Mesh.cpp
    src/Texture.cpp
    src/Camera.cpp
    
)

# 添加头文件搜索路径
target_include_directories(GLRender PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${OpenGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIRS}
)

# 链接库
target_link_libraries(GLRender ${OPENGL_LIBRARIES} glfw GLEW assimp)
