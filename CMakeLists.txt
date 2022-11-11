cmake_minimum_required(VERSION 3.16)
project(blockchain)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(class)
include_directories(function)
include_directories(test/*.csv)

add_executable(blockchain
        class/BPlusTree.h
        class/DoubleList.h
        class/HashMap.h
        class/nodes.h
        function/BoyerMoore.h
        function/hashFunctions.h
        function/stringToLong.h
        function/unixToDate.h
        test/test.h
        block.h
        BlockChain.h
        main.cpp
        transaction.h ui/Gui.h)

target_link_libraries(${PROJECT_NAME}  sfml-system sfml-window sfml-graphics sfml-audio)