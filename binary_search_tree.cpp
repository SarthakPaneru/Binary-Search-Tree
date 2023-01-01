#include <iostream>
#include <chrono> // to calculate execution time of a function
// #include <time.h>
#include <unistd.h>


using namespace std;

struct Node
{
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node, int data)
{
    if (node == NULL)
    {
        return newNode(data);
    }
    else if(data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if(data > node->data)
    {
        node->right = insert(node->right, data);
    }

    return node;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
}

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        cout<<root->data<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct Node *root)
{
    if(root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout<<root->data<<" ";
    }
}

int height(struct Node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    int lDepth = height(root->left);
    int rDepth = height(root->right);

    if (lDepth > rDepth)
    {
        return lDepth+1;
    } else
    {
        return rDepth+1;
    }
}

bool isEmpty(struct Node *node)
{
    if(node == NULL)
    {
        return true;
    }
    return false;
}

bool search(Node *root, int data)
{
    // cout<<"\nRoot.data at first = "<<root->data<<" Data  =  "<<data<<endl;

    // if(root == NULL)
    // {
    //     return false;
    // }

    if(root->data == data)
    {
        return true;
    }
    //int ht = 3;//height(root);
    // cout<<"Root.data = "<<root->data<<" Data  =  "<<data<<endl;
    if(data < root->data)
    {
        if(root->left == NULL)
        {
            return false;
        }

        search(root->left, data);
    } else {
        if(root->right == NULL)
        {
            return false;
        }
        search(root->right, data);
    }
    // cout<<"Bahira aayo"<<endl;
    // return false;

    // for(int i=0; i<ht; i++)
    // {
    //     if(data < root->data)
    //     {
    //         search(root->left, data);
    //     }
    //     else if(data > root->data)
    //     {
    //         search(root->right, data);
    //     }
    //     else if(data == root->data)
    //     {
    //         return true;
    //     }
    //     else
    //     {
    //         return false;
    //     }
    // }
    //return false;
}

int findMinMax(struct Node *root)
{
    int ht = height(root);
    int htL = height(root->left);
    cout<<"Ht left: "<<htL<<endl;
    int htR = height(root->right);
    cout<<"Ht right: "<<htR<<endl;
    int minMax;
    struct Node *node;
    // int min = root->right->data;
    struct Node *temp = root;
    int count = 0;
    
    if(htR >= htL )
    {
        node = root->right;
        minMax = node->data;
        temp = node;

        while (node != NULL && node->left != NULL)
        {
            temp = node;
            node = node->left;
            minMax = node->data;
            count++;
        }
        // free(temp->left);
        if(count == 0)
        {
            root->right = NULL;
            free(root->right);
        }
        temp->left = NULL;
        free(temp->left);
    } else
    {
        node = root->left;
        minMax = node->data;
        temp = node;

        while (node != NULL && node->left != NULL)
        {
            temp = node;
            node = node->right;
            minMax = node->data;
            count++;
        }
        if(count == 0)
        {
            root->left = NULL;
            free(root->left);
        }
        // free(temp->right);
        temp->right = NULL;
        free(temp->right);
    }
     
    return minMax;
    
}

struct Node* deleteNode(struct Node *root, int data, int ht, struct Node *parent)
{
    // cout<<endl<<"Function chalxa"<<endl;
    
    ht--;
    // cout<<temp2->left->data<<endl;
    int k = 7;

    if(root == NULL)
    {
        free(root);
        return NULL;
    }

    // .....This is the next segment.....

    if(root->data == data)
    {

        if (root->left != NULL && root->right != NULL)
        {
            int minMax = findMinMax(root);
            cout<<minMax<<endl;
            root->data = minMax;
            
        }
        else if (root->left == NULL && root->right == NULL)
        {
            
            // first if statement to delete last node in the tree
            if (parent == NULL)
            {
                root->data = NULL;
                root = NULL;
                // free(root);
                // free(root); dont free root node
            }

            else if (parent->left != NULL && parent->left->data == data)
            {

                parent->left = NULL;
                free(root);
            } else if(parent->right->data == data)
            {
                parent->right = NULL;
                free(root);
            }
        }
        // It is better to breakdown into two else if cases
        // else if (root->left == NULL || root->right == NULL)
        else if (root->left == NULL)
        {
            struct Node *temp = NULL;
            temp = root;

            if (parent == NULL)
            {
                struct Node *deleteNext = NULL;
                deleteNext = root->right;

                root->data = deleteNext->data;
                root->right = deleteNext->right;
                root->left = deleteNext->left;
                deleteNext = NULL;
                free(deleteNext);
                // return root;
            }
            else if(parent->left != NULL && parent->left->data == data)
            {
                parent->left = root->right;
                free(temp);
            } else
            {
                parent->right = root->right;
                free(temp);
            }
        } else if(root->right == NULL)
        {
            struct Node *temp = NULL;
            temp = root;
            // cout<<"Parent: "<<NULL<<endl;

            if (parent == NULL)
            {
                struct Node *deleteNext = NULL;
                deleteNext = root->left;

                root->data = root->left->data;
                root->right = root->left->right;
                root->left = root->left->left;

                deleteNext = NULL;
                free(deleteNext);

                // return root;
            }
            else if(parent->left != NULL && parent->left->data == data)
            {
                parent->left = root->left;
                free(temp);
            } else
            {
                parent->right = root->left;
                free(temp);
            }
        }
    }
    else if(data < root->data)
    {
        deleteNode(root->left, data, ht, root);
    } else if(data > root->data) {
        deleteNode(root->right, data, ht, root);
    }
}

