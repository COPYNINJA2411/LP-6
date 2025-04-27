
#include<iostream>
#include<omp.h>
#define _BSD_SOURCE_
#include <sys/time.h>
using namespace std;

int sum_sequential(int arr[],int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum+=arr[i];
    }
    return sum;
  
}

int sum_parallel(int arr[],int n)
{
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<n;i++)
    {
        sum+=arr[i];
    }
    return sum;
    
}

float average_seq(int arr[],int n)
{
    int sum=sum_sequential(arr,n);
    return sum/n;
}

float average_parallel(int arr[],int n)
{
    int sum=sum_parallel(arr,n);
    return sum/n;
}

int max_sequential(int arr[],int n)
{
    int max=0;
    for(int i=0;i<n;i++)
    {
        if(arr[i]>max)
            max=arr[i];
    }
    return max;
}

int max_parallel(int arr[],int n)
{
    int max=0;
    #pragma omp parallel for reduction(max:max)
    for(int i=0;i<n;i++)
    {
        if(arr[i]>max)
            max=arr[i];
    }
    return max;
}

int min_sequential(int arr[],int n)
{
    int min=99999;
    for(int i=0;i<n;i++)
    {
        if(arr[i]<min)
            min=arr[i];
    }
    return min;
}

int min_parallel(int arr[],int n)
{
    int min=99999;
    #pragma omp parallel for reduction(min:min)
    for(int i=0;i<n;i++)
    {
        if(arr[i]<min)
            min=arr[i];
    }
    return min;
}

int product_sequential(int arr[],int n)
{
    int sum=1;
    for(int i=0;i<n;i++)
    {
        sum*=arr[i];
    }
    return sum;
  
}

int product_parallel(int arr[],int n)
{
    int sum=1;
    #pragma omp parallel for reduction(*:sum)
    for(int i=0;i<n;i++)
    {
        sum*=arr[i];
    }
    return sum;
    
}

int main()
{
    int n,ch;
    cout<<"Enter the size of Array"<<endl;
    cin>>n;
    int arr[n];
    struct timeval start,end;
    
    cout<<"Enter the elements"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    
    while(true)
    {
        cout<<"Enter: 1-Sequential Sum || 2- Parallel Sum || 3- Sequential average || 4-Parallel average || 5- Max Sequential || 6- Max Parallel || 7- Min Sequential || 8- Min Parallel || 9- Product Sequential || 10 - Product Parallel" <<endl;
        cin>>ch;
        
        if(ch==1)
        {
            gettimeofday(&start,NULL);
            cout<<"Sequential sum: "<<sum_sequential(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==2)
        {
            gettimeofday(&start,NULL);
            cout<<"Parallel sum: "<<sum_parallel(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==3)
        {
            gettimeofday(&start,NULL);
            cout<<"Sequential average: "<<average_seq(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==4)
        {
            gettimeofday(&start,NULL);
            cout<<"Parallel average: "<<average_parallel(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==5)
        {
            gettimeofday(&start,NULL);
            cout<<"Sequential max: "<<max_sequential(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==6)
        {
            gettimeofday(&start,NULL);
            cout<<"Parallel max: "<<max_parallel(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==7)
        {
            gettimeofday(&start,NULL);
            cout<<"Sequential min: "<<min_sequential(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==8)
        {
            gettimeofday(&start,NULL);
            cout<<"Parallel min: "<<min_parallel(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
         if(ch==9)
        {
            gettimeofday(&start,NULL);
            cout<<"Sequential Product: "<<product_sequential(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else if(ch==10)
        {
            gettimeofday(&start,NULL);
            cout<<"Parallel Product: "<<product_parallel(arr,n)<<endl;
            gettimeofday(&end,NULL);
            cout<<"Time: "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" ns"<<endl;
        }
        else
        {
            cout<<"Invalid Choice ";
            break;
        }
    }
}