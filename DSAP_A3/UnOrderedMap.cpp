#include <iostream>
#include<vector>
using namespace std;
template <typename T1, typename T2>
class UnorderedMap 
{
private:
    struct Node {
        Node* next;
        T2 value;
        T1 key;
        Node(T1 k, T2 v) : key(k), value(v), next(nullptr) {}
    };
    static const int TSIZE = 100000; 
    Node* tb[TSIZE];

   int hash(T1 key) 
   {
    int mpl = 31;
    int hval = 0;
    for(size_t i = 0; i < sizeof(T1);i++) 
    {
    hval = (hval * mpl + ((reinterpret_cast<char*>(&key))[i]));
    }
    return (hval % TSIZE + TSIZE) % TSIZE;
}


public:
      bool erase(T1 key) 
    {
        int ind = hash(key);
        if(tb[ind] == nullptr) 
            return false;
        Node* curr = tb[ind];
        Node* prev = nullptr;
        while(curr != nullptr) 
        {
            if(curr->key == key) 
            {
                if(prev == nullptr) 
                
                    tb[ind] = curr->next;
                 else 
                 {
                    prev->next = curr->next;
                }
                delete curr;
                return true; 
            }
            prev = curr;
            curr = curr->next;
        }

        return false; 
    }
  T2& operator[](T1 key) 
    {
    int ind = hash(key);
    Node* curr = tb[ind];
    while(curr != nullptr) 
    {
        if(curr->key == key)
        {
            return curr->value;
        }
        curr = curr->next;
    }
    Node* newNode = new Node(key, T2());
    newNode->next = tb[ind];
    tb[ind] = newNode;
    return tb[ind]->value;
}
    bool insert(T1 key, T2 value) 
    {
        Node* newNode = new Node(key, value);
        int ind = hash(key);
        if(tb[ind] == nullptr) 
        {
            tb[ind] = newNode;
        } 
        else
        {
        Node* curr=tb[ind];
            while(curr->next != nullptr)
            {
                if(curr->key == key)
                {
                    delete newNode;
                    return false; 
                }
                curr=curr->next;
            }
            if(curr->key==key) {
                delete newNode;
                return false; 
            }
            curr->next = newNode;
        }

        return true; 
    }
    void clear()
     {
        for (int i = 0; i < TSIZE; ++i) 
        {
            Node* curr = tb[i];
            while(curr != nullptr) 
            {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
            tb[i] = nullptr;
        }
    }
UnorderedMap() 
    {
        for (int i = 0; i < TSIZE; ++i)
        {
            tb[i] = nullptr;
        }
    }
    bool contains(T1 key) 
    {
        int ind = hash(key);
        Node* curr = tb[ind];
        while (curr != nullptr) 
        {
            if(curr->key == key) 
            {
                return true; 
            }
            curr = curr->next;
        }

        return false; 
    }

  
    void keys(vector<T1>& result) {
        for(int i = 0; i < TSIZE; ++i) 
        {
            Node* curr = tb[i];
            while(curr != nullptr) 
            {
                result.push_back(curr->key);
                curr = curr->next;
            }
        }
    }

    int size() 
    {
        int count = 0;
        for(int i = 0; i < TSIZE; ++i)
         {
            Node* curr = tb[i];
            while(curr != nullptr) 
            {
                count++;
                curr = curr->next;
            }
        }
        return count;
    }

    bool empty()
    {
        return size() == 0;
    }

   
};



int main() {
    UnorderedMap<int, string> myMap;
    int q;
    cin >> q;
    while (q--) {
        int c;
        cin >> c;
        if(c == 1) 
        { 
            int key;
            string value;
            cin>>key>>value;
            if(myMap.insert(key, value)) 
            {
                cout << "true" << endl;
            } else 
            {
                cout << "false" << endl;
            }
        } else if(c == 2) 
        { 
            int key;
            cin >> key;
            if(myMap.erase(key)) 
            {
                cout << "true" << endl;
            } else 
            {
                cout << "false" << endl;
            }
        } else if(c == 3) 
        { 
            int key;
            cin >> key;
            if(myMap.contains(key))
             {
                cout <<"true"<< endl;
            } else {
                cout<<"false"<<endl;
            }
        } 
        else if(c == 4)
         { 
            int key;
            cin >> key;
            cout << myMap[key] << endl;
        }
         else if(c == 5) 
        {
            myMap.clear();
        } 
        else if(c == 6) 
        { 
            cout << myMap.size() << endl;
        } 
        else if(c == 7) { 
            if(myMap.empty())
            {
                cout << "true" << endl;
            }
            else {
                cout << "false" << endl;
            }
        }
        else if(c == 8)
        { 
            vector<int> keys;
            myMap.keys(keys);
            for (int i = 0; i < keys.size(); ++i) {
                cout << keys[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}