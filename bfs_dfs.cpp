#include<iostream>
#include<stack>
#include<queue>
using namespace std;

class Treenode{
    public:
    Treenode *left;
    Treenode *right;
    int data;
    
    Treenode(int n)
    {
        data=n;
        left=right=NULL;
    }
};

class Tree
{
    public:
    
    Treenode *root;
    Tree()
    {
        root=NULL;
    };
    
    void insert(int data)
    {
        Treenode *n=new Treenode(data);
        if(root==NULL)
        {
            root=n;
        }
        else
        {
            queue<Treenode *>q;
            q.push(root);
            
            int flag=0;
            
            while(!q.empty() && !flag)
            {
                for(int i=0;i<q.size();i++)
                {
                    Treenode *temp=q.front();
                    q.pop();
                    
                    if(temp->left==NULL)
                    {
                        temp->left=n;
                        flag=1;
                    }
                    else
                    {
                        q.push(temp->left);
                        if(temp->right==NULL)
                        {
                            temp->right=n;
                            flag=1;
                        }
                        else
                        {
                            q.push(temp->right);
                        }
                        
                    }
                }
            }
        }
    }
    
    void bfs()
    {
        queue<Treenode *>q;
        q.push(root);
        
        while(!q.empty())
        {
            int n=q.size();
            
            #pragma omp parallel for
            for(int i=0;i<n;i++)
            {
                Treenode *temp;
                #pragma omp critical
                {
                    temp=q.front();
                    q.pop();
                    
                    cout<<temp->data<<" | ";
                }
               
                if(temp->left!=NULL)
                {
                    q.push(temp->left);
                }
                if(temp->right!=NULL)
                {
                    q.push(temp->right);
                }
            }
        }
        cout<<endl;
        
        
    }
    
    void dfs()
    {
        Treenode *temp=root;
        stack<Treenode *>s;
        s.push(root);
        
        
        while(!s.empty())
        {
            int n=s.size();
            #pragma omp parallel for
            for(int i=0;i<n;i++)
            {
                #pragma omp critical
                {
                    while(temp!=NULL)
                    {
                        temp=temp->left;
                        if(temp!=NULL)
                        {
                            s.push(temp);
                        }
                    }
                        temp=s.top();
                        s.pop();
                        
                        cout<<temp->data<<" | ";
                        
                        if(temp->right!=NULL)
                        {
                             s.push(temp->right);
                        }
                        temp=temp->right;
                    
                } 
                
            }
        }
        cout<<endl;
    }
};

int main()
{
    Tree *t=new Tree();
    
    while(true)
    {
        int ch,n;
        cout<<"Enter 1- Insert || 2- BFS || 3- DFS || 4- Exit"<<endl;
        cin>>ch;
        
        if(ch==1)
        {
            cout<<"Enter NO"<<endl;
            cin>>n;
            t->insert(n);
        }
        else if(ch==2)
        {
            t->bfs();
        }
        else if(ch==3)
        {
            t->dfs();
        }
        else if(ch==4)
        {
            break;
        }
        else
        {
            return 0;
        }
    
    }
    
}