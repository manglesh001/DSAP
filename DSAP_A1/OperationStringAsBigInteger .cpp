#include<iostream>
#include<string.h>
#include<cstring>
using namespace std;
template <class T>
class stack{
   
    int size;
    int top;
     T *arr;
public:
stack(int s)
{
    size=s;
    arr=new T[size];
    top=-1;
}
bool isempty()
{
    if(top==-1)
    return true;
    else
    return false;
}
bool isfull()
{
    if(top==size-1)
    return true;
    return false;
}
bool push(T item)
{
    if(top<size-1)
    {
        top++;
        arr[top]=item;
        return true;
    }
    else 
    return false;
}
T pop()
{
    
    if(top>=0)
    {
        return arr[top--];        
    }
    else
    return T();
}
T peek()
{
    if(top!=-1)
    return arr[top];
    else
    return  T();
}

};
string Add(string x,string y) {
        int i=x.length()-1;
        string s="";
        int sum=0;
        int j=y.length()-1;
        int carry=0;
        
        while(i>=0 && j>=0)
        {
            int a=x[i]-48; 
            int b=y[j]-48; 
            sum=a+b; 
            sum=sum+carry; 
            s=to_string(sum%10)+s; 
            carry=sum/10; 
            j=j-1; 
            i=i-1;
        }
        while(i>=0){
            int sum=x[i]-48; 
            sum=sum+carry;
            carry=sum/10; 
            s=to_string(sum%10)+s;  
            i=i-1; 
        }
        while(j>=0){
            int sum=y[j]-48; 
            sum=sum+carry;
            s=to_string(sum%10)+s; 
            carry=sum/10; 
            j=j-1; 
        }
        int n=0; 
        if(carry>=1)
            s=to_string(carry)+s;
            int size=s.length()-1;
        for(int i=0;i<=size;i++){
            if(s[i]==48){
                n=n+1;
                if(i==size)
                    return "0"; 
            }
            else
                break;
        }
        s.erase(0,n); 
        return s;
    }
    string multiply(string s1, string s2) {
        if(s1=="0"||s2=="0")
            return "0";
        int l1=s1.length();
        int l2=s2.length();
        string mul(l1+l2,48);
        for(int i=l1-1;i>=0;i--){
            for (int j=l2-1;j>=0;j--)
            {   
                int prod=(s1[i]-48)*(s2[j]-48);
                int carry=(mul[i+j+1]-48)+prod;
                mul[i+j]=(mul[i+j]-48)+(carry/10)+48;
                mul[i+j+1]=(carry%10)+48;
            }
        }  
        if(mul[0]==48)
            mul.erase(0,1);
        return mul;
    }
string Sub(string s1,string s2) {
    int l1=s1.length();
    string s="";
    int l2=s2.length();
    int borrow=0;
    int sub=l1-l2;
    for(int i=l2-1;i>=0;i--) 
    {
        int x=(s1[i+sub]-48);
        int y=(s2[i]-48);
        int diff=x-y-borrow;
        if(diff<0) 
        {
            diff=diff+10;
            borrow=1;
        } 
        else{
            borrow=0;
        }
        s=to_string(diff)+s;
    }
    for(int i=l1-l2-1;i>=0;i--)
     {
        int d=s1[i]-48;
        int diff=d-borrow;
        if(diff<0) 
        {
            diff=diff+10;
            borrow=1;
        }
        else
            borrow=0;
        s=to_string(diff)+s;
        }
        while(s.length()>1 && s[0]=='0')
        {
            s.erase(0,1);
        }
        return s;
}
    string divide(string s1,string s2)
{
     string count="1";
    if(s1.length()<s2.length())
    return "0";
    else if(s1.length()==s2.length() && strcmp(s1.c_str(),s2.c_str())<0)
    return "0";
    else if(s1.length()==s2.length() && strcmp(s1.c_str(),s2.c_str())==0)
    return "1";
    else{
         string temp="";
            while((temp.length()<s1.length()) || ((temp.length()==s1.length()) && (strcmp(temp.c_str(),s1.c_str())<=0)))
        {
        temp=multiply(s2,count);
        count=Add(count,"1");
        }
    }
    count= Sub(count,"1");
    count= Sub(count,"1");
    return count;
}
string mod(string s1,string s2)
{
    string q=divide(s1,s2);
    string temp=multiply(s2,q);
    string rem=Sub(s1,temp);
    return rem;
}
string gcd(string a,string b)
{
    if(b=="0")
    return a;
    else
    return gcd(b,mod(a,b));
}
string expo(string a,string b)
{   if(a=="0")
        return "0";
    if(b=="0")
        return "1";
    if(b=="1")
        return a;
    int l=b.length()-1;
    string s="";
    string s1="";
    if((b[l]-'0')%2==0)
    {
        s=divide(b,"2");
        string x=expo(a,s);
        return multiply(x,x);
    }
    else{
        s1=Sub(b,"1");
        string y=divide(s1,"2");
        string str=expo(a,y);
        string p=multiply(str,str);
        return multiply(a,p);
    }
}
string factorial(string s1)
{
   
     if(s1=="0"||s1=="0")
            return "1";
            string str=s1;
        long long int i=atol(s1.c_str());
        for(;i>1;i--)
        {
            str=multiply(str,to_string(i-1));
        }
        return str;
}
string calculate(string a, string b, char op) {
    switch (op) {
        case '+':
            return Add(a,b);
        case '-':
            return Sub(a,b);
        case 'x':
            return multiply(a,b);
        case '/':
            return divide(a,b);
    }
    return "";
}


bool isOperator(char c) {
    return (c=='+' || c=='-' || c=='x' || c=='/');
}

int priority(char op) {
    if (op=='x' || op=='/') 
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}


string math(string str) {
    int i = 0;
    int length = str.length();
    stack<string> arr(length);
    stack<char> op(length);
    while (i < length) {
       
            if (isdigit(str[i])) {
                string num;
                while (i < length && (isdigit(str[i]))) {
                    num += str[i];
                    i++;
                }
                arr.push(num);
            } else if (isOperator(str[i])) {
                while (!op.isempty() && priority(op.peek())>=priority(str[i])) {
                    string val2=arr.pop();
                    string val1=arr.pop();
                    char ch =op.pop();
                    arr.push(calculate(val1,val2,ch));
                }
                op.push(str[i]);
                i++;
            }
        
    }

    while (!op.isempty()) {
        string val2=arr.pop();
        string val1=arr.pop();
        char ch=op.pop();
        arr.push(calculate(val1,val2,ch));
    }

    return arr.peek();
}

int main()
{
    int input;
   
    cin>>input;
    switch(input)
    {
        case 1: {
                string s;
                cin>>s;
                string str=math(s);
                cout<<str<<endl;
                break;
        }
        case 2:
         {       string s1,s2;
                cin>>s1>>s2;
                string str=expo(s1,s2);
                cout<<str<<endl;
                break;
             } 
        case 3: 
               { 
                   string s1,s2;
                cin>>s1>>s2;
                string str=gcd(s1,s2);
                cout<<str<<endl;
                break;
               }
        case 4: 
                {
                string s;
                cin>>s;
                string str=factorial(s);
                cout<<str<<endl;
                break;
                }
        default:{}
                   }
    return 0;
}
