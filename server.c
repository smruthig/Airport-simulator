#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct que                         //used in queue used for planes
{
    int planeno;
    struct que* link;
};

struct plane                       //used in array holding random numbers of planes for each unit time
{
    int q;
    int flag;
};

struct que* insert_queue(int item, struct que* first)  //inserting a plane in queue
{
    struct que *temp, *cur;
    temp=(struct que*)malloc(1*sizeof(struct que));
    temp->planeno=item;
    temp->link=NULL;
    if (first==NULL)
        return temp;
    cur=first;
    while(cur->link!=NULL)
        cur=cur->link;
    cur->link=temp;
    return first;
}

struct que* del_land( struct que* first)      //deleting an element from queue "land" (plane landed)
{
    struct que* temp;
    temp=first;
    temp=temp->link;
    printf("Plane %d has landed\n",first->planeno);
    free(first);
    return temp;
}

struct que* del_take(struct que* first)      //deleting an element from queue "take" (plane taken off)
{
    struct que* temp;
    temp=first;
    temp=temp->link;
    printf("Plane %d has taken off\n",first->planeno);
    free(first);
    return temp;
}

int count_queue(struct que* first)              //counting number of planes in queue to land/take off
{
    struct que* cur;
    int count=0;
    cur=first;
    while(cur!=NULL)
    {
        count++;
        cur=cur->link;
    }
    return count;
}

float delay(float b)      //delaying the execution of next command (used for more randomness in number of planes)
{
     float sec;
     clock_t starty,end;
     starty =clock();
     b:
        end=clock();
        sec=(end-starty)/1000.0;
        if(sec>=b)
            return 0;
        else goto b;
}

int sum(struct plane *a,int tot_time)       //to count total number of planes ready to land/take-off
{
    int count=0;
    for(int i=0;i<tot_time;i++)
     {
         count+=a[i].q;
     }
    return count;
}

int access_array(struct plane *a,int tot_time)    //accesses elements of random index numbers of array
{
    do
    {
        delay(1);
        srand(time(0));
        int num = (rand() %(tot_time));
        if  (a[num].flag == 0)
        {
            a[num].flag=1;
            return a[num].q;
        }
    }while (1);
}

void sim(int tot_time, int maxarr, int maxdep, float arrrate, float deprate)      //major part of the simulation done here
{
    struct que* firsta;        //queue for planes to land using linked list (queue "land")
    struct que* firstd;        //queue for planes to take off using linked list (queue "take")
    int arrcount=0, depcount=0, success_arr=0, success_dep=0, cancel_arr=0, cancel_dep=0;
    firsta=NULL;
    firstd=NULL;
    struct plane arr[tot_time];     //array to hold random numbers of planes generated per unit time for landing
    struct plane dep[tot_time];     //array to hold random numbers of planes generated per unit time for takeoff

    for (int i=0;i<tot_time;i++)    //initializing array elements to 0
    {
        arr[i].q = 0;
        arr[i].flag = 0;
        dep[i].q = 0;
        dep[i].flag = 0;
    }

    int x1=(int)(arrrate*tot_time);     //for poisson's distribution in landing
    int x2=(int)(deprate*tot_time);     //for poisson's distribution in takeoff

    printf("\nPlease wait:\n\nPreparing the runways...\n\n");

    for (int i=0;i<tot_time;i++)
    {
        delay(1);
        srand(time(0));
        int num = (rand() %(4));
        if (sum(arr,tot_time)+ num <= x1)       //filling array "arr" with random nos.
            arr[i].q=num;
        if (sum(dep,tot_time)+ num <= x2)       //filling array "dep" with random nos.
            dep[i].q=num;
        if ((sum(arr,tot_time)+ num > x1) && (sum(dep,tot_time)+ num > x2))
            break;
        if (i==3)
            printf("Checking plane functionalities...\n\n");
        if (i==7)
            printf("Checking weather...\n\n");
        if (i==15)
            printf("Checking connectivity...\n\n");
        if (i==20)
            printf("Waiting for go-signal from airway control...\n\n");
    }

    //ensuring poisson's distribution

    int diff1 = x1 - sum(arr,tot_time);
    if (diff1>0 &&diff1<5)
        arr[0].q += diff1;
    else if (diff1>=5&&diff1<8)
    {
        arr[0].q =4;
        arr[1].q = diff1-5;
    }
    else if (diff1>=8)
    {
        arr[0].q = 4;
        arr[1].q = 4;
        arr[2].q = diff1-8;
    }

    int diff2 = x2 - sum(dep,tot_time);
    if (diff2>0 && diff2<5)
        dep[0].q += diff2;
    else if (diff2>=5&&diff2<8)
    {
        dep[0].q =4;
        dep[1].q = diff2-5;
    }
    else if (diff2>=8)
    {
        dep[0].q = 4;
        dep[1].q = 4;
        dep[2].q = diff2-8;
    }

    for (int i=0; i<tot_time; i++)
    {
        printf("%d:\n",i+1);
        static int planeno=1;
        int a=access_array(arr,tot_time);
        delay(1);
        int b=access_array(dep,tot_time);
        for(int x=0;x<a;x++)                                //printing planes ready to land
        {
            printf("Plane %d ready to land\n", planeno);
            if(count_queue(firsta)<= maxarr)
            {
                firsta=insert_queue(planeno,firsta);
            }
            else
            {
                printf("Plane %d redirected to another airport due to queue\n", planeno);
                cancel_arr++;

            }
            planeno++;
            arrcount++;
        }
        for(int x=0;x<b;x++)                                    //printing planes ready to takeoff
        {
            printf("Plane %d ready to takeoff\n", planeno);
            if(count_queue(firstd)<=maxdep)
            {
                firstd=insert_queue(planeno,firstd);
            }
            else
             {
                printf("Plane %d cancelled due to queue\n", planeno);
                cancel_dep++;
             }
            planeno++;
            depcount++;
        }

        if (count_queue(firsta)>0)           //Runway 1 action
        {
            printf("Runway 1: ");
            firsta=del_land(firsta);
            success_arr++;
        }
        else
            printf("Runway 1 idle: Landing queue empty\n");

        if (count_queue(firstd)>0)           //Runway 2 action
        {
            printf("Runway 2: ");
            firstd=del_take(firstd);
            success_dep++;
        }
        else
            printf("Runway 2 idle: Takeoff queue empty\n");

        if (count_queue(firsta)>0)           //Runway 3 action
        {
            printf("Runway 3: ");
            firsta=del_land(firsta);
            success_arr++;
        }
        else if (count_queue(firstd)>0)
        {
            printf("Runway 3: ");
            firstd=del_take(firstd);
            success_dep++;
        }
        else
            printf("Runway 3 idle: Both queues empty\n");

    }
    //final stats
    printf("\nTotal number of planes: %d\n",arrcount+depcount);
    printf("Number of planes arrived: %d\nNumber of planes ready to takeoff: %d\n",arrcount,depcount);
    printf("Number of planes successfully landed: %d\nNumber of planes successfully taken off: %d\n",success_arr,success_dep);
    printf("Number of planes redirected before landing: %d\nNumber of planes cancelled from take-off: %d\n", cancel_arr,cancel_dep);
    printf("Number of planes in queue for landing: %d\nNumber of planes in queue for takeoff: %d\n",count_queue(firsta),count_queue(firstd));
    free(firsta);
    free(firstd);
}
