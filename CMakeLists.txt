cmake_minimum_required(VERSION 3.25)
project(SDIZO2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")

add_executable(SDIZO2 main.cpp Graphs/AdjacencyMatrix.cpp Graphs/AdjacencyMatrix.h Graphs/Edge.cpp Graphs/Edge.h Tools/FileClass.cpp Tools/Generator.cpp Tools/Timer.cpp Menu/Menu.cpp Menu/Menu.h Graphs/AdjacencyList.cpp Graphs/AdjacencyList.h Graphs/ListElement.cpp Graphs/ListElement.h Tools/SetNode.cpp Tools/SetNode.h Tools/Set.cpp Tools/Set.h Tools/Heap.cpp Tools/HeapSSSP.cpp Tools/HeapSSSP.h Tools/HeapSSSPelement.cpp Tools/HeapSSSPelement.h Tools/CostAndPrevElement.cpp Tools/CostAndPrevElement.h Tools/CostAndPrevElement.h Tools/Array.h Tools/Array.cpp)
