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
        for(int i = 0; i<TSIZE; ++i)
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

    int solve(int arr[], int k,int n) 
    {
          int count=0;
           UnorderedMap<int,int> ump;
           int sum=0;
            ump.insert(0,1);
        for(int i=0;i<n;i++){
            sum=arr[i]+sum;
            if(ump[sum-k])
            {
                count=ump[sum-k]+count;
            }
            ump[sum]++;
        }
        return count;
    }

int main()
{
    int n;
    cin>>n;
    int k;
    cin>>k;
    int arr[n];
    for(int i=0;i<n;i++)
    {   
    cin>>arr[i];
    }
cout<<solve(arr,k,n)<<endl;
return 0;
}
