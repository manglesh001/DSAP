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
int main() {
int h;
cout<<"max 0 & min 1"<<endl;
cin>>h;
if(h==0)
{
MaxPriorityQueue maxh;
 while(true)
{
int choice;
cin>>choice;
switch(choice)
{
case 0:
{
exit(1);
}
case 1: 
{
maxh=MaxPriorityQueue();
break;
}
case 2:
{cout<<maxh.size();
break;
}
case 3:
{
int ele;
cin>>ele;
maxh.push(ele);
break;
}
case 4:
{
cout<<maxh.top()<<endl;
break;
}
case 5:
{
maxh.pop();
break;
}
case 6:
{
    if(maxh.empty())
cout<<"true "<<endl;
else
cout<<"false"<<endl;
break;
}
default:
{
cout<<"wrong Input Case Maxheap "<<endl;
}}}}
else if(h==1){
MinPriorityQueue minh;
while(true)
{
int choice;
cin>>choice;
switch(choice)
{
case 0: {exit(1);}
case 1: 
{
 minh=MinPriorityQueue();
break;
}
case 2:
{cout<< minh.size();
break;
}
case 3:
{
int ele;
cin>>ele;
minh.push(ele);
break;
}
case 4:
{
cout<<minh.top()<<endl;
break;
}
case 5:
{
minh.pop();
break;
}
case 6:
{
cout<<minh.empty()<<endl;
break;
}
 default:
{
cout<<"wrong Input Case minheap "<<endl;
}
}
}}
else
cout<<"Wrong Input"<<endl;
    return 0;
}

