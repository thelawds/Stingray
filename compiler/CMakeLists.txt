cmake_minimum_required(VERSION 3.21)
project(compiler)

set(CMAKE_CXX_STANDARD 20)

FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX REQUIRED)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

BISON_TARGET(
        PARSER
        ${CMAKE_SOURCE_DIR}/syntax/stingray.y
        ${CMAKE_CURRENT_BINARY_DIR}/syntax/Parser.C
        DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/syntax/Parser.H
        COMPILE_FLAGS -t
        COMPILE_FLAGS -pstingray_
)

FLEX_TARGET(
        SCANNER ${CMAKE_SOURCE_DIR}/syntax/stingray.l
        ${CMAKE_CURRENT_BINARY_DIR}/syntax/Lexer.C
        COMPILE_FLAGS -Pstingray_
)

ADD_FLEX_BISON_DEPENDENCY(SCANNER PARSER)

set(
        BNFC_SOURCES
        syntax/Absyn.C
        syntax/Absyn.H
        syntax/Buffer.C
        syntax/Buffer.H
        syntax/Printer.C
        syntax/Printer.H
        syntax/Skeleton.C
        syntax/Skeleton.H
        syntax/ParserError.H
        typecheck/Classes.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR} syntax/)

add_executable(
        compiler
        main.cpp
        ${BNFC_SOURCES}
        ${FLEX_SCANNER_OUTPUTS}
        ${BISON_PARSER_OUTPUTS}
        typecheck/TypeChecker.cpp
        typecheck/TypeChecker.h
        typecheck/BaseTypes.cpp
        intermediate/StingrayTypes.cpp
        intermediate/StingrayTypes.h
        typecheck/Expressions.cpp
        typecheck/Statements.cpp
        typecheck/Unused.cpp
        typecheck/TopLevelDeclarations.cpp
        intermediate/LayeredTable.h
        interpretation/InterpretationVisitor.h
        interpretation/InterpretationVisitor.cpp
        interpretation/Expressions.cpp
        interpretation/Statements.cpp
        interpretation/TopLevelDeclarations.cpp
        interpretation/Unused.cpp
        intermediate/RuntimeValues.h intermediate/RuntimeValues.cpp)

target_include_directories(compiler PRIVATE ${CMAKE_SOURCE_DIR})