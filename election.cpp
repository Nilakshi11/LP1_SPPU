#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

class Candidate
{
    int id;
    bool active;
    public:
        Candidate()
        {
            id=0;
            active=true;
        }
        void addCandidate()
        {
            cout<<"Enter the Candidate ID: ";
            cin>>id;
        }
        friend class Election;
};
class Election
{
    vector<Candidate> v;
    int currindex;          //refers to the current coordinator
    public:
        Election()
        {
            currindex=-1;
        }
        void getCandidate()
        {
            Candidate c;
            c.addCandidate();
            v.push_back(c);
        }
        void addfailure()
        {
            int max=0;
            for(int i=0;i<v.size();i++)
            {
                if(v[i].id>max && v[i].active)
                {
                    max=v[i].id;
                    currindex=i;
                }
            }
            cout<<"Current Coordinator is "<<v[currindex].id<<endl;
            cout<<"Failure of Current Coordinator"<<endl;
            v[currindex].active=false;
            cout<<"Election initiated..."<<endl;
        }
        void ringelection()
        {
            int old=currindex;
            int new1=old-1;
            int cnt=0,next;

            while(new1!=old)
            {
                next=(new1+1)%v.size();
                if(new1==old-1 && cnt==0)
                {
                    next=(new1+2)%v.size();
                    sleep(4);
                    cout<<"Message from coordinator "<<v[new1].id<<" to "<<v[next].id<<endl;
                    cnt++;
                    new1=next;
                    continue;
                }
                if(v[next].active)
                {
                    sleep(3);
                    cout<<"Message from coordinator "<<v[new1].id<<" to "<<v[next].id<<endl;
                }
                new1=next;
            }
            int max=0;
            for(int i=0;i<v.size();i++)
            {
                if(v[i].id>max && v[i].active)
                {
                    max=v[i].id;
                    currindex=i;
                }
            }
            cout<<"New coordinator is "<<v[currindex].id<<endl;
        }
        void bullyelection()
        {
            int old=currindex;
            int new1=(rand()%(v.size()-1));

            cout<<"Decteted by "<<v[new1].id<<endl;
            
            while(true)
            {
                for(int i=new1;i<v.size()-1;i++)
                {
                    cout<<"Message from "<<v[new1].id<<" to "<<v[i+1].id<<endl;
                }
                for(int i=v.size()-1;i>new1;i--)
                {
                    if(v[i].active)
                        cout<<"OK from "<<v[i].id<<" to "<<v[new1].id<<endl;
                }
                if(new1<v.size()-1 && v[new1].active)
                    new1++;
                else
                    break;
            }
            cout<<"New coordinator is "<<v[new1-1].id<<endl;
        }
};
int main()
{
    Election e;
    int n,ch;

    do
    {
        cout<<"Enter the no. of nodes: ";
        cin>>n;
        for(int i=0;i<n;i++)
        {
            e.getCandidate();
        }
        cout<<"1.Ring\n2.Bully\n3.Exit\nEnter your choice:";
        cin>>ch;

        switch(ch)
        {
            case 1: e.addfailure();
                    e.ringelection();
                    break;
            case 2: e.addfailure();
                    e.bullyelection();
                    break;
            case 3: cout<<"Thanks"<<endl;
                    break;
            default:cout<<"Invalid choice..."<<endl;
        }
    } while (ch!=3);    
    return 0;
}