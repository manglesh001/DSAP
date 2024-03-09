#include <iostream>
#include <vector>
#include <utility>
using namespace std;
template <typename Key, typename Value>
class MyOrderedMap {
private:
    struct Node 
    {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;
        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };
    Node* root;
    Node* findMinNode(Node* node) {
        while(node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }
    int balFactor(Node* node) {
        if(node == nullptr)
            return 0;
        return getH(node->left) - getH(node->right);
    }
    int getH(Node* node) {
        if (node == nullptr) 
            return 0;
        return node->height;
    }

    Node* RL(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(getH(x->left), getH(x->right));
        y->height = 1 + max(getH(y->left), getH(y->right));
        return y;
    }

    Node* RR(Node* y) 
    {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(getH(y->left), getH(y->right));
        x->height = 1 + max(getH(x->left), getH(x->right));

        return x;
    }

    

    Node* insertNode(Node* node, const Key& key, const Value& value) 
    {
        if(node == nullptr) 
            return new Node(key, value);
        if (key < node->key) {
            node->left = insertNode(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertNode(node->right, key, value);
        } else {
            return node;
    }

        node->height = 1 + max(getH(node->left), getH(node->right));

        int bal = balFactor(node);

        if (bal < -1 && key > node->right->key)
         {
            return RL(node);
        }
        if (bal > 1 && key < node->left->key) 
        {
            return RR(node);
        }

         if (bal < -1 && key < node->right->key) 
         {
            node->right = RR(node->right);
            return RL(node);
        }
        
        if (bal > 1 && key > node->left->key) 
        {
            node->left = RL(node->left);
            return RR(node);
        }
        return node;
    }


   
 void keysInOrder(Node* node, vector<Key>& result) 
 {
        if (node == nullptr)
            return;
        keysInOrder(node->left, result);
        result.push_back(node->key);
        keysInOrder(node->right, result);
    }
    bool containsNode(Node* node, const Key& key) 
    {
        if (node == nullptr) 
            return false;
        if (key < node->key) 
            return containsNode(node->left, key);
        else if (key > node->key) 
            return containsNode(node->right, key);
        else 
            return true;
        
    }
     int getSize(Node* node) 
     {
        if (node == nullptr) 
        {
            return 0;
        }
        return 1 + getSize(node->left) + getSize(node->right);
    }


    Node* findNode(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr; 
        }

        if (key==node->key) 
        {
            return node; 
        } else if (key < node->key) {
            return findNode(node->left, key); 
        } else {
            return findNode(node->right, key); 
        }
    }

   
 Node* deleteNode(Node* node, const Key& key)
    {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
    
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left != nullptr) ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            }
             else {
                Node* temp = findMinNode(node->right);

                node->key = temp->key;
                node->value = temp->value;

                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + max(getH(node->left), getH(node->right));

        int bal = balFactor(node);
 
        if (bal < -1 && balFactor(node->right) <= 0) {
            return RL(node);
        }
    
        if (bal > 1 && balFactor(node->left) >= 0) {
            return RR(node);
        }

       if (bal < -1 && balFactor(node->right) > 0) {
            node->right = RR(node->right);
            return RL(node);
        }

        
        if (bal > 1 && balFactor(node->left) < 0) {
            node->left = RL(node->left);
            return RR(node);
        }

        
        

        return node;
    }
   
public:
    MyOrderedMap() : root(nullptr) {}
bool erase(const Key& key)
 {
        int initialSize = size();
        root = deleteNode(root, key);
        return size() < initialSize;
    }
    bool empty()
     {
        return root == nullptr;
    }
     vector<Key> keys()
  {
        vector<Key> result;
        keysInOrder(root, result);
        return result;
    }
    

    bool contains(const Key& key)
     {
        return containsNode(root, key);
    }
int size() 
{
        return getSize(root);
    }
    

    
    bool insert(const Key& key, const Value& value) 
    {
        int initialSize = size();
        root = insertNode(root, key, value);
        return size() > initialSize;
    }

    void clear() 
    {
        while(root != nullptr) 
        {
            root = deleteNode(root, root->key);
        }
    }

    ~MyOrderedMap() {
        clear();
    }
  pair<bool, Key> upper_bound(const Key& key, Node* node) 
  {
        Node* curr = root;
        Key ub = Key();
        bool found = false;
        while (curr != nullptr) {
        if(curr->key == key) 
        {
            ub = curr->key;
            found = true;
                break;
        }
        else if(curr->key < key)
         {
                curr = curr->right;
        } 
        else 
        {
                ub = curr->key;
                curr = curr->left;
        }
        }

        return make_pair(found, ub);
    }
    

    
     Value& operator[](const Key& key) 
    {
        Node* foundNode = findNode(root, key);
        if (foundNode != nullptr) {
            return foundNode->value;
        } else {
            
            Value defaultValue = Value(); 
            root = insertNode(root, key, defaultValue);
            return findNode(root, key)->value;
        }
    }
    pair<bool, Key> lower_bound(const Key& key) 
    {
        return lower_bound(key, root);
    }

    pair<bool, Key> upper_bound(const Key& key) 
    {
        return upper_bound(key, root);
    }

    pair<bool, Key> lower_bound(const Key& key, Node* node)
     {
        Node* curr = root;
        Key lb = Key(); 
        bool found = false;

        while (curr != nullptr) {
            if (curr->key == key) {
                lb = curr->key;
                found = true;
                break;
            } else if (curr->key < key) {
                lb = curr->key;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        return make_pair(found, lb);
    }

  
};

    int solve(vector<vector<int>>& vec) {
      MyOrderedMap<pair<int , int> , int > m;
    int cnt = 0;
    for(vector v : vec){
        int a = v[0];
      int  b = v[1];
        if(a > b) 
        swap(a , b);
        if(m[{a , b}])
         cnt += m[{a , b}];
        m[{a , b}]++;
    }
    return cnt;
    }
 int main() {
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(2));

    for (int i = 0; i < n; ++i) {
        cin >> v[i][0] >> v[i][1];
    }

    int result = solve(v);
    cout << result << endl;

    return 0;
}