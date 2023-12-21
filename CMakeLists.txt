cmake_minimum_required(VERSION 3.25)
project(main)

set(CMAKE_CXX_STANDARD 17)

add_library(Exam_CPP Array/Graph/Graph.cpp Array/Graph/Graph.h General/AbstractGraph.cpp
        General/AbstractGraph.cpp General/Path.cpp General/Path.h Array/DisjointSet.cpp Array/DisjointSet.h
        Array/Element.h Array/Element.cpp Array/Hash.cpp Array/Hash.h Array/Queue.h Array/Queue.cpp
        Array/Set.cpp Array/Set.h Array/Stack.h Array/Stack.cpp Array/Heap/DHeap.cpp Array/Heap/DHeap.h
        Array/Heap/Heap.cpp Array/Heap/Heap.h Array/Heap/HeapNode.cpp Array/Heap/HeapNode.h Array/Heap/MaxDHeap.cpp
        Array/Heap/MaxDHeap.h Array/Heap/MaxHeap.cpp Array/Heap/MaxHeap.h Array/Heap/MinDHeap.cpp Array/Heap/MinDHeap.h
        Array/Heap/MinHeap.cpp Array/Heap/MinHeap.h Tree/Tree.cpp Tree/Tree.h Tree/TreeNode.cpp Tree/TreeNode.h
        List/Graph/Edge.cpp List/Graph/Edge.h List/Graph/EdgeList.cpp List/Graph/EdgeList.h List/DoublyLinkedList.h
        List/DoublyLinkedList.cpp List/DoublyNode.h List/DoublyNode.cpp List/Hash.h List/Hash.cpp List/LinkedList.h
        List/LinkedList.cpp List/Node.h List/Node.cpp List/Queue.cpp List/Queue.h List/Stack.cpp List/Stack.h
        Tree/Queue.h Tree/Queue.cpp Tree/Stack.h Tree/Stack.cpp Tree/Element.h Tree/Element.cpp)


add_executable(main main.cpp)
target_link_libraries(main Exam_CPP)
