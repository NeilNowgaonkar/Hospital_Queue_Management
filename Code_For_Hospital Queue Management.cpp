#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<ctime>
using namespace std;
struct info             // Basic structure fro Accepting details
{
    char name[20];
    int age,id;
    int dt,mt,yr;
    int hr,mins,secs;

};
class queue
{
    struct node     //  Declaring structure for creating linked list
    {
        info data;
        struct node *next;
    };
public:
    node *front,*rear;      // Declaring front and rear pointer for queue
    void enque(info);       // For en-queuing the data
    info deque();           // For dequeuing the data
    int isempty();
    int priority(int);
    void display(info);
    void disp_q();
    info search_id(int);
    queue();

};
queue::queue()          // Constructor for Declaring front and rear as NULL
{
    front=NULL;
    rear=NULL;
}
void queue::enque(info data)    // Enqueuing the data in Queue using LINKED LIST
{
    struct node *temp=new struct node;
    temp->next=NULL;
    temp->data=data;
    if(front==NULL)
    {
        front=temp;
        rear=temp;
    }
    else
    {
        rear->next=temp;
        rear=temp;
    }
}
info queue::deque()         // For Dequeuing the data
{
    struct node *temp = new struct node;
    info details;
    temp=front;
    if(front==NULL)
    {
        cout<<"\n the list is empty ";
    }
    else if(front==rear)
    {
        details=front->data;
        front=NULL;
        rear=NULL;
    }
    else
    {
        details=front->data;
        front=front->next;
        temp->next=NULL;

    }
    delete temp;
    return details;
}
int priority(int dis)       // Priority According to diseases
{
    if(dis==1 || dis==7)    //Checking if fever or any other disease
    {
        return 2;           //Low Priority
    }
    else if(dis==2 || dis==6)   //Checking if typhoid or headache
    {
        return 1;               //Medium Priority
    }
    else if(dis==3 || dis==4 || dis==5) // Checking if cancer, malaria or dengue
    {
        return 0;                       //High Priority
    }
}
void queue::disp_q()        //  for Displaying the data
{
    info data;
    struct node *temp=front;
    while(temp!=NULL)
    {
        data=temp->data;
        display(data);
        cout<<"\n";
        temp=temp->next;
    }

}
void queue::display(info data)
{
    cout<<"\n Name  : "<<data.name;
    cout<<"\n Age   : "<<data.age;
    cout<<"\n Id    : "<<data.id;
}
info queue::search_id(int temp)
{
    info data;
    struct node *head=front;
    while(head!=NULL)
    {
        data=head->data;
        if(temp==data.id)
        {
           return data;
        }
        head=head->next;
    }

}
int queue::isempty()        // Checking if queue is empty or not
{
    if(front==NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    info data;
    queue q[3];         // Declaring queue
    int cho,ch,dis;
    FILE *fp;

    do
    {
        cout<<"\n\t\t\t----------------------------------------------\n";
        cout<<"\n\t\t\t\t 1. Add   Patient ";
        cout<<"\n\t\t\t\t 2. Treat Patient ";
        cout<<"\n\t\t\t\t 3. Display Queue ";
        cout<<"\n\t\t\t\t 4. Existing Patient ";
        cout<<"\n\t\t\t\t 5. All Records ";
        cout<<"\n\t\t\t\t 6. Exit \n";
        cout<<"\n\t\t\t----------------------------------------------\n";
        cout<<"\n\t Enter Choice : ";

        cin>>cho;
        if(cho==1)
        {
            fp=fopen("hospital_que.txt","a");
            do
            {
                cout<<"\n-----------------------------\n";
                time_t todays_time=time(0);
                tm *ltm=localtime(&todays_time);
                char* dt=ctime(&todays_time);
                cout<<"\n Todays Current Date and Time : "<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/"<<1900+ltm->tm_year<<"\t"<<ltm->tm_hour<<":"<<ltm->tm_min<<":"<<ltm->tm_sec<<endl;
                data.dt=ltm->tm_mday;
                data.mt=1+ltm->tm_mon;
                data.yr=1900+ltm->tm_year;
                data.hr=ltm->tm_hour;
                data.mins=ltm->tm_min;
                data.secs=ltm->tm_sec;
                cout<<"\n Enter Name : ";
                cin>>data.name;
                cout<<"\n Enter Age  : ";
                cin>>data.age;
                cout<<"\n Enter Id   : ";
                cin>>data.id;
                cout<<"\n Enter Disease : 1. Fever 2. Typhoid 3. Cancer 4. Malaria 5. Dengue 6. Headache 7. Other \n";

                cin>>dis;
                fprintf(fp,"%d %d %s %d %d %d %d %d %d\n",data.id,data.age,data.name,data.dt,data.mt,data.yr,data.hr,data.mins,data.secs);
                dis=priority(dis);
                q[dis].enque(data);
                cout<<"\n------------------------------\n";

                cout<<"\n Do you wish to continue (1/0) : ";
                cin>>ch;
            }while(ch!=0);
            fclose(fp);
        }
        else if(cho==2)
        {
            if(q[0].isempty()==0)
            {
                data=q[0].deque();
                q[0].display(data);
                cout<<endl;
            }
            else if(q[1].isempty()==0)
            {
                data=q[1].deque();
                q[1].display(data);
                cout<<endl;
            }
            else if(q[2].isempty()==0)
            {
                data=q[2].deque();
                q[2].display(data);
                cout<<endl;
            }
            else
                cout<<"\n All Patient are treated "<<endl;
        }
        else if(cho==3)
        {
            cout<<"\n High Priority Patients ";
            if(q[0].isempty()==0)
            {
                q[0].disp_q();
            }
            else
            {
                cout<<"\n No High Priority Patients to serve"<<endl;
            }
            cout<<"\n Mid  Priority Patients ";
            if(q[1].isempty()==0)
            {
                q[1].disp_q();
            }
            else
            {
                cout<<"\n No Mid Priority Patients to serve"<<endl;
            }
            cout<<"\n Low Priority Patients ";
            if(q[2].isempty()==0)
            {
                q[2].disp_q();
            }
            else
            {
                cout<<"\n No Low Priority Patients to serve"<<endl;
            }
        }
        if(cho==4)
        {
            int temp,flag=0;
            fp=fopen("hospital_que.txt","r");
            cout<<"\n Enter Your ID : ";
            cin>>temp;
            do
            {
                fscanf(fp,"%d %d %s %d %d %d %d %d %d\n",&data.id,&data.age,data.name,&data.dt,&data.mt,&data.yr,&data.hr,&data.mins,&data.secs);
               // if(feof(fp))
                //    break;
                if(temp==data.id)
                {
                    cout<<"\n Name  : "<<data.name;
                    cout<<"\n Age   : "<<data.age;
                    cout<<"\n ID    : "<<data.id;
                    flag=1;
                    break;
                }
            }while(!feof(fp));
            if(flag==0)
            {
                cout<<"\nNo Records Found with Exisiting ID ";
            }
            else
            {
                cout<<"\nEnter New Details ";
                cout<<"\n-----------------------------\n";


                cout<<"\n Enter Disease : 1. Fever 2. Typhoid 3. Cancer 4. Malaria 5. Dengue 6. Headache 7. Other ";
                cin>>dis;
                dis=priority(dis);
                q[dis].enque(data);
                cout<<"\n------------------------------\n";

            }
            fclose(fp);
        }
        if(cho==5)
        {
            int temp;
            fp=fopen("hospital_que.txt","r");
            cout<<"\n--------------------------------------------------------------------\n";
            cout<<setw(3)<<"ID"<<setw(10)<<"Age"<<setw(10)<<"Name"<<setw(15)<<"Date"<<setw(20)<<"Time"<<endl;
            cout<<"--------------------------------------------------------------------\n";
            do
            {
                fscanf(fp,"%d %d %s %d %d %d %d %d %d\n",&data.id,&data.age,data.name,&data.dt,&data.mt,&data.yr,&data.hr,&data.mins,&data.secs);
                cout<<setw(2)<<data.id<<setw(10)<<data.age<<setw(13)<<data.name<<setw(10)<<data.dt<<"/"<<data.mt<<"/"<<data.yr<<setw(13)<<data.hr<<":"<<data.mins<<":"<<data.secs<<endl;

            }while(!feof(fp));
            fclose(fp);
        }
    }while(cho!=6);
    fclose(fp);
}
