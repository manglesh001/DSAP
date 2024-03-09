#include <iostream>
using namespace std;
template <class T>
class MyDeque
{
private:
    int cp;
    int s;
    T *arr;
    int f;
    int r;
public:
    MyDeque()
    {
        cp=1; 
        f=0; 
        s=0;
        r=-1;
        arr=new T[cp];
         
    }
    bool isfull() {
        return (size()==capacity());
    }
    MyDeque(int n,T x) {
        cp=n;
        arr=new T[cp];
        for(int i=0;i<cp;i++)
            arr[i]=x;
        s=cp;
        f=0;
        r=s-1;
    }

    bool empty() {
        return (size()==0);
    }
    MyDeque(int n) {
        cp=n;
        arr=new T[cp];
        f=-1;
        r=-1;
        s=0;   
    }

     bool pop_front() {
        if (f==-1 || s==0)
            return false;

        if (f==r) {
            arr[f]=T();
            f=-1;
            r=-1;
        } else if(f==cp - 1)
        {
            arr[f]=T();
            f=0;
        } else 
        {
            arr[f]=T();
            f=(f+1)%cp;
        }
        s--;
        return true;
    }
    
     bool push_back(T x) {
        if (f==-1 ||(f==(r+1)%cp) || s==cp) {
            if(f==0 && s==0){}
            else
            reserve(cp * 2);
          
        }
        if (f==-1)
        { 
            f=r=0;
        }
       
        else
            {
                r=(r + 1)%cp;
    
        }
        arr[r]=x;
        s++;
        return true;
    }
    bool pop_back() 
    {
    if (f==-1 || s==0)
        return false;

    if (f==r) {
        arr[r]=T(); 
        f=r=-1;
    } 
    else if(r == 0) 
    {
        arr[r]=T(); 
        r=cp-1;
    } else {
        arr[r]=T();
        r=(r-1+cp)%cp;
    }
    s--;
    return true;
}

   
    bool push_front(T x) {
    if (s==cp) 
    {
        reserve(cp*2);
    }
    
    if (f ==-1) {
       
        f=r=0;
    } else if(f==0) {
      
        f=cp-1;
    } else {
        
        f=(f-1+cp)%cp;
    }
    arr[f] = x;
    s++;
   
    return true;
}


    T front(){
        if(s>0){
            return arr[f];
        }
        return T();
    }

    T back() {
        if (s>0)
        {
            return arr[r];
        }
        return T();
    }

   
    int size() {
        return s;
    }
void resize(int n) {
    if (n<s) {
        s=n;
    }
    if(s!=0){
        T *newarr = new T[n];
        for (int i=0; i<s;++i) {
            newarr[i]=arr[(f+i)%cp];
        }
        if(arr!=NULL)
            delete[] arr;
        arr=newarr;
        f=0;
        s=n;
        r=s-1;   
    }
    if(n>cp) {
        cp=n;
    } 
}
 T operator[](int n) 
    {
        if (n >= 0 && n<s) {
            return arr[(f+n)%cp];
        }
          else if(n<0 && (-n)<cp)
        return arr[(cp+n+f)%cp];
        else{}
        return T();
    }

 int capacity() {
        return cp;
    }

    void resize(int n,T value) {
        if (n<s) {
            s=n;
        }

       if(s!=0){
            T *newarr=new T[n];
        for (int i=0; i<s;i++) {
            newarr[i]= arr[(f+i)%cp];
        }

        delete[] arr;
        arr=newarr;
        f=0;
        r=s-1;
       }
          if(cp<n)
        cp=n;

        for (int i=s;i<cp;i++) {
            arr[i]=value;
        }
        s=n;
        r=s-1;
       
    }

  

void clear() {
        f=-1;
        r=-1;
        s=0;
        if(arr!=NULL)
        delete[] arr;
        arr=NULL;
        cp=0;
    }
    void shrink_to_fit()
    {
        if (s<cp) {
            T *newarr=new T[s];
            for (int i=0; i<s;i++) {
                newarr[i] = arr[(f+i)%cp];
            }
            delete[] arr;
            arr=newarr;
            f=0;
            r=s-1;
            cp=s;
        }
    }
  void reserve(int n) {
        if (n==0) n=1;
        if (n>cp) 
        {
            T *newarr=new T[n];
            for(int i=0;i<s;i++) 
            {
                newarr[i]=arr[(f+i)%cp];
            }
            if (arr!=NULL) 
            {
                delete[] arr;
            }
            arr=newarr;
            f=0;
            r=s-1;
            cp=n;
        }
    }
    ~MyDeque() {
        delete[] arr;
    }
};

