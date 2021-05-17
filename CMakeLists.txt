cmake_minimum_required(VERSION 3.19)

project(flywick)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

FLEX_TARGET(lexer src/lexer.ll ${CMAKE_CURRENT_BINARY_DIR}/lexer.tab.cc)
BISON_TARGET(parser src/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wno-register -Ofast")

file(GLOB SRC src/*.cpp)

message(STATUS ${SRC})

add_executable(parser
  ${SRC}
  ${FLEX_lexer_OUTPUTS}
  ${BISON_parser_OUTPUTS}
)

target_include_directories(parser
  PRIVATE
  src
  include
)
