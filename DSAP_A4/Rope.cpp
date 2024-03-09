#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstdlib> 
using namespace std;
class Rope {
private:
    struct Node {
        string data;
        int length;
        Node* left;
        Node* right;

        Node(const string& str) : data(str), length(str.length()), left(nullptr), right(nullptr) {}
    };

    Node* root;

    int getLength(Node* node) {
        return node ? node->length : 0;
    }


    Node* merge(Node* left, Node* right) {
    Node* merged = new Node("");
    merged->left = left;
    merged->right = right;
    merged->length = getLength(left);
    if (left) {
        merged->length += getLength(left->right);
    }
    if (right) {
        merged->length += getLength(right->left);
    }
    return merged;
}

// Node* merge(Node* left, Node* right) {
//     Node* merged = new Node("");
//     merged->left = left;
//     merged->right = right;
//     merged->length = getLength(left) + getLength(right);
//     return merged;
// }


 pair<Node*, Node*> splitt(Node* node, int position) {
    if (!node) {
        return {nullptr, nullptr};
    }

    int leftLength = getLength(node->left);

    if (position < leftLength) {
        auto [left, right] = splitt(node->left, position);
        node->left = right;
        node->length = getLength(node->left);
        if (node->left) {
            node->length += getLength(node->left->right);
        }
        return {left, node};
    } else if (position > leftLength) {
        auto [left, right] = splitt(node->right, position - leftLength - 1);
        node->right = left;
        node->length = getLength(node->right);
        if (node->right) {
            node->length += getLength(node->right->left);
        }
        return {node, right};
    } else {
        return {node->left, node};
    }
}


    bool erase(Node*& node, int first, int last) {
        if (!node) {
            return false;
        }

        int leftLength = getLength(node->left);

        if (last < leftLength) {
            return erase(node->left, first, last);
        } else if (first >= leftLength) {
            return erase(node->right, first - leftLength, last - leftLength);
        } else {
            auto [left, right] = split(node, first);
            auto [mid, newRight] = split(right, last - first + 1);

            delete mid; 
            node = merge(left, newRight);
            return true;
        }
    }

    Node* atIndex(Node* node, int index) {
        if (!node) {
            return nullptr;
        }

        int leftLength = getLength(node->left);

        if (index < leftLength) {
            return atIndex(node->left, index);
        } else if (index >= leftLength && index < leftLength + getLength(node)) {
            return node;
        } else {
            return atIndex(node->right, index - leftLength - getLength(node));
        }
    }

    Node* pushBack(Node* node, const string& s) {
        if (!node) {
            return new Node(s);
        }

        int leftLength = getLength(node->left);

        if (rand() % (getLength(node) + 1) == 0) {
            auto [left, right] = split(node, leftLength);
            auto newNode = new Node(s);
            return merge(merge(left, newNode), right);
        } else if (getLength(node->left) >= getLength(node->right)) {
            node->right = pushBack(node->right, s);
        } else {
            node->left = pushBack(node->left, s);
        }

        node->length = getLength(node->left);
        if (node->left) {
            node->length += getLength(node->left->right);
        }

        return node;
    }

    string toString(Node* node) {
        if (!node) {
            return "";
        }
        return toString(node->left) + node->data + toString(node->right);
    }

    pair<Node*, Node*> split(Node* node, int index) {
        auto [left, right] = splitt(node, index);
        return {left, right};
    }

public:
    Rope() : root(nullptr) {}

    void rope(const string& s) {
        root = new Node(s);
    }

   
    void clear() {
      
        while (root) {
            auto temp = root;
            root = merge(root->left, root->right);
            delete temp;
        }
    }

    bool insert(int i, const string& s) {
        if (i < 0 || i > size()) {
            return false;
        }

        auto [left, right] = split(root, i);
        auto newNode = new Node(s);
        root = merge(merge(left, newNode), right);
        return true;
    }
     bool empty() {
        return root == nullptr;
    }

    int size() {
        return getLength(root);
    }


