#include <iostream>
#include <vector>
#include <queue>
#include <chrono>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

class Node {
public:
    int freq;
    char symbol;
    Node* left;
    Node* right;

    Node(int freq, char symbol, Node* left = nullptr, Node* right = nullptr)
        : freq(freq), symbol(symbol), left(left), right(right) {}
};

void calculateHuffmanCodes(const Node* node, const string& code, map<char, string>& huffmanCodes) {
    if (node) {
        if (!node->left && !node->right) {
            huffmanCodes[node->symbol] = code;
        }
        calculateHuffmanCodes(node->left, code + "0", huffmanCodes);
        calculateHuffmanCodes(node->right, code + "1", huffmanCodes);
    }
}

void deleteHuffmanTree(Node* node) {
    if (node) {
        deleteHuffmanTree(node->left);
        deleteHuffmanTree(node->right);
        delete node;
    }
}

int main() {
    int n;
    cout << "Enter the number of unique characters: ";
    cin >> n;

    vector<char> chars(n);
    vector<int> freq(n);

    cout << "Enter the characters and their frequencies:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Character " << i + 1 << ": ";
        cin >> chars[i];
        cout << "Frequency of " << chars[i] << ": ";
        cin >> freq[i];
    }

    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, greater<pair<int, Node*>>> nodes;

    for (size_t i = 0; i < chars.size(); ++i) {
        nodes.push({freq[i], new Node(freq[i], chars[i])});
    }

    auto start_time = chrono::high_resolution_clock::now();

    Node* root = nullptr;
    while (nodes.size() > 1) {
        auto left = nodes.top().second;
        nodes.pop();
        auto right = nodes.top().second;
        nodes.pop();

        Node* newNode = new Node(left->freq + right->freq, '\0', left, right);
        nodes.push({newNode->freq, newNode});
    }

    root = nodes.top().second;
    nodes.pop();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    cout << "Huffman Tree Construction Elapsed Time: " << duration.count() << " microseconds" << endl;

    map<char, string> huffmanCodes;
    calculateHuffmanCodes(root, "", huffmanCodes);

    cout << "Huffman Codes for characters:\n";
    for (const auto& kv : huffmanCodes) {
        cout << kv.first << ": " << kv.second << endl;
    }

    double spaceUsed = 0;
    for (const auto& kv : huffmanCodes) {
        spaceUsed += kv.second.length() * freq[find(chars.begin(), chars.end(), kv.first) - chars.begin()];
    }
    spaceUsed = ceil(spaceUsed / 8);

    cout << "Estimated Space Used for Huffman Codes: " << spaceUsed << " bytes" << endl;

    deleteHuffmanTree(root);

    return 0;
}
