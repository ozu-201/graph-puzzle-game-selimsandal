#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

struct Graph {
    std::vector<std::string> vertices;
    std::vector<std::vector<int>> edges;

    Graph(int wordLength, const std::string& filePath) {
        if (!loadWordsFromFile(wordLength, filePath)) {
            std::cerr << "Error: Unable to load words from the file." << std::endl;
            exit(1);
        }

        initializeEdges();
    }

    bool loadWordsFromFile(int wordLength, const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open the file: " << filePath << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.size() == wordLength) {
                vertices.push_back(line);
            }
        }

        return true;
    }

    void initializeEdges() {
        int numVertices = vertices.size();
        edges = std::vector<std::vector<int>>(numVertices, std::vector<int>(numVertices, 0));

        for (int i = 0; i < numVertices; i++) {
            for (int j = i + 1; j < numVertices; j++) {
                if (oneCharDifference(vertices[i], vertices[j])) {
                    edges[i][j] = 1;
                    edges[j][i] = 1;
                }
            }
        }
    }

    bool oneCharDifference(const std::string& first, const std::string& second) const {
        int diffCount = 0;
        for (size_t i = 0; i < first.size(); i++) {
            if (first[i] != second[i]) {
                diffCount++;
                if (diffCount > 1) {
                    return false;
                }
            }
        }
        return diffCount == 1;
    }

    std::vector<std::string> findShortestPath(const std::string& from, const std::string& to) {
        int startIdx = findWordIndex(from);
        int endIdx = findWordIndex(to);

        if (startIdx == -1) {
            return {"start word not found"};
        }
        if (endIdx == -1) {
            return {"end word not found"};
        }

        std::vector<std::string> path;
        std::vector<int> prev(vertices.size(), -1);
        std::queue<int> queue;

        queue.push(startIdx);

        while (!queue.empty()) {
            int curr = queue.front();
            queue.pop();

            if (curr == endIdx) {
                // Build the path from end to start
                while (curr != startIdx) {
                    path.push_back(vertices[curr]);
                    curr = prev[curr];
                }
                path.push_back(from); // Add the start word
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (int neighbor = 0; neighbor < vertices.size(); neighbor++) {
                if (edges[curr][neighbor] == 1 && prev[neighbor] == -1) {
                    prev[neighbor] = curr;
                    queue.push(neighbor);
                }
            }
        }

        return {"didn't reach end"};
    }

    int findWordIndex(const std::string& word) const {
        auto it = std::find(vertices.begin(), vertices.end(), word);
        if (it != vertices.end()) {
            return std::distance(vertices.begin(), it);
        }
        return -1; // Word not found
    }
};

void print(const std::vector<std::string>& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != container.end()) {
            std::cout << " <---> ";
        }
    }
    std::cout << std::endl;
}


int main() {
    Graph graph(4, "/Users/selimsandal/Developer/graph-puzzle-game-selimsandal/english.txt");
    auto path = graph.findShortestPath("cora", "cora");
    print(path);
    return 0;
}
