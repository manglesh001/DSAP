#include<iostream>
#include <algorithm> 
using namespace std;
template<typename T>
struct arrnode{
int row;
int col;
T val;
};
template<typename T>
struct Node {
int row;
int col;
T val;
Node<T>* next;
Node(int r, int c, T v) : row(r), col(c), val(v), next(nullptr) {}
};

template <typename T>
Node<T>* createNewNode(int row, int col, T val) {
    return new Node<T>(row, col, val);
}
template <typename T>
void addSparseMatrices() {
Node<T>* mat1 = nullptr;
Node<T>* mat2 = nullptr;
Node<T>* temp;
int row1, col1, row2, col2;
//cout << "Enter the dimensions of the first matrix (rows and columns): ";
cin >> row1 >> col1;
//cout << "Enter the elements of the first matrix:" << endl;
int flag=0;
for(int i = 0; i < row1; i++) {
for (int j = 0; j < col1; j++) {
int val;
cin >> val;
if (val != 0) {
Node<T>* newNode = createNewNode(i, j, val);
if(flag==0)
{mat1 = temp = newNode;
flag=1;}
else{
temp->next=newNode;
temp=newNode;
}}}}
temp=nullptr;
//cout << "Enter the dimensions of the second matrix (rows and columns): ";
cin >> row2 >> col2;
//cout << "Enter the elements of the second matrix:" << endl;
flag=0;
for (int i = 0; i < row2; i++) {
for (int j = 0; j < col2; j++) {
int val;
cin >> val;
if (val != 0) {
Node<T>* newNode = createNewNode(i, j, val);
if(flag==0)
{mat2=temp = newNode;
flag=1;}
else{
temp->next=newNode;
temp=newNode;
}
}}}
Node<T>* result = nullptr;
Node<T>* p1 = mat1;
Node<T>* p2 = mat2;
Node<T>* p3 = nullptr;
for (int i = 0; i < row1; i++) {
for (int j = 0; j < col1; j++) {
if ((p1!=NULL && p2!=NULL && p1->row == i && p1->col == j) && (p2->row == i && p2->col == j)) {
Node<T>* newNode = createNewNode(i, j, p1->val + p2->val);
if (result == nullptr) {
result = p3 = newNode;
cout<<p3->val<<" ";
} else {
p3->next = newNode;
p3 = newNode;
cout<<p3->val<<" ";
}
 p1 = p1->next;
 p2 = p2->next;
}
else if (p1!=NULL && p1->row == i && p1->col == j) {
Node<T>* newNode = createNewNode(i, j, p1->val);
if (result == nullptr) {
result = p3 = newNode;
cout<<p3->val<<" ";
} 
else {
p3->next = newNode;
p3 = newNode;
cout<<p3->val<<" ";
}
p1 = p1->next;
} else if (p2!=NULL && p2->row == i && p2->col == j) {
Node<T>* newNode = createNewNode(i, j, p2->val);
if (result == nullptr) {
result = p3 = newNode;
cout<<p3->val<<" ";
} else {
p3->next = newNode;
p3 = newNode;
cout<<p3->val<<" ";
}
p2 = p2->next;
} else {
Node<T>* newNode = createNewNode(i, j, 0);
if (result == nullptr) {
 result = p3 = newNode;
 cout<<p3->val<<" ";
} else {
p3->next = newNode;
 p3 = newNode;
cout<<p3->val<<" ";
}
}
}
cout<<endl;
}
}
template <typename T>
void multiplcation()
{
    Node<T>* mat1 = nullptr;
    Node<T>* mat2 = nullptr;
    Node<T> * mat3=nullptr;
    Node<T> * mat4=nullptr;
Node <T>* temp;
    int row1, col1, row2, col2;

    cout << "Enter the dimensions of the first matrix (rows and columns): ";
    cin >> row1 >> col1;
    cout << "Enter the elements of the first matrix:" << endl;
int flag=0;
int s1=0;int s2=0;
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            int val;
            cin >> val;
            if (val != 0) {
                Node<T>* newNode = createNewNode(i, j, val);
                if(flag==0)
                {mat1 = temp = newNode;
                s1++;
                flag=1;}
                else{
                temp->next=newNode;
                temp=newNode;
                s1++;
                }
            }
        }
    }
temp=nullptr;
    cout << "Enter the dimensions of the second matrix (rows and columns): ";
    cin >> row2 >> col2;
    cout << "Enter the elements of the second matrix:" << endl;
