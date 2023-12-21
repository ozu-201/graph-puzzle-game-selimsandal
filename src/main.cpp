#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>

class WordGraph {
    std::vector<std::string> nodes;
    std::vector<std::vector<int>> links;

    bool Diff(const std::string& a, const std::string& b) const {
        int count = 0;
        for (size_t i = 0; i < a.length(); ++i) {
            if (a[i] != b[i] && ++count > 1) return false;
        }
        return count == 1;
    }

    void createLinks() {
        size_t size = nodes.size();
        links.assign(size, std::vector<int>(size, 0));

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = i + 1; j < size; ++j) {
                if (Diff(nodes[i], nodes[j])) {
                    links[i][j] = links[j][i] = 1;
                }
            }
        }
    }

public:
    WordGraph(int length, const std::string& file) {
        std::ifstream inFile(file);
        if (!inFile) {
            std::cerr << "Error opening file: " << file << std::endl;
            exit(1);
        }

        std::string word;
        while (std::getline(inFile, word)) {
            if (word.length() == length) {
                nodes.push_back(word);
            }
        }

        createLinks();
    }

    std::vector<std::string> findPath(const std::string& start, const std::string& end) {
        auto findIndex = [this](const std::string& word) -> int {
            auto it = std::find(nodes.begin(), nodes.end(), word);
            return it != nodes.end() ? it - nodes.begin() : -1;
        };

        int startIndex = findIndex(start), endIndex = findIndex(end);
        if (startIndex == -1 || endIndex == -1) {
            return {"Word not found"};
        }

        std::vector<int> prev(nodes.size(), -1);
        std::queue<int> q;
        q.push(startIndex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == endIndex) {
                std::vector<std::string> path;
                for (int at = endIndex; at != startIndex; at = prev[at]) {
                    path.push_back(nodes[at]);
                }
                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (size_t i = 0; i < nodes.size(); ++i) {
                if (links[current][i] && prev[i] == -1) {
                    prev[i] = current;
                    q.push(i);
                }
            }
        }

        return {"Path not found"};
    }
};

void displayPath(const std::vector<std::string>& path) {
    for (const auto& word : path) {
        std::cout << word << " -> ";
    }
    std::cout << "\b\b\b   " << std::endl;  // Erase last arrow
}

int main() {
    WordGraph wg(4, "/Users/selimsandal/Developer/graph-puzzle-game-selimsandal/english.txt");
    auto solution = wg.findPath("cora", "tree");
    displayPath(solution);
    return 0;
}
