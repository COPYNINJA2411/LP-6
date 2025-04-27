
#include<iostream>
#include<omp.h>
#define _BSD_SOURCE_
#include <sys/time.h>
using namespace std;

void bubble(int arr[],int n)
{
    cout<<"Sequential Bubble Sort"<<endl;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void bubbleParallel(int arr[],int n)
{   
    cout<<"Parallel Bubble Sort"<<endl;;
    for(int i=0;i<n-1;i++)
    {
        #pragma omp parallel 
        for(int j=0;j<n-i-1;j++)
        {
            #pragma omp critical
            {
                if(arr[j]>arr[j+1])
                {
                    int temp=arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                }
            }
            
        }
    }
}

void merge(int arr[],int left,int mid,int right)
{
    int p1=left;
    int p2=mid+1;
    
    int narr[right-left+1];
    int i=0;
    
    
    while(p1<=mid && p2<=right)
    {
        if(arr[p1]<=arr[p2])
        {
            narr[i]=arr[p1];
            i++;
            p1++;
        }
        
        else
        {
            narr[i]=arr[p2];
            i++;
            p2++;
        }
    }
    while(p1<=mid )
    {
            narr[i]=arr[p1];
            i++;
            p1++;
    }
    
    while(p2<=right )
    {
            narr[i]=arr[p2];
            i++;
            p2++;
    }
    
    
    for(int k=0,x=left;k<sizeof(narr)/sizeof(narr[0]);k++,x++)
    {
        arr[x]=narr[k];
    }
}
void mergeSeq(int arr[],int left,int right)
{
   
    if(left<right)
    {
        int mid=left+(right-left)/2;
        mergeSeq(arr,left,mid);
        mergeSeq(arr,mid+1,right);
        merge(arr,left,mid,right);
        
    }
}

void mergePar(int arr[],int left,int right)
{
    
    if(left<right)
    {
        int mid=left+(right-left)/2;
        #pragma omp parallel
        { mergeSeq(arr,left,mid);}
        #pragma omp parallel
        { mergeSeq(arr,mid+1,right);}
        #pragma omp critical
        { merge(arr,left,mid,right);}
        
        
    }
}


int main()
{
    int n,ch;
    cout<<"Enter the size of Array"<<endl;
    cin>>n;
    int arr[n];
    
    cout<<"Enter the elements"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    
    cout<<"Enter: 1- Sequential Bubble sort || 2- Parallel Bubble sort || 3- Sequential Merge sort || 4-Parallel Merge sort "<<endl;
    cin>>ch;
    
    
    struct timeval start,end;
    if(ch==1)
    {
        gettimeofday(&start,NULL);
        bubble(arr,n);
    }
    else if(ch==2)
    {
        gettimeofday(&start,NULL);
        bubbleParallel(arr,n);
    }
    else if(ch==3)
    {
        cout<<"Sequential Merge Sort"<<endl;
        gettimeofday(&start,NULL);
        mergeSeq(arr,0,n-1);
    }
    else if(ch==4)
    {
        cout<<"Parallel Merge Sort"<<endl;
        gettimeofday(&start,NULL);
        mergePar(arr,0,n-1);
    }
    else
    {
        cout<<"Invalid Choice :"<<endl;
        return 0;
    }
    cout<<"Sorted array :"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    gettimeofday(&end,NULL);
    cout<<"TIME "<<(end.tv_sec-start.tv_sec)*1e9+(end.tv_usec-start.tv_usec)*1000<<" sec";
    
}