flag=0;
    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            int val;
            cin >> val;
            if (val != 0) {
                Node<T>* newNode = createNewNode(i, j, val);
                if(flag==0)
                {mat2=temp = newNode;
                s2++;
                flag=1;}
                else{
                temp->next=newNode;
                temp=newNode;
                s2++;
                }
            }
        }
    }

    Node<T>* result = nullptr;
    Node<T>* p1 = mat1;
    Node<T>* p2 = mat2;
    Node<T>* p3 = nullptr;
    

    for (int i = 0; i < s1; i++) {
        for (int j = 0; j < s2; j++) {
            if (p1!=NULL && p2!=NULL && p1->col == p2->row ) {
                Node<T>* newNode = createNewNode(p1->row,p2->col,p1->val * p2->val);
                if(p3==nullptr)
                mat3=p3=newNode;
                else
               { p3->next=newNode;
               p3=newNode;
           }
        }}
    }
//cout<<"jhdjd";
mat3 = mergeSort(mat3);
//cout<<"jd";

Node<T> *p4=nullptr;
p3=mat3;
Node<T>* newNode = createNewNode(p3->row,p3->col,p3->val);
if(p4==NULL)
{
    mat4 = p4=newNode;
}
// p4->row=newNode->row;
// p4->col=newNode->col;
// p4->val=newNode->val;
// p4->next=nullptr;
p3=p3->next;
//cout<<"bbhsh";
while(p3!=NULL)
{
    if(p4!=NULL && p4->row==p3->row && p4->col==p3->col)
    {    
         p4->val= p3->val+p4->val;
        p3=p3->next;
    }
    else if (p3!=NULL){
        Node<T>* newNode = createNewNode(p3->row,p3->col,p3->val);
    
        p4->next=newNode;

        p4=newNode;
        p4=p3;
        p3=p3->next;
    }
}

 p4=mat4;


  for(int i = 0; i < row1; i++) {
     for (int j = 0; j < col2; j++) {
          if (p4!=NULL && p4->row == i && p4->col == j) {
        cout << p4->val << " ";
            p4= p4->next;
                 } else {
               cout << 0 << " ";
           }
        }
        cout << endl;
   }
}


template <typename T>
Node<T>* merge(Node<T>* left, Node<T>* right) {
Node<T> dummy(0, 0, 0);
Node<T>* current = &dummy;
while (left && right) {
if (left->row < right->row || (left->row == right->row && left->col < right->col)) {
current->next = left;
left = left->next;
} else {
current->next = right;
right = right->next;
}
current = current->next;
}
current->next = left ? left : right;
return dummy.next;
}
template<typename T>
void multiply()
{
arrnode <T>mat1[100],mat2[100],mat3[100],mat4[100];
int row1,row2;
int col1,col2;
cout<<"row1 & col1 "<<endl;
cin>>row1>>col1;
T val1,val2;
int n=0;
for(int i=0;i<row1;i++)
{
for(int j=0;j<col1;j++)
{
cin>>val1;
if(val1!=0)
{
mat1[n].row=i;
mat1[n].col=j;
mat1[n].val=val1;
n++;
}
}}
int m=0;
cout<<"row2 & col2  ";
cin>>row2>>col2;
for(int i=0;i<row2;i++)
{
for(int j=0;j<col2;j++)
{
cin>>val2;
if(val2!=0)
{
mat2[m].row=i;
mat2[m].col=j;
mat2[m].val=val2;
m++;
}
}}
int k=0;
for(int i=0;i<n;i++)
{
for(int j=0;j<m;j++)
{
if(mat1[i].col==mat2[j].row)
{
mat3[k].row=mat1[i].row;
mat3[k].col=mat2[j].col;
mat3[k].val=mat1[i].val*mat2[j].val;
k++;
}
    }
}
sort(mat3,mat3+k,compare<T>);
int p=0;
 int i=1;
 mat4[p]=mat3[0];
while(i<k )
 {  
if(mat4[p].row==mat3[i].row && mat4[p].col==mat3[i].col)
    {
mat4[p].val+=mat3[i].val;
i++;
}
else{
p++;
mat4[p]=mat3[i];
i++;    }
 }
 p=0;
  for(int i=0;i<row1;i++)
{for(int j=0;j<col2;j++)
            {
if((mat4[p].row==i && mat4[p].col==j) )
 {
                
cout<<mat4[p].val<<" ";
p++;
}
else{
cout<<0<<" ";
 }
}
 cout<<endl;
        }

}
template <typename T>
Node<T>* mergeSort(Node<T>* head) {
    if (!head || !head->next) {
        return head; 
    }
Node<T>* slow = head;
Node<T>* fast = head->next;
while(fast && fast->next) {
slow = slow->next;
fast = fast->next->next;
    }
Node<T>* left = head;
Node<T>* right = slow->next;
slow->next = nullptr; 
left = mergeSort(left);
right = mergeSort(right);
return merge(left, right);
}
template <typename T>
void transposelist() {
Node<T>* mat1 = nullptr;
Node<T>* temp=nullptr;
int row1, col1;
//cout << "Enter the dimensions of the first matrix (rows and columns): ";
cin >> row1 >> col1;
//cout << "Enter the elements of the first matrix:" << endl;
int flag=0;
for (int i = 0; i < row1; i++) {
for (int j = 0; j < col1; j++) {
int val;
cin >> val;
if (val != 0) {
Node<T>* newNode = createNewNode(j, i, val);
if(flag==0 || temp==nullptr)
{mat1 = temp = newNode;
flag=1;}
else{
temp->next=newNode;
temp=newNode;
}
}
}
}
mat1 = mergeSort(mat1);
Node<T> * p=mat1;
for (int i = 0; i < col1; i++) {
for (int j = 0; j < row1; j++) {
if (p!=NULL && p->row == i && p->col == j) {
cout << p->val << " ";
p = p->next;
} else {
cout << 0 << " ";
}
}
cout << endl;
}
}

