#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<int, vector<int>> tree;
set<int> children;
int height = 0;

void preorder(int node) {
    cout << node << " ";
    for (int child : tree[node]) {
        preorder(child);
    }
}

void postorder(int node) {
    for (int child : tree[node]) {
        postorder(child);
    }
    cout << node << " ";
}

void inorder(int node) {
    if (tree[node].size() > 2) {
        cout << "NOT BINARY TREE";
        exit(0);
    }
    if (tree[node].size() >= 1)
        inorder(tree[node][0]);
    cout << node << " ";
    if (tree[node].size() == 2)
        inorder(tree[node][1]);
}

int getHeight(int node) {
    int h = 0;
    for (int child : tree[node]) {
        h = max(h, getHeight(child));
    }
    return h + 1;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        children.insert(v);
    }

    // Tìm root (nút không là con của ai)
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (children.find(i) == children.end()) {
            root = i;
            break;
        }
    }

    // Chiều cao
    cout << getHeight(root) << endl;

    // Duyệt tiền tự
    preorder(root);
    cout << endl;

    // Duyệt hậu tự
    postorder(root);
    cout << endl;

    // Kiểm tra cây nhị phân
    bool isBinary = true;
    for (auto p : tree) {
        if (p.second.size() > 2) {
            isBinary = false;
            break;
        }
    }

    if (isBinary) {
        inorder(root);
        cout << endl;
    } else {
        cout << "NOT BINARY TREE" << endl;
    }

    return 0;
}
