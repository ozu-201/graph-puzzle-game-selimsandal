//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include "Graph.h"
#include "../../Array/DisjointSet.h"
#include "../Queue.h"
#include "../../Array/Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    void Graph::addEdge(int from, int to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges[from].insert(edge);
    }

    Graph::~Graph() {
        delete[] edges;
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::breadthFirstSearch(bool *visited, int startNode) {
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();
            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::breadthFirstSearchWithTracking(bool *visited, int startNode) {
        std::unordered_map<int, int> parentMap; // to keep track of parents
        std::vector<int> path; // to store the path for a particular node
        Edge* edge;
        int fromNode, toNode;

        Queue queue = Queue();
        queue.enqueue(new Node(startNode));
        parentMap[startNode] = -1; // startNode has no parent
        visited[startNode] = true;

        while (!queue.isEmpty()) {
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();

            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]) {
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                    parentMap[toNode] = fromNode; // set the parent of toNode
                }
                edge = edge->getNext();
            }
        }
    }

}