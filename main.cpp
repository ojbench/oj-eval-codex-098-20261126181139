#include <array>
#include <iostream>

struct Node {
    long long value = 0;
    int left = -1;
    int right = -1;
};

constexpr int kNodeCount = 7;
using Tree = std::array<Node, kNodeCount>;

bool find_rank(const Tree& tree, int node, int& rank, long long& answer) {
    if (node == -1) {
        return false;
    }
    // Reverse inorder visits a BST's values in descending order.
    if (find_rank(tree, tree[node].right, rank, answer)) {
        return true;
    }
    if (--rank == 0) {
        answer = tree[node].value;
        return true;
    }
    return find_rank(tree, tree[node].left, rank, answer);
}

int main() {
    Tree tree;
    for (int i = 0; i < kNodeCount; ++i) {
        if (!(std::cin >> tree[i].value)) {
            return 0;
        }
        if (i == 0) {
            continue;
        }
        // Level order places every ancestor before its descendants, so
        // ordinary BST insertion reconstructs the original tree.
        int current = 0;
        while (true) {
            int& child = tree[i].value < tree[current].value
                             ? tree[current].left
                             : tree[current].right;
            if (child == -1) {
                child = i;
                break;
            }
            current = child;
        }
    }

    int rank;
    if (!(std::cin >> rank) || rank < 1 || rank > kNodeCount) {
        return 0;
    }
    long long answer = 0;
    if (find_rank(tree, 0, rank, answer)) {
        std::cout << answer << '\n';
    }
}
