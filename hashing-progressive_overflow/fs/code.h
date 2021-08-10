#ifndef CODE_H
#define CODE_H
#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
char sadd[50];
char indexadd[100][50];
char u[10],n[30],brn[20],sem[10];
int cnt;

class Student{
    public:

      long usn;
      string name;
      void unpack(int);
      Student(){

      }
};
//int nor;
class Hashtable{
    public:
    Student **arr;
    int size;
    int hashindex;

    //char sadd[50];

        Hashtable(int s){
        //cnt=0;
        size=s;
        arr=new Student*[size];
        for(int i=0;i<size;i++)
        {
            arr[i]=nullptr;
        }
    }
    int hashfunc(int n)
    {
       return n%size;
    }
    void recovery(){
        fstream f1("C:/Users/HP/Documents/fs/hash.txt",ios::in);
        if(!f1)
        {
            //cout<<"file couldn't open";
            f1.close();
            return;
        }
    char index[3],u[20];
    while(f1.getline(index,3,'|'))
    {
        f1.getline(u,20,'|');
        int i=atoi(index);
        arr[i] = new Student();
        arr[i]->usn=atoi(u);
        f1.getline(indexadd[i],50);
        cnt++;
    }

    f1.close();
    return;
    }
    int insert(long key,string value,string brn,string sem)
    {
        //long key;string value;
        //cout<<"Record:"<<cnt+1<<endl;
        if(key<=0)
            return -3;
        if(cnt==size)
        {
           cout<<"Storage is full!!"<<endl;
           return -1;
        }
        //cout<<"Enter usn,name,branch and sem\n";
        //cin>>key>>value>>brn>>sem;
        for(int i=0;i<size;i++)
        {
            if(arr[i]!=nullptr&&arr[i]->usn==key)
            {
                cout<<"\nDuplicate entry\n";
                return -2;
            }
        }

        fstream f1("C:/Users/HP/Documents/fs/hash.txt",ios::app);
        fstream f2("C:/Users/HP/Documents/fs/hrec.txt",ios::app);

        int hashindex = hashfunc(key);
        while(arr[hashindex] != nullptr){
            hashindex= (hashindex + 1)%size;
        }
        arr[hashindex] = new Student();
        arr[hashindex]->usn = key;
        arr[hashindex]->name = value;

        f2.seekp(0,ios::end);
        itoa(f2.tellp(),sadd,10);
        strcpy(indexadd[hashindex],sadd);
        //cout<<indexadd[hashindex]<<"--->"<<sadd<<endl;
        f1<<hashindex<<'|'<<key<<'|'<<f2.tellp()<<'\n';
        f2<<key<<'|'<<value<<'|'<<brn<<'|'<<sem<<'|';
        cnt++;
        cout<<"Inserted "<<value<<" at "<<hashindex<<endl;
        return 1;
        f1.close();
        f2.close();
    }

    int length(long key)
    {
        int c=0;
        while(key!=0)
        {
           key=key/10;
           ++c;
        }
        return c;
    }

    int search(long key)
    {
        if(key<=0)
            return -3;
        if(cnt==0){
            cout<< "Empty";
            return 0;
        }
        hashindex= hashfunc(key);
        int temp= -1;
        //cout<<hashindex<<"----"<<arr[hashindex]->usn<<endl;
        while(hashindex!=temp && (arr[hashindex]== nullptr||arr[hashindex]->usn!=key))
        {
            if(temp==-1)
                temp=hashindex;
            hashindex= hashfunc(hashindex + 1);
            //cout<<hashindex<<"....."<<temp<<endl;
        }

        if (hashindex == temp)//removed null condition ***
        {
                cout<< "Not found\n";
                return 0;
        }
        else
            return 1;
            /*
            else
            {
                int add=atoi(indexadd[hashindex]);
                unpack(add);

                cout<<"Student record found "<<endl;
                cout<<"usn:"<<u<<"\tname:"<<n<<"\tbranch:"<<brn<<"\tsem:"<<sem<<endl;
                //cout<<arr[hashindex]->name<<;
                return 1;
            }*/
    }
   void unpack(int add)
    {
    fstream f1("C:/Users/HP/Documents/fs/hrec.txt",ios::in);
    f1.seekg(add);
    f1.getline(u,10,'|');
    f1.getline(n,30,'|');
    f1.getline(brn,20,'|');
    f1.getline(sem,10,'|');
    f1.close();
    }

