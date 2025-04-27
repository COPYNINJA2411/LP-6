#include <iostream>
#include <stack>
#include <queue>
#include <omp.h>
#include <vector>
using namespace std;

class TreeNode
{
public:
    TreeNode *left;
    TreeNode *right;
    int data;
    TreeNode(int x)
    {
        data = x;
        left = right = NULL;
    }
};

class Tree
{
public:
    TreeNode *root;
    Tree() { root = NULL; }

    void insert(int x)
    {
        TreeNode *n = new TreeNode(x);
        if (root == NULL)
            root = n;
        else
        {
            queue<TreeNode *> q;
            q.push(root);

            int flag = 0;

            while (!q.empty() && !flag)
            {
                for (int i = 0; i < q.size(); i++)
                {
                    TreeNode *temp = q.front();
                    q.pop();

                    if (temp->left == NULL)
                    {
                        temp->left = n;
                        flag = 1;
                    }
                    else
                    {
                        q.push(temp->left);
                        if (temp->right == NULL)
                        {
                            temp->right = n;
                            flag = 1;
                        }
                        else
                            q.push(temp->right);
                    }
                }
            }
        }
    }

    void bfs()
    {
        if (root == NULL)
            return;

        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int n = q.size();
            vector<TreeNode *> levelNodes(n);

            // Fetch nodes of current level
            for (int i = 0; i < n; i++)
            {
                levelNodes[i] = q.front();
                q.pop();
            }

            vector<TreeNode *> nextLevel;

            #pragma omp parallel for
            for (int i = 0; i < n; i++)
            {
                TreeNode *current = levelNodes[i];

                // Print node data in parallel
                #pragma omp critical
                cout << current->data << " | ";

                // Collect children in the critical section to ensure thread safety
                if (current->left)
                    nextLevel.push_back(current->left);
                if (current->right)
                    nextLevel.push_back(current->right);
            }

            // Push next level nodes into the queue in a critical section
            for (int i = 0; i < nextLevel.size(); i++)
            {
                #pragma omp critical
                q.push(nextLevel[i]);
            }
        }
        cout << endl;
    }

    void dfs()
    {
        if (root == NULL)
            return;

        TreeNode *temp = root;
        stack<TreeNode *> s;
        s.push(root);

        while (!s.empty())
        {
            TreeNode *current = s.top();
            s.pop();

            // Print in prefix order
            cout << current->data << " | ";

            // Push right child first to ensure left child is processed first in DFS
            if (current->right)
                s.push(current->right);
            if (current->left)
                s.push(current->left);
        }
        cout << endl;
    }
};

int main()
{
    Tree *t = new Tree();
    while (true)
    {
        int ch;
        cout << "Enter 1-Insert | 2-BFS | 3-DFS | 0-Exit : ";
        cin >> ch;

        if (ch == 1)
        {
            cout << "Enter a number to insert: ";
            cin >> ch;
            t->insert(ch);
        }
        else if (ch == 2)
            t->bfs();
        else if (ch == 3)
            t->dfs();
        else if (ch == 0)
        {
            cout << "Exited successfully." << endl;
            break;
        }
        else
            cout << "Invalid Input." << endl;
    }

    return 0;
}



