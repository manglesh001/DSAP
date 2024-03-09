#include <iostream>
#include <string>
#include <vector>
using namespace std;
const int DIST=3;
struct Node {
Node* links[26];
bool flag = false;
bool isend() 
{
        return flag;
}
    void putc(char ch) 
    {
        links[ch-'a'] = new Node();
    }
Node* getn(char ch) 
{
        return links[ch-'a'];
}
    bool containskey(char ch) 
    {
        if (links[ch-'a'] != NULL) 
        {
            return true;
        }
        return false;
    }
    void setend() 
    {
        flag = true;
    }
};
class MyTrie 
{
public:
    Node* root = NULL;
    MyTrie() 
    {
        root = new Node();
    }
     int countPrefix(Node* node)
    {
        if(node == nullptr) 
        {
            return 0;
        }

        int count = 0;
        if(node->isend()) 
        {
            count++;
        }

        for(int i = 0; i < 26; i++) 
        {
            count =count+countPrefix(node->getn('a' + i));
        }

        return count;
    }
    bool search(string word)
     {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) 
        {
            if(!node->containskey(word[i])) 
            {
                return false;
            }
            node=node->getn(word[i]);
        }
        return node->isend();
    }
   
    void getPrefix(Node* node, string prefix, vector<string>& words) 
    {
        if(node == nullptr) 
        {
            return;
        }

        if(node->isend()) 
        {
            words.push_back(prefix);
        }

        for(int i = 0; i < 26; i++)
         {
            getPrefix(node->getn('a' + i), prefix + char('a' + i), words);
        }
    }
     void autocorrect(string word) 
     {
        vector<string> words;
        getPrefix(root, "", words);

        vector<string> ans;
        for(string w : words) 
        {
            int dist = editdis(w, word);
            if(dist <= 3) 
            {
                ans.push_back(w);
            }
        }
        cout<< ans.size() << endl;
        for(string w : ans) 
        {
            cout << w << endl;
        }
    }
    int editdis(string s1, string s2) 
    {
        vector<vector<int>> ld(s1.length() + 1, vector<int>(s2.length() + 1, 0));
        for (int i = 0; i <= s1.length(); i++) {
            for(int j = 0; j <= s2.length(); j++) 
            {
                if(i == 0) 
                {

                    ld[i][j] = j;
                } 
                else if(j == 0) 
                {
                    ld[i][j] = i;
                } 
                else if(s1[i - 1] == s2[j - 1]) 
                {
                    ld[i][j] = ld[i - 1][j - 1];
                } 
                else 
                {
                    ld[i][j] = min( ld[i - 1][j], min(ld[i][j - 1], ld[i - 1][j - 1])) + 1;
                }
            }
        }
        return ld[s1.length()][s2.length()];
    }
    bool startsWith(string prefix) 
    {
        Node* node = root;
        for(int i = 0; i < prefix.size(); i++) 
        {
            if(node->containskey(prefix[i])) 
            {
                node = node->getn(prefix[i]);
            } 
            else 
            {
                return false;
            }
        }

        int count=countPrefix(node);
        cout << count << endl;
        vector<string> words;
        getPrefix(node, prefix, words);
        for(string word : words) 
        {
            cout << word << endl;
        }
    return true;
    }
 void insert(string word) 
 {

        Node* node = root;
        for(int i = 0; i < word.size(); i++) 
        {
            if(node->containskey(word[i]) == true) 
            {
                node = node->getn(word[i]);
            }
             else
             {
                node->putc(word[i]);
                node = node->getn(word[i]);
            }
        }
        node->setend();
 }
};

int main() 
{
    int n, q;
    cin >> n >> q;
    MyTrie mt;
    for (int i = 0; i < n; i++) 
    {
        string word;
        cin >> word;
        mt.insert(word);
    }
    for(int i = 0; i < q; i++)
     {
        int c;
        string s;
        cin >> c >>s;
        if(c == 1)
         {
            if(mt.search(s)) {
                cout << "1" << endl;
            } 
            else 
            {
                cout << "0" << endl;
            }
        } 
        else if(c == 2) 
        {
            mt.startsWith(s);
        } 
        else if(c == 3)
         {
            mt.autocorrect(s);
        }
    }

    return 0;
}