    int deletestud(long key)
    {
        if(key<=0)
            return -3;
        int len_field;
        if(cnt==0){
          cout<< "Empty";
          return -1;
        }
        //char susn = key;
        int hashindex= hashfunc(key);
        int temp= -1;
        //cout<<hashindex<<"----"<<arr[hashindex]->usn<<endl;
        while(hashindex!=temp && (arr[hashindex]== nullptr||arr[hashindex]->usn!=key))
        {
            if(temp==-1)
            temp=hashindex;
            hashindex= hashfunc(hashindex + 1);
            //cout<<hashindex<<"....."<<temp<<endl;
        }

        if (hashindex == temp||arr[hashindex]==NULL )
        {
                cout<< "Not found\n";
                return -2;
        }
            else
            {
                fstream f1("C:/Users/HP/Documents/fs/hash.txt",ios::out|ios::trunc);
                int add=atoi(indexadd[hashindex]);
                //cout<<add<<endl;
                fstream f2("C:/Users/HP/Documents/fs/hrec.txt", ios::in | ios::out);
                len_field = length(key);
                f2.seekp(add, ios::beg);
                for(int j = 0; j < len_field; j++)
                {
                    f2<<'*';
                }
                f2.close();
                delete arr[hashindex];
                arr[hashindex]= nullptr;
                for(int i=0;i<size;i++)
                {
                if(arr[i]!=nullptr)
                f1<<i<<'|'<<arr[i]->usn<<'|'<<indexadd[i]<<'\n';
                }
                f1.close();
                cout<<"\nStudent with usn "<<key<<" is deleted\n ";
                cnt--;
                return 1;
            }
    }
    int display()
    {
        if(cnt==0)
        {
           cout<<"No records to display\n";
           return -1;
        }

        /*for(int i=0;i<size;i++)
        {
            if(arr[i]!=nullptr)
            {
                int add=atoi(indexadd[i]);
                unpack(add);
                cout<<"ht["<<i<<"]:\tusn ="<< u<< "\tname="<<n<<"\tbranch:"<<brn<<"\tsem:"<<sem<<endl;
            }
        }*/
    }
    /*void modify()
    {
        int u;
        if(cnt==0){
            cout<< "Empty";
            return;
        }
        cout<<"Enter usn of record to be modified\n";
        cin>>u;
        int found=search(u);
        if(found==1)
        {
            deletestud(u);
            insert();
        }
    }*/
};
/*int main()
{
    Hashtable ht(50);
    int c;
    long u;
    string n;
    ht.recovery();
    while(1)
    {
    cout<<"1.Insert  2.Search  3.Delete  4.Display  5.Modify 6.Exit\n";
    cout<<"Enter your choice: ";
    cin>>c;
    switch(c)
    {
        case 1:
                ht.insert();
                break;
        case 2:cout<<"Enter usn to search:";
                cin>>u;
                ht.search(u);
                break;
        case 3:cout<<"Enter usn\n";
                cin>>u;
                ht.deletestud(u);
                break;
        case 4:ht.display();
                break;
        case 5:ht.modify();
                break;
        case 6://remove("C:/Users/HP/Documents/fs/hash.txt");
                //remove("C:/Users/HP/Documents/fs/hrec.txt");
                exit(0);
        default: cout<<"Invalid choice\n";
    }
    }
    return 0;
}*/
#endif // CODE_H
