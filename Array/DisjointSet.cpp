//
// Created by Olcay Taner YILDIZ on 6.05.2023.
//

#include "DisjointSet.h"

DisjointSet::DisjointSet(int *elements, int count) {
    sets = new Set[count];
    for (int i = 0; i < count; i++){
        sets[i] = Set(elements[i], i);
    }
    this->count = count;
}

DisjointSet::~DisjointSet() {
    delete[] sets;
}

int DisjointSet::findSetRecursive(int index) {
    int parent = sets[index].getParent();
    if (parent != index){
        return findSetRecursive(parent);
    }
    return parent;
}

int DisjointSet::findSetIterative(int index) {
    int parent = sets[index].getParent();
    while (parent != index){
        index = parent;
        parent = sets[index].getParent();
    }
    return parent;
}

DisjointSet::DisjointSet(int count) {
    sets = new Set[count];
    for (int i = 0; i < count; i++){
        sets[i] = Set(i, i);
    }
    this->count = count;
}
