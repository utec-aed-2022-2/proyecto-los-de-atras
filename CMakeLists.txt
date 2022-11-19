cmake_minimum_required(VERSION 3.16)
project(block_chain)
set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(class)
include_directories(function)
include_directories(Base)
include_directories(ui)
include_directories(test)

add_executable(block_chain
        class/BPlusTree.h
        class/DoubleList.h
        class/Hash.h
        class/Heap.h
        class/nodes.h
        function/hashFunctions.h
        Base/block.h
        Base/Blockchain.h
        Base/transaction.h
        ui/button.h
        ui/gui.h
        ui/word.h
        main.cpp
        test/test.h
        )

target_link_libraries(
    ${PROJECT_NAME}  sfml-system sfml-window sfml-graphics sfml-audio
)