    bool erase(int first, int last) {
        if (first < 0 || last >= size() || first > last) {
            return false;
        }

        return erase(root, first, last);
    }

    char charAt(int index) {
        auto node = atIndex(root, index);
        return node ? node->data[index - getLength(node->left)] : '\0';
    }

    Rope* subrope(int first, int last) {
        auto [left, right] = split(root, first);
        auto [mid, newRight] = split(right, last - first + 1);

        Rope* subRope = new Rope();
        subRope->root = mid;

        root = merge(left, newRight);

        return subRope;
    }

    Rope* concat(Rope* r2) {
        Rope* newRope = new Rope();
        newRope->root = merge(root, r2->root);
        return newRope;
    }

    Rope* push_back(const string& s) {
        root = pushBack(root, s);
        return this;
    }

    string to_string() {
        return toString(root);
    }

    pair<Rope*, Rope*> split(int index) {
        auto [left, right] = split(root, index);

        Rope* rope1 = new Rope();
        rope1->root = left;

        Rope* rope2 = new Rope();
        rope2->root = right;

        return {rope1, rope2};
    }

    void printRope(Node* node) {
        if (node) {
            printRope(node->left);
            cout << node->data;
            printRope(node->right);
        }
    }

    void printRope() {
        printRope(root);
        cout << endl;
    }

    ~Rope() {
        clear();
    }
};

int main() {
    Rope rope;
cout << "Menu:\n";
        

        int choice;
        
    while (true) {
        
cin >> choice;
        switch (choice) {
            case 1: {
                string s;
                cout << "Enter string s: ";
                cin >> s;
                rope.rope(s);
                break;
            }
            case 2: {
                cout << (rope.empty() ? "true" : "false") << endl;
                break;
            }
            case 3: {
                cout << rope.size() << endl;
                break;
            }
            case 4: {
                rope.clear();
                break;
            }
            case 5: {
                int i;
                string s;
                cout << "Enter index i: ";
                cin >> i;
                cout << "Enter string s: ";
                cin >> s;
                cout << (rope.insert(i, s) ? "true" : "false") << endl;
                break;
            }
            case 6: {
                int first, last;
                cout << "Enter first index: ";
                cin >> first;
                cout << "Enter last index: ";
                cin >> last;
                cout << (rope.erase(first, last) ? "true" : "false") << endl;
                break;
            }
            case 7: {
                int index;
                cout << "Enter index: ";
                cin >> index;
                char result = rope.charAt(index);
                cout << result << endl;
                break;
            }
            case 8: {
                int first, last;
                cout << "Enter first index: ";
                cin >> first;
                cout << "Enter last index: ";
                cin >> last;
                Rope* subRope = rope.subrope(first, last);
                cout << "Subrope: ";
                subRope->printRope();
                cout << endl;
                break;
            }
            case 9: {
                Rope* r2 = new Rope();
                cout << "Enter string s for second rope: ";
                string s;
                cin >> s;
                r2->rope(s);
                Rope* concatenatedRope = rope.concat(r2);
                cout << "Concatenated Rope: ";
                concatenatedRope->printRope();
                cout << endl;
                break;
            }
            case 10: {
                string s;
                cout << "Enter string s: ";
                cin >> s;
                Rope* newRope = rope.push_back(s);
                cout << "New Rope: ";
                newRope->printRope();
                cout << endl;
                break;
            }
            case 11: {
                string result = rope.to_string();
                cout << "Rope content: " << result << endl;
                break;
            }
            case 12: {
                int index;
                cout << "Enter index to split at: ";
                cin >> index;
                auto [rope1, rope2] = rope.split(index);
                cout << "Rope 1: ";
                rope1->printRope();
                cout << "Rope 2: ";
                rope2->printRope();
                cout << endl;
                break;
            }
            case 0: {
                return 0;
            }
            default: {
                cout << "Invalid choice. Try again.\n";
            }
        }

        
    }

    return 0;
}
