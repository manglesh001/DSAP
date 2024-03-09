#include <iostream>
using namespace std;
class MinPriorityQueue {
private:
int* minh;
int cap;
int s;
public:
bool empty()
{return s == 0;
}
int size()
{return s;
}
void swap(int& a,int& b) 
{
int temp=a;
a=b;
b=temp;
}
MinPriorityQueue() 
{cap=0;
s=0;
minh = nullptr;
}
void increasecap(){
int newcap=0;
if(cap==0)
newcap = 1;
else
newcap=cap*2;
int* newminh = new int[newcap];
for (int i = 0; i < cap; ++i) {
newminh[i] = minh[i];
}
delete[] minh;
minh = newminh;
cap = newcap;
}
void minheapify(int ind) {
int left = 2 * ind + 1;
int right = 2 * ind + 2;
int smallest = ind;
if (left < s && minh[left] < minh[smallest]) {
smallest = left;
}
if (right < s && minh[right] < minh[smallest]) {
smallest = right;
}
if (smallest != ind) {
swap(minh[ind], minh[smallest]);
minheapify(smallest);
}
}
void push(int element) {
if (s == cap) {
increasecap();
}
int ind = s;
minh[s++] = element;
while (ind > 0 && minh[ind] < minh[(ind - 1) / 2]) {
swap(minh[ind], minh[(ind - 1) / 2]);
ind = (ind - 1) / 2;
}
}
int top()
{
if (s == 0) {
cout << "Priority queue is empty" << endl;
return -1;
}
return minh[0];
}
void pop() {
if (s == 0) {
cout << "Priority queue is empty" << endl;
}
swap(minh[0], minh[s - 1]);
s--;
minheapify(0);
}
};
class MaxPriorityQueue {
private:
int* maxh;
int cap;
int s;
public:
bool empty() {
return s == 0;
 }
int size() {
 return s;
}
void swap(int& a, int& b) {
int temp = a;
a = b;
b = temp;
}
MaxPriorityQueue() {
cap = 0;
s = 0;
maxh = nullptr;
}
void increasecapacity() {
int newcap = 0;
if (cap == 0)
newcap = 1;
else
newcap = cap * 2;
int* newmaxh = new int[newcap];
for (int i = 0; i < cap; ++i) {
newmaxh[i] = maxh[i];
}
delete[] maxh;
maxh = newmaxh;
cap = newcap;
}
void maxheapify(int ind) {
int left = 2 * ind + 1;
int right = 2 * ind + 2;
int largest = ind;
if(left < s && maxh[left] > maxh[largest]) {
largest = left;
}
if (right < s && maxh[right] > maxh[largest]) {
largest = right;
}
if (largest != ind) {
swap(maxh[ind], maxh[largest]);
maxheapify(largest);
 }
}
void push(int element) {
if (s == cap) {
 increasecapacity();
 }
int ind = s;
maxh[s++] = element;
while (ind > 0 && maxh[ind] > maxh[(ind - 1) / 2]) {
swap(maxh[ind], maxh[(ind - 1) / 2]);
ind = (ind - 1) / 2;
 }
}
int top() {
if(s == 0) {
cout << "Priority queue is empty" << endl;
return -1;
}
return maxh[0];
}
void pop() {
if (s == 0) {
cout <<"Priority queue is empty" << endl;
}
swap(maxh[0], maxh[s - 1]);
s--;
maxheapify(0);
}   
};
double* medianWindow(int* nums, int numsSize, int k, int* returnSize) {
*returnSize = numsSize - k + 1;
double* ans = (double*)malloc((*returnSize) * sizeof(double));
MaxPriorityQueue maxh;
MinPriorityQueue minh;
maxh=MaxPriorityQueue();
minh=MinPriorityQueue();  
auto add = [&](int x) {
maxh.push(x);
minh.push(maxh.top());
maxh.pop();
if(maxh.size() < minh.size()) {
maxh.push(minh.top());
minh.pop();
}
};
int ansind = 0;
for(int i = 0; i < numsSize; i++) {
add(nums[i]);
if (i >= k - 1) {
if (k % 2 == 0) {
ans[ansind++] = (static_cast<double>(maxh.top()) + minh.top()) / 2.0;
}
else {
ans[ansind++] = static_cast<double>(maxh.top());
}
int removedNum = nums[i - k + 1];
if(removedNum <= maxh.top()) {
maxh.pop();
}
else
{ 
minh.pop();
}}}    
return ans;
}
 void median(int num[],int n,int d,double med1[])
{
MaxPriorityQueue maxh;
MinPriorityQueue minh;
maxh=MaxPriorityQueue();
minh=MinPriorityQueue();
for(int i=0;i<n;i++)
{
if(maxh.empty() || maxh.top()>num[i])
maxh.push(num[i]);
else
minh.push(num[i]);
if(maxh.size()>minh.size()+1)
{
minh.push(maxh.top());
maxh.pop();
}
else if(maxh.size()+1<minh.size())
{
maxh.push(minh.top());
minh.pop();
}
if(maxh.size()==minh.size())
  {
if(maxh.empty()){}
    else{
med1[i]=(maxh.top()+minh.top())/2.0;
    }
  }
else{ if(maxh.size()>minh.size()){
med1[i]=maxh.top();
  }  
  else{
med1[i]=minh.top();
}}
}}
int main()
 {
int n,d;
cin >> n;
cin >> d;
int nums[n];
double med1[n];    
for (int i = 0; i < n; ++i) {
cin >> nums[i];
}
int returnSize;
int count=0;
double sum=0.0;
median(nums,n,d,med1);
double* med2 =medianWindow(nums,n,d,&returnSize);
for(int i=d;i<n;i++)
{
sum=med1[i-1]+med2[i-d];
if(sum<=nums[i])
count++;
}
cout<<count;
return 0;
} 