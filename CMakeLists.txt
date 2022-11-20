cmake_minimum_required(VERSION 3.16)
project(block_chain)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(classes)
include_directories(functions)
include_directories(base)
include_directories(ui)
include_directories(test)
include_directories(utils)

add_executable(block_chain
        classes/BPlusTree.h
        classes/DoubleList.h
        classes/Hash.h
        classes/Heap.h
        classes/nodes.h
        functions/hashFunctions.h
        base/block.h
        base/Blockchain.h
        base/transaction.h
        ui/button.h
        ui/gui.h
        ui/word.h
        main.cpp
        ui/input.h ui/password.h)

target_link_libraries(
    ${PROJECT_NAME}  sfml-system sfml-window sfml-graphics sfml-audio
)
