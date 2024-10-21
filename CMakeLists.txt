cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(CryptoSystem VERSION 1.0)

# C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 头文件的包含目录
include_directories(include)

# 定义源文件目录
file(GLOB SOURCES "src/*.cpp")

# 添加可执行文件目标
add_executable(crypto_manager ${SOURCES})

# 链接 OpenSSL 库
find_package(OpenSSL REQUIRED)
target_link_libraries(crypto_manager OpenSSL::SSL OpenSSL::Crypto)

# 设置安装目录（可选，提供可执行文件的安装）
install(TARGETS crypto_manager DESTINATION bin)

# 选择性地添加文档生成（如使用 Doxygen）
option(BUILD_DOCS "Build documentation" ON)
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/docs")
        configure_file(DoxygenConfig.in ${CMAKE_CURRENT_BINARY_DIR}/DoxygenConfig.out @ONLY)
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/DoxygenConfig.out
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
        add_custom_target(doc ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/docs)
    endif()
endif()
