#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib> 
using namespace std;
template <typename T>
class Treap
{
private:
    struct TreapNode
    {
        T val;
        int priority, size;
        TreapNode *left, *right;
        TreapNode(T v) : val(v), priority(rand() % 100), size(1), left(nullptr), right(nullptr) {}
    };

    TreapNode *root;
 void updateSize(TreapNode *node)
    {
        if (node!=NULL)
        {
            node->size = 1 + getSize(node->left) + getSize(node->right);
        }
    }

       int getSize(TreapNode *root)
    {
        if (root==NULL)
            return 0;
        return  root->size;
    }
   

   

    TreapNode *leftRotate(TreapNode *x)
    {
        TreapNode *y = x->right;
        TreapNode *T2 = y->left;

        
        x->right = T2;
        y->left = x;
        updateSize(x);
        updateSize(y);

        return y;
    }
     TreapNode *rightRotate(TreapNode *y)
    {
        TreapNode *x = y->left;
        TreapNode *T2 = x->right;

        y->left = T2;

        x->right = y;
        updateSize(y);
        updateSize(x);

        return x;
    }
    void clearTree(TreapNode *root)
    {
        if (!root)
            return;

        clearTree(root->left);
        clearTree(root->right);

        delete root;
    }

    int indexOf(TreapNode *root, T val, int &index)
    {
        if (!root)
            return -1;

        int leftSize = getSize(root->left);

        if (val == root->val)
        {
            index += leftSize;
            return index;
        }
        else if (val < root->val)
        {
            return indexOf(root->left, val, index);
        }
        else
        {
            index += leftSize + 1;
            return indexOf(root->right, val, index);
        }
    }
    TreapNode *insert(TreapNode *root, T val, int &index)
    {
        if (!root)
        {
            index = 0;
            return new TreapNode(val);
        }

        if (val <= root->val)
        {
            root->left = insert(root->left, val, index);

            if (root->left->priority > root->priority)
                root = rightRotate(root);

            updateSize(root);
            updateSize(root->left);   
        }
        else
        {
            int leftSize = getSize(root->left) + 1;
            
            root->right = insert(root->right, val, index);
            index += leftSize;

            if (root->right->priority > root->priority)
                root = leftRotate(root);

            updateSize(root);
            updateSize(root->right);  
        }

        
     
        return root;
    }

    TreapNode *search(TreapNode *root, T val)
    {
        if (!root || root->val == val)
            return root;

        if (val < root->val)
            return search(root->left, val);

        return search(root->right, val);
    }

pair<TreapNode*, bool> erase1(TreapNode* root, int index) {
    if (!root || index < 0 || index >= root->size)
        return {root, false};  

    int leftSize = getSize(root->left);

    if (index < leftSize) {
        auto result = erase1(root->left, index);
        root->left = result.first;
        updateSize(root);  
        return {root, result.second};
    } else if (index > leftSize) {
        auto result = erase1(root->right, index - leftSize - 1);
        root->right = result.first;
        updateSize(root);  
        return {root, result.second};
    } else {
      
        auto temp = root;
        root = merge(root->left, root->right);
        delete temp;
        return {root, true};
    }
}

 pair<TreapNode *, TreapNode *> split(TreapNode *root, int index, int &currentIndex)
{
    if (!root)
        return {nullptr, nullptr};

    int leftSize = getSize(root->left);

    if (index < leftSize)
    {
        auto leftRightPair = split(root->left, index, currentIndex);
        root->left = leftRightPair.second;
        updateSize(root);  
        return {leftRightPair.first, root};
    }
    else if (index > leftSize)
    {
        auto leftRightPair = split(root->right, index - leftSize - 1, currentIndex);
        root->right = leftRightPair.first;
        updateSize(root);  
        return {root, leftRightPair.second};
    }
    else
    {
        currentIndex = leftSize;
        updateSize(root);
        return {root->left, root->right};
    }
}





    int count(TreapNode* root, T val) {
    if (!root)
        return 0;

    int cnt = 0;

    if (val == root->val)
        cnt++;

    cnt += count(root->left, val);
    cnt += count(root->right, val);

    return cnt;
}


    void toArray(TreapNode *root, vector<T> &result)
    {
        if (!root)
            return;

        toArray(root->left, result);
        result.push_back(root->val);
        toArray(root->right, result);
    }
    

    T atIndex(TreapNode *root, int index, int &currentIndex)
    {
        if (!root)
            return T(); 

        int leftSize = getSize(root->left);

        if (index == leftSize)
        {
            currentIndex = leftSize;
            return root->val;
        }
        else if (index < leftSize)
        {
            return atIndex(root->left, index, currentIndex);
        }
        else
        {
            currentIndex = leftSize + 1;
            return atIndex(root->right, index - leftSize - 1, currentIndex);
        }
    }

    int upperBound(TreapNode *root, T val, int &count)
    {
        if (!root)
            return count;

        if (val < root->val)
        {
            return upperBound(root->left, val, count);
        }
        else
        {
            count += getSize(root->left) + 1;
            return upperBound(root->right, val, count);
        }
    }
        pair<TreapNode *, bool> eraseRange(TreapNode *root, int first, int last)
    {
        int currentIndex = 0;
        auto leftPair = split(root, first, currentIndex);
        auto rightPair = split(leftPair.second, last - first-1, currentIndex);

        clearTree(rightPair.first);

        root = merge(leftPair.first, rightPair.second);
        updateSize(root);
        return {root, currentIndex == first};
    }

