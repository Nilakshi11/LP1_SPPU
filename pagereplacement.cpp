#include<bits/stdc++.h>
using namespace std;

class PageReplacement
{
    int pf;
    vector<int> input;
    vector<int> table;
    public:
        PageReplacement()
        {
            int n,x;
            cout<<"Enter the total no. of elements: ";
            cin>>n;
            cout<<"Enter the "<<n<<" Values: ";
            for(int i=0;i<n;i++)
            {
                cin>>x;
                input.push_back(x);
            }
            cout<<"Enter the total frames: ";
            cin>>pf;
        }
        int ishit(int x)
        {
            if(find(table.begin(),table.end(),x)!=table.end())
                return 1;
            return 0;
        }
        void fifo()
        {
            int faults=0;
            for(int i=0;i<input.size();i++)
            {
                if(!ishit(input[i]))
                {
                    if(table.size()==pf)
                    {
                        table.erase(table.begin());
                    }
                    table.push_back(input[i]);
                    faults++;
                    cout<<"Page fault!!!"<<endl;
                }
                else
                {
                    cout<<"Page hit!!!"<<endl;
                }
            }
            cout<<"Total no. of page faults: "<<faults<<endl;
        }
        void LRU()
        {
            int faults=0,ind;
            map<int,int> m;

            for(int i=0;i<input.size();i++)
            {
                m[input[i]]=-1;
            }

            for(int i=0;i<input.size();i++)
            {
                if(!ishit(input[i]))
                {
                    if(table.size()==pf)
                    {
                        for(int k=0;k<i;k++)
                        {
                            m[input[k]]=k;
                        }
                        int min=INT_MAX;
                        for(int k=0;k<table.size();k++)
                        {
                            if(m[table[k]]<min)
                            {
                                min=m[table[k]];
                                ind=table[k];
                            }
                        }
                        table.erase(find(table.begin(),table.end(),ind));
                    }
                    table.push_back(input[i]);
                    faults++;
                    cout<<"Page fault!!!"<<endl;
                }
                else
                {
                    cout<<"Page hit!!!"<<endl;
                }
            }
            cout<<"Total page faults: "<<faults<<endl;
        }
        void optimal()
        {
            int faults=0,ind;
            map<int,int> m;
            for(int i=0;i<input.size();i++)
            {
                m[input[i]]=INT_MAX;
            }

            for(int i=0;i<input.size();i++)
            {
                if(!ishit(input[i]))
                {
                    if(table.size()==pf)
                    {
                        for(int k=i+1;k<input.size();k++)
                        {
                            m[input[k]]=k;
                        }
                        int max=INT_MIN;
                        for(int k=0;k<table.size();k++)
                        {
                            if(m[table[k]]>max)
                            {
                                max=m[table[k]];
                                ind=table[k];
                            }
                        }
                        table.erase(find(table.begin(),table.end(),ind));
                    }
                    table.push_back(input[i]);
                    faults++;
                    cout<<"Page fault!!!"<<endl;
                }
                else
                {
                    cout<<"Page hit!!!"<<endl;
                }
            }
            cout<<"Total page fautls: "<<faults<<endl;
        }
};

int main()
{
    PageReplacement pr;
    pr.optimal();
    return 0;
}