int main() 
{
MyDeque<int> dq;
  
 int s;

    int choice = -1;
    while (choice != 0) {
        cin >> choice;
        if (choice == 1) {
            dq = MyDeque<int>();
        }
        else if (choice == 2) {
            int n;
            cin >> n;
            dq = MyDeque<int>(n);
        }
        else if (choice == 3) {
            int n,x;
            cin >> n;
            cin >> x;
            dq = MyDeque<int>(n, x);
        }
        else if (choice == 4) {
            cin >> s;
            cout << boolalpha << dq.push_back(s) << endl;
        }
        else if (choice == 5) {
            cout << boolalpha << dq.pop_back() << endl;
        }
        else if (choice == 6) {
            cin >> s;
            cout << boolalpha << dq.push_front(s) << endl;
        }
        else if (choice == 7) {
            cout << boolalpha << dq.pop_front() << endl;
        }
        else if (choice == 8) {
            s = dq.front();
            cout << s << endl;
        }
        else if (choice == 9) {
            s = dq.back();
            cout << s << endl;
        }
        else if(choice==10)
        {
            int n;
            cin>>n;
        cout << dq[n] << endl;
        }
        else if (choice == 11) {
            cout << boolalpha << dq.empty() << endl;
        }
        else if (choice == 12) {
            cout << dq.size() << endl;
        }
        else if (choice == 13) {
            int n;
            cin>>n;
            dq.resize(n);
        }
        else if (choice == 14) {
            int n,x;
            cin>>n>>x;
            dq.resize(n,x);
        }
        else if (choice == 15) {
            int n;
            cin>>n;
            dq.reserve(n);
        }
        else if (choice == 16) {
            dq.shrink_to_fit();
        }
        else if (choice == 17) {
            dq.clear();
        }
        else if (choice == 18) {
            cout << dq.capacity() << endl;
        }
        else{}
        }
return 0;
}

/*
    while (1) {
       
        cin >> choice;

        switch(choice) {
            case 0:
                exit(0);

            case 1: {
                d = MyDeque<int>();
                break;
            }
            case 2: {
                int n;
                cout << "Enter Length" << endl;
                cin >> n;
                d = MyDeque<int>(n);
                break;
            }
            case 3: {
                int n, x;
                cout << "Enter Length" << endl;
                cin >> n;
                cout << "Enter Default Value" << endl;
                cin >> x;
                d =MyDeque<int>(n, x);
                break;
            }
            case 4: {
                int x;
                cout << "Enter Item" << endl;
                cin >> x;
                if (d.push_back(x))
                    cout << "True";
                else
                    cout << "False";
                break;
            }
            case 5: {
                if (d.pop_back())
                    cout << "True";
                else
                    cout << "False";
                break;
            }
            case 6: {
                int x;
                cout << "Enter Item" << endl;
                cin >> x;
                if (d.push_front(x))
                    cout << "True" << endl;
                else
                    cout << "false" << endl;
                break;
            }
            case 7: {
                if (d.pop_front())
                    cout << "True";
                else
                    cout << "False";
                break;
            }
            case 8: {
                cout << d.front() << endl;
                break;
            }
            case 9: {
                cout << d.back() << endl;
                break;
            }
            case 10: {
                int n;
                cout << "Enter Index " << endl;
                cin >> n;
                cout << d[n] << endl;
                break;
            }
            case 11: {
                if (d.empty())
                    cout << "True";
                else
                    cout << "False";
                break;
            }
            case 12: {
                cout << d.size() << endl;
                break;
            }
            case 13: {
                cout << "Enter the New s" << endl;
                
                int n;
                cin >> n;
                d.resize(n);
                break;
            }
            case 14: {
                cout << "Enter the New s" << endl;
                int n;
                cin >> n;
                cout << "Enter Default Value" << endl;
                int df;
                cin >> df;

                d.resize(n, df);
                break;
            }
            case 15: {
                cout << "Enter the maxs" << endl;
                int n;
                cin >> n;
                d.reserve(n);
                break;
            }
            case 16: {
                d.shrink_to_fit();
                break;
            }
            case 17: {
                d.clear();
                break;
            }
            case 18: {
                cout << d.capacity() << endl;
                break;
            }
            default: {
                cout << "Wrong Input! Give Another Input!!" << endl;
                break;
            }
        }
    }

    return 0;
}
*/