    TreapNode *merge(TreapNode *t1, TreapNode *t2)
    {
        if (!t1)
        {
            updateSize(t2);
            return t2;
        }
        if (!t2)
        {
            updateSize(t1);
            return t1;
        }

        if (t1->priority > t2->priority)
        {
            t1->right = merge(t1->right, t2);
            updateSize(t1);
            return t1;
        }
        else
        {
            t2->left = merge(t1, t2->left);
            updateSize(t2);
            return t2;
        }
    }

   
    int lowerBound(TreapNode *root, T val, int &count)
    {
        if (!root)
            return count;

        if (val <= root->val)
        {
            return lowerBound(root->left, val, count);
        }
        else
        {
            count += getSize(root->left) + 1;
            return lowerBound(root->right, val, count);
        }
    }


    TreapNode *slice(TreapNode *root, int first, int last, int &currentIndex)
    {
        auto leftPair = split(root, first - 1, currentIndex);
        auto rightPair = split(leftPair.second, last - first, currentIndex);

        return rightPair.first;
    }


public:
    Treap() : root(nullptr) {}

    int insert(T val)
    {
        int index = 0;
        root = insert(root, val, index);
        return index;
    }
    bool erase(int index)
    {
        bool ans;
        root = erase1(root, index).first;
        if(root==NULL)
            return false;
        else
        return true;
    }

    bool search(T val)
    {
        return search(root, val) != nullptr;
    }

    int indexOf(T val)
    {
        int index = 0;
        return indexOf(root, val, index);
    }

    T atIndex(int index)
    {
        int currentIndex = 0;
        return atIndex(root, index, currentIndex);
    }

    pair<TreapNode *, TreapNode *> split(int index)
    {
        int currentIndex = 0;
        return split(root, index, currentIndex);
    }

    Treap<T> *merge(Treap<T> *t2)
    {
        Treap<T> *newTreap = new Treap<T>();
        newTreap->root = merge(root, t2->root);
        return newTreap;
    }

    bool empty()
    {
        return root == nullptr;
    }

    int size()
    {
        return getSize(root);
    }

    void clear()
    {
        clearTree(root);
        root = nullptr;
    }

    void inorderTraversal()
    {
        printTree(root, 0);
    }

    int lower_bound(T val)
    {
        int count = 0;
        return lowerBound(root, val, count);
    }

    int upper_bound(T val)
    {
        int count = 0;
        return upperBound(root, val, count);
    }

    int count(T val)
    {
        return count(root, val);
    }

    vector<T> to_array()
    {
        vector<T> result;
        toArray(root, result);
        return result;
    }

        bool erase(int first, int last)
    {
        auto result = eraseRange(root, first, last);
        root = result.first;
        return result.second;
    }

    Treap<T> *slice(int first, int last)
    {
        int currentIndex = 0;
        auto slicedRoot = slice(root, first, last, currentIndex);

        Treap<T> *slicedTreap = new Treap<T>();
        slicedTreap->root = slicedRoot;
          slicedTreap->updateSize(slicedTreap->root);
        return slicedTreap;
    }
};

int main() {
    Treap<int> t;
    int choice;
 
        cout << "Enter your choice: ";
    while (true) {
       
        cin >> choice;

        if (choice == 0) {
            break;
        }

         switch (choice) {
            case 1:
                cout << (t.empty() ? "true" : "false") << endl;
                break;
            case 2:
                cout << t.size() << endl;
                break;
            case 3:
                t.clear();
                break;
            case 4:
                int val;
                cin >> val;
                cout<< t.insert(val) << endl;
                
                break;
            case 5:
                int index;
                cin >> index;
                cout << (t.erase(index) ? "true" : "false") << endl;
                break;
            case 6:
                cin >> val;
                cout << t.indexOf(val) << endl;
                break;
            case 7:
                cin >> index;
                cout << t.atIndex(index) << endl;
                break;
            case 8: {
                Treap<int> t2;
                int val;
                while (true) {
                    cin >> val;
                    if (val == -1) break;
                    t2.insert(val);
                }
                Treap<int>* merged = t.merge(&t2);
                delete merged;
                break;
            }
            case 9: {
                int index;
                cin >> index;
                auto [leftTreap, rightTreap] = t.split(index);
                 leftTreap;
                 rightTreap;
                break;
            }
            case 10:
                int first, last;
                cin >> first >> last;
                cout << (t.erase(first, last) ? "false" : "true") << endl;
                break;
            case 11: {
                int first, last;
                cin >> first >> last;
                Treap<int>* sliced = t.slice(first, last);
                delete sliced;
                break;
            }
            case 12:
                cin >> val;
                cout << t.lower_bound(val) << endl;
                break;
            case 13:
                cin >> val;
                cout << t.upper_bound(val) << endl;
                break;
            case 14:
                cin >> val;
                cout << t.count(val) << endl;
                break;
            case 15: {
                vector<int> arr = t.to_array();
                for (int num : arr) {
                    cout << num << " ";
                }
                cout << endl;
                break;
            }
            default:
                cout << "Invalid choice" << endl;
        }
     }

    return 0;
}


//Question B
// class Solution {
// public:
//     vector<int> countSmaller(vector<int>& nums) {
     
//     int n = nums.size();
//     vector<int> counts(n, 0);
//     Treap<int> t;

//     for (int i = n - 1; i >= 0; i--) {
//         t.insert(nums[i]);
//         int smallerCount = t.lower_bound(nums[i]);
//         counts[i] = smallerCount;
//     }

//     return counts;
        
//     } 
// };