template<typename T>
void add()
   {    arrnode<T> mat1[100],mat2[100],mat3[100];
    int row1,row2;
    int col1,col2;
   // cout<<"row1 & col1 "<<endl;
    cin>>row1>>col1;
    T val1,val2;

    int n=0;
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<col1;j++)
        {
            cin>>val1;
            if(val1!=0)
            {
                mat1[n].row=i;
                mat1[n].col=j;
                mat1[n].val=val1;
                     n++;
            }
        }
    }
    int m=0;
  //  cout<<"row2 & col2  ";
    cin>>row2>>col2;
     for(int i=0;i<row2;i++)
    {
        for(int j=0;j<col2;j++)
        {
            cin>>val2;
            if(val2!=0)
            {
                mat2[m].row=i;
                mat2[m].col=j;
                mat2[m].val=val2;
                  m++;
            }
        }

    
    }
    int first=0,second=0,third=0;
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<col1;j++)
        {
            if((mat1[first].row==i && mat1[first].col==j)  && (mat2[second].row==i && mat2[second].col==j))
            {
                mat3[third].row=mat1[first].row;

            mat3[third].col=mat1[first].col;
                mat3[third].val=mat1[first].val + mat2[second].val;
            first++;
            second++;
            third++;
            }
            else if(mat1[first].row==i && mat1[first].col==j)
            {
                mat3[third].row=mat1[first].row;
            mat3[third].col=mat1[first].col;
            mat3[third].val=mat1[first].val;
            first++;
            third++;
            }
            else if((mat2[second].row==i && mat2[second].col==j))
            {
                mat3[third].row=mat2[second].row;
            mat3[third].col=mat2[second].col;
            mat3[third].val=mat2[second].val;
            second++;
            third++;
            }
        }
        }
int p=0;
        for(int i=0;i<row1;i++)
        {
            for(int j=0;j<col1;j++)
            {
               if((mat3[p].row==i && mat3[p].col==j) )
               {
                
                    cout<<mat3[p].val<<" ";
                    p++;
                }
                else{
                    cout<<0<<" ";
                }
            }
            cout<<endl;
        }
    }
    template<typename T>
    bool compare(arrnode<T> a, arrnode<T> b) {
    if (a.row == b.row) {
        return a.col < b.col;
    }
    return a.row < b.row;
}
template<typename T>
    void transpose()
    {
         arrnode<T> mat1[100];
         arrnode<T> mat3[100];
    int row1;
    int col1;
    cout<<"row1 & col1 "<<endl;
    cin>>row1>>col1;
    T val1;

    int n=0;
    for(int i=0;i<row1;i++)
    {
        for(int j=0;j<col1;j++)
        {
            cin>>val1;
            if(val1!=0)
            {
                mat1[n].row=j;
                mat1[n].col=i;
                mat1[n].val=val1;
                     n++;
            }
        }
    }
   
    cout<<endl;
   sort(mat1,mat1+n,compare<T>);
int p=0;
 for(int i=0;i<col1;i++)
        {
            for(int j=0;j<row1;j++)
            {
               if((mat1[p].row==i && mat1[p].col==j) )
               {
                
                    cout<<mat1[p].val<<" ";
                    p++;
                }
                else{
                    cout<<0<<" ";
                }
            }
            cout<<endl;
        }
    }

int main()
{   
    int ds;
   // cout<<"1 Array & 2 LL";
    cin>>ds;
    int x;
    if(ds==1)
    {
        
     //   cout<<"ADD 1 or TRANS 2 or MUL 3 ";
        cin>>x;
        switch(x)
        {
        case 1:   { add<int>(); break;}
case 2:{
    transpose<int>(); break;}
    case 3:
    {
        multiply<int>();
        break;

    }
    }

    
    }
    else if(ds==2)
{
      
       // cout<<"ADD 1 or TRANS 2 or MUL 3 ";
        cin>>x;
        switch(x)
        {
        case 1:   { addSparseMatrices<int>(); break;}
case 2:{
    transposelist<int>(); break;
   }
    case 3:
    {
      multiply<int>();
        break;

    }
    }
}


return 0;
}
