#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val=-1;
    vector<Node*> children;
};

Node* parse(string s) {
    int depth = 0;
    Node *node = new Node;

    if (s[0] != '[') {
        node->val = stoi(s);
        return node;
    }

    int i = 0;
    for (int j = 0; j < s.length(); j++) {
        if (s[j] == '[') {
            depth++;
            if (depth == 1) {
                i = j+1;
            }
            continue;
        }
        if (s[j] == ']') {
            depth--;
            if (depth == 0 && i != j) {
                node->children.push_back(parse(s.substr(i, j-i)));
            }
            continue;
        }
        if (depth == 1 && s[j] == ',') {
            node->children.push_back(parse(s.substr(i, j-i)));
            i = j+1;
        }
    }
    return node;
}

int nodeLess(Node *&n1, Node *&n2) {
    if (n1->val != -1 && n2->val != -1) {
        if (n1->val > n2->val) return -1;
        return n1->val < n2->val;
    }
    if (n1->val == -1 && n2-> val != -1) {
        Node *c = new Node;
        c->children.push_back(n2);
        n2 = c;
    }
    if (n1->val != -1 && n2->val == -1) {
        Node *c = new Node;
        c->children.push_back(n1);
        n1 = c;
    }

    for (int i = 0;; i++) {
        if (i >= n1->children.size() || i >= n2->children.size()) {
            if (n1->children.size() > n2->children.size()) return -1;
            return n1->children.size() < n2->children.size();
        }
        int ret;
        if (ret = nodeLess(n1->children[i], n2->children[i])) {
            return ret;
        }
    }
}

int main() {
    string s1, s2;
    Node *n1, *n2;
    int res = 0;
    int index = 0;
    while (cin >> s1 >> s2) {
        index++;
        n1 = parse(s1);
        n2 = parse(s2);
        if (nodeLess(n1, n2) == 1) {
            res += index;
        }
    }
    cout << res << "\n";
}
