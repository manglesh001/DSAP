#include <iostream>
#include <cstdlib>
#include <ctime>
#include<cstring>
using namespace std;
const int MAX_LEVEL =20; 
template <typename T>
struct Node 
{
T val;
Node<T>** fwd;
Node(T k, int level) : val(k)
{
fwd=new Node<T>*[level+1];
memset(fwd,0,sizeof(Node<T>*)*(level+1));
}
 ~Node()
{
delete[] fwd;
}
};
template <typename T>
class SkipList 
{
int level;
Node<T>* head;
public:
 SkipList()
{
level = 0;
head = new Node<T>(T(),MAX_LEVEL);
}
int count_occurrence(T val)
{
int count = 0;
Node<T>* curr = head->fwd[0];
while (curr != nullptr && curr->val <= val) {
if (curr->val == val) {
                count++; }
curr = curr->fwd[0];}
return count;
}
int randomLevel() 
{
int lvl=0;
while(rand()<RAND_MAX/2 && lvl<MAX_LEVEL)
{
lvl++;
}
return lvl;
}
~SkipList(){
delete head;
}
 T lower_bound(T val)
 {
Node<T>* curr = head;
for(int i = level; i >= 0; i--) 
{
while (curr->fwd[i] != nullptr && curr->fwd[i]->val < val) {
curr = curr->fwd[i];}}
curr = curr->fwd[0];
if(curr != nullptr && curr->val >= val) {
return curr->val;}
return T(); 
} void insert(T val) {
Node<T>* md[MAX_LEVEL + 1];
Node<T>* curr = head;
for (int i = level; i >= 0; i--) 
{while (curr->fwd[i] != nullptr && curr->fwd[i]->val < val) {
curr = curr->fwd[i];
}
md[i] = curr;
}
curr = curr->fwd[0];
if(curr == nullptr || curr->val != val) {
int newLevel = randomLevel();
if(newLevel>level) {
 for(int i = level + 1; i <= newLevel; i++) 
{
md[i] = head;
}
level = newLevel;
}
Node<T>* newNode = new Node<T>(val, newLevel);
for (int i = 0; i <= newLevel; i++) {
newNode->fwd[i] = md[i]->fwd[i];
md[i]->fwd[i] = newNode;
}
}
}
T closest_element(T val) 
{
Node<T>* curr = head;
T closest=T(); 
for (int i = level; i >= 0; i--) {
while (curr->fwd[i] != nullptr && curr->fwd[i]->val <= val) {
curr = curr->fwd[i];
if(curr->val > closest) {
closest = curr->val;
}}}
return closest;
}
bool search(T val) 
{
Node<T>* curr = head;
for(int i = level; i >= 0; i--)
{
while (curr->fwd[i] != nullptr && curr->fwd[i]->val < val) {
curr = curr->fwd[i];
} }
curr = curr->fwd[0];
return (curr != nullptr && curr->val == val);
}
void remove(T val) {
Node<T>* md[MAX_LEVEL + 1];
Node<T>* curr = head;
for (int i = level; i >= 0; i--) 
{
while (curr->fwd[i] != nullptr && curr->fwd[i]->val < val)
{
curr = curr->fwd[i];
}
md[i] = curr;
}
curr = curr->fwd[0];
if(curr != nullptr && curr->val == val) 
{
while(curr != nullptr && curr->val == val) {
for(int i = 0; i <= level; i++) 
{
if(md[i]->fwd[i] != curr) {
break;
}
md[i]->fwd[i] = curr->fwd[i];
}
Node<T>* temp = curr;
curr = curr->fwd[0];
delete temp;
}
while (level > 0 && head->fwd[level] == nullptr) {
level--;
}
}
}
 void display()
 {
cout << "Skip List (level " << level << "):" << endl;
for(int i = level; i >= 0; i--) {
Node<T>* curr = head->fwd[i];
cout << "Level " << i << ": ";
 while (curr != nullptr) {
cout << curr->val << " ";
curr = curr->fwd[i];
}
cout <<endl;
}
}
T upper_bound(T val) {
Node<T>* curr = head;
T upperBound = T(); 
for(int i = level; i >= 0; i--) {
while(curr->fwd[i] != nullptr && curr->fwd[i]->val <= val) {
curr = curr->fwd[i];
}
if(curr->val > upperBound)
{
upperBound = curr->val;
}
}
return upperBound; }  
};
int main() 
{
srand(time(0));
SkipList<int> skipList;
while (true) 
{
cout << "0. Exit  1. Insert  2. Search  3. Delete  4. Count Occurrences  5. Lower Bound  6. Upper Bound 7 Closest Element 8.Display  " << endl;
int choice;
cin >> choice;
switch (choice)
{
case 1: 
{
int val;

cin >> val;
skipList.insert(val);
break;
}
case 2: {
 int val;
cin >> val;
cout <<(skipList.search(val) ? "TRUE":"FALSE")<< endl;
break;
}
case 3: 
{
int val;
cin >> val;
skipList.remove(val);
break;
}
case 4: {
int val;
cin >> val;
int count = skipList.count_occurrence(val);
cout<< count<< endl;
break;
}
case 5: {
int val;
cin >> val;
int lowerBound = skipList.lower_bound(val);
if (lowerBound !=0) 
{
 cout<<lowerBound << endl;
} else 
{
cout<<"No lower bound" << endl;
}
break;
}            
case 6: {
int val;
 cin >> val;
int upperBound = skipList.upper_bound(val);
if (upperBound !=0) {
 cout<<upperBound << endl;
 } else {
 cout<<"No upper bound" << endl;
}
  break;
}
case 7: {
int val;

 cin >> val;
int close= skipList.closest_element(val);
if (close!=0) {
 cout<< close << endl;
 } else {
 cout<<"No Close Element" << endl;
  }
  break;
}
case 8:
skipList.display();
 break;
case 0:
exit(0);
default:
cout << "wrong choice" << endl;
}
}

    return 0;
}