void showTree()
{

}

int main()
{
    struct Node *node = NULL;

    int choice;
    int data;

    while (true)
    {

        cout<<"\n***** BINARY SEARCH *****"<<endl;
        cout<<"1. Simple Binary Search"<<endl;
        cout<<"2. FInd Time Complexity from large data set"<<endl;
        cout<<"3. Exit"<<endl;
        cin>>choice;


        switch (choice)
        {
        case 1:
            node = insert(node, 50);
            insert(node, 30);
            insert(node, 20);
            insert(node, 40);
            insert(node, 70);
            insert(node, 60);
            insert(node, 80);


            cout<<"\nIn-Order: ";
            inorder(node);

            cout<<"\nPre-Order: ";
            preOrder(node);

            cout<<"\nPost-Order: ";
            postOrder(node);

            data = 800; 
            break;

        case 2:
            int counter;
            cout<<"Enter the no of data sets to insert in Binary Tree: ";
            cin>>counter;

            // Return new random value after each execution
            srand(time(NULL));

            if(node==NULL)
            {
                node = insert(node, rand()%counter);
            }

            {
                auto start = std::chrono::high_resolution_clock::now();


                for (int i = 1; i <= counter; ++i)
                {
                    insert(node, rand()%counter);
                }
                auto end = std::chrono::high_resolution_clock::now();

                double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
                cout<<"\n\nInsertion completed in "<<elapsed_time<<" ms"<<endl;

                sleep(2);
            }

            // Display data in In-Order Traversal
            cout<<"\nIn-Order: ";
            {
                auto start = std::chrono::high_resolution_clock::now();

                inorder(node);

                auto end = std::chrono::high_resolution_clock::now();
                double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
                cout<<"\n\nIn-Order Traversal completed in "<<elapsed_time<<" ms"<<endl;

                sleep(2);
            }

            // Display data in Pre-Order Traversal
            cout<<"\nPre-Order: ";
            {
                auto start = std::chrono::high_resolution_clock::now();

                preOrder(node);

                auto end = std::chrono::high_resolution_clock::now();
                double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
                cout<<"\n\nPre-Order Traversal completed in "<<elapsed_time<<" ms"<<endl;
                sleep(5);
            }

            // Display data in Post-Order Traversal
            cout<<"\nPost-Order: ";
            {
                auto start = std::chrono::high_resolution_clock::now();

                postOrder(node);

                auto end = std::chrono::high_resolution_clock::now();
                double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
                cout<<"\n\nPost-Order Traversal completed in "<<elapsed_time<<" ms"<<endl;

                sleep(2);
            }

            cout<<"\nEnter the no to search: ";
            cin>>data;
            cout<<data<<endl;
            
            break;

        case 3:
            exit(0);
        
        default:
            cout<<"Wrong Input"<<endl;
            break;
        }

        bool stop = false;

        while(!stop)
        {

            int ht = height(node);
            cout<<"\n\nHeight: "<<ht;

            bool present;
            
            if (node!=NULL)
            {
                auto start = std::chrono::high_resolution_clock::now();
                present = search(node, data);
                auto end = std::chrono::high_resolution_clock::now();
                double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
                cout<<endl<<endl<<data<<" found: "<<boolalpha<<present<<endl;
                cout<<"\nSearch completed in "<<elapsed_time<<" ms"<<endl;
            } else {
                cout<<"\nEmpty Tree"<<endl;
            }

            // Delete node
            //int del;
            cout<<"\nEnter data to be deleted: "<<endl;
            cin>>data;

            present = search(node, data);

            // cout<<endl<<node<<endl;
            auto start = std::chrono::high_resolution_clock::now();

            if(present)
            {
                deleteNode(node, data, ht, NULL);
                if(node == NULL)
                {
                    stop = true;
                    cout<<endl<<"Empty Tree"<<endl;
                }
            } else
            {
                cout<<endl<<data<<" not found"<<endl;
            }

            auto end = std::chrono::high_resolution_clock::now();
            double elapsed_time = std::chrono::duration<double, std::milli>(end - start).count();
            cout<<"\nDeletion completed in "<<elapsed_time<<" ms"<<endl;

            cout<<"Node = "<<node->data<<endl;

            inorder(node);
            cout<<endl<<endl;
            preOrder(node);       
            
        }
    }
    return 0;
}