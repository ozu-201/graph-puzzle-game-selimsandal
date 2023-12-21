#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> readWordsFromFile(const std::string& filename) {
    std::vector<std::string> words;
    std::ifstream file(filename);
    std::string word;

    while (std::getline(file, word)) {
        words.push_back(word);
    }

    return words;
}

#include "List/Graph/Graph.h"
#include <unordered_map>

bool isOneLetterDifferent(const std::string& word1, const std::string& word2) {
    if (word1.length() != word2.length()) return false;

    int diffCount = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) {
            if (++diffCount > 1) return false;
        }
    }
    return diffCount == 1;
}

list::Graph buildGraph(const std::vector<std::string>& words) {
    list::Graph graph(words.size());
    std::unordered_map<std::string, int> wordToIndex;

    for (int i = 0; i < words.size(); ++i) {
        wordToIndex[words[i]] = i;
    }

    for (int i = 0; i < words.size(); ++i) {
        for (int j = i + 1; j < words.size(); ++j) {
            if (isOneLetterDifferent(words[i], words[j])) {
                graph.addEdge(i, j);
                graph.addEdge(j, i); // Since the graph is undirected
            }
        }
    }

    return graph;
}

#include <queue>
#include <unordered_map>

std::vector<int> findPath(list::Graph& graph, int start, int target) {
    std::queue<int> queue;
    std::unordered_map<int, int> predecessors;
    std::vector<int> path;
    bool found = false;

    queue.push(start);
    while (!queue.empty() && !found) {
        int current = queue.front();
        queue.pop();

        // Here, you need to iterate over neighbors of 'current'
        // For example, using a method like 'graph.getNeighbors(current)'
        for (int neighbor : graph.getNeighbors(current)) {
            if (predecessors.find(neighbor) == predecessors.end()) {
                predecessors[neighbor] = current;
                queue.push(neighbor);

                if (neighbor == target) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) return path;

    for (int at = target; at != start; at = predecessors[at]) {
        path.push_back(at);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

// Assume the following functions are defined elsewhere
std::vector<std::string> readWordsFromFile(const std::string& filename);
list::Graph buildGraph(const std::vector<std::string>& words);
std::vector<int> findPath(list::Graph& graph, int start, int target);

int main() {
    // Load words from files
    std::vector<std::string> englishWords = readWordsFromFile("english.txt");
    std::vector<std::string> turkishWords = readWordsFromFile("turkish.txt");

    // Combine English and Turkish words into one vector
    std::vector<std::string> combinedWords = englishWords;
    combinedWords.insert(combinedWords.end(), turkishWords.begin(), turkishWords.end());

    // Build the graph
    list::Graph wordGraph = buildGraph(combinedWords);

    // Example usage: Find a path from one word to another
    std::string startWord = "cat"; // Example start word
    std::string targetWord = "dog"; // Example target word

    // Find indices of start and target words
    int startIndex = -1, targetIndex = -1;
    for (int i = 0; i < combinedWords.size(); i++) {
        if (combinedWords[i] == startWord) startIndex = i;
        if (combinedWords[i] == targetWord) targetIndex = i;
    }

    if (startIndex == -1 || targetIndex == -1) {
        std::cout << "Start or target word not found in dictionary." << std::endl;
        return 1;
    }

    // Find the path
    std::vector<int> path = findPath(wordGraph, startIndex, targetIndex);

    // Print the path
    if (!path.empty()) {
        std::cout << "Path from " << startWord << " to " << targetWord << ":" << std::endl;
        for (int index : path) {
            std::cout << combinedWords[index] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}