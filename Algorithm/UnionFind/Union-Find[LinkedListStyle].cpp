#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int value;
    Node* parent;
    int rank;

    Node(int val) : value(val), parent(this), rank(0) {}
};

class UnionFind {
private:
    unordered_map<int, Node*> nodes;

public:
    Node* Parentfind(int value) {
        if (nodes.find(value) == nodes.end()) {
            return nullptr;
        }

        Node* node = nodes[value];
        if (node->parent != node) {
            node->parent = Parentfind(node->parent->value);
        }

        return node->parent;
    }

    void union_sets(int value1, int value2) {
        Node* node1 = nodes.find(value1) != nodes.end() ? nodes[value1] : new Node(value1);
        Node* node2 = nodes.find(value2) != nodes.end() ? nodes[value2] : new Node(value2);

        Node* root1 = Parentfind(node1->value);
        Node* root2 = Parentfind(node2->value);

        if (root1 == nullptr || root2 == nullptr || root1 == root2) {
            return;
        }

        if (root1->rank < root2->rank) {
            root1->parent = root2;
        }
        else if (root1->rank > root2->rank) {
            root2->parent = root1;
        }
        else {
            root2->parent = root1;
            root1->rank++;
        }
    }

    void make_set(int value) {
        if (nodes.find(value) == nodes.end()) {
            nodes[value] = new Node(value);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    UnionFind ziphap;
    int node_count;
    cout << "노드의 개수를 입력하세요: ";
    cin >> node_count;
    for (int i = 1; i <= node_count; i++) {
        ziphap.make_set(i);
    }

    int link_count, link1, link2;
    cout << "연결 시킬 간선의 개수를 입력하세요: ";
    cin >> link_count;
    while (link_count--) {
        cout << "연결 시킬 노드 두 개를 입력하세요: ";
        cin >> link1 >> link2;
        ziphap.union_sets(link1, link2);
    }
    cout << "확인할 노드 세트 개수를 입력하세요: ";
    cin >> link_count;
    while (link_count--) {
        cout << "확인할 노드 두 개를 입력하세요: ";
        cin >> link1 >> link2;
        cout << link1 << "과 " << link2 << "는 ";
        if (ziphap.Parentfind(link1) == ziphap.Parentfind(link2)) {
            cout << "연결되어 있습니다.\n";
        }
        else {
            cout << "연결되어 있지 않습니다.\n";
        }
    }
}