#include <iostream>
#include <unistd.h>
#include <string.h>


using namespace std;

struct Node
{
    string symbol, value;
    bool flag;
    struct Node *left, *right;
};

struct Node* newNode(string symbol, string value, bool flag)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->symbol = symbol;
    node->value = value;
    node->flag = flag;
    node->left = node->right = NULL;
    return node;
}

struct Node* insert(struct Node* node,   string symbol  , string value  , bool flag)
{
    if (node == NULL)
    {
        return newNode(symbol, value, flag);
    }
    else if(symbol.compare(node->symbol) == 0)
    {
        cout<<"doubly defined... rejecting"<<endl;
    }
    else if(symbol.compare(node->symbol) < 0)
    {
        node->left = insert(node->left, symbol, value, flag);
    }
    else if(symbol.compare(node->symbol) > 0)
    {
        node->right = insert(node->right, symbol, value, flag);
    }

    return node;
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->symbol<<"\t|\t"<<root->value<<"\t|\t"<<(root->flag ? "True" : "False")<< "\n";
        cout<<"-------\t-\t-------\t-\t------"<<endl;
        inorder(root->right);
    }
}

void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        cout<<root->symbol<<"\t|\t"<<root->value<<"\t|\t"<<(root->flag ? "True" : "False")<< "\n";
        cout<<"-------\t-\t-------\t-\t------"<<endl;
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
        cout<<root->symbol<<"\t|\t"<<root->value<<"\t|\t"<<(root->flag ? "True" : "False")<< "\n";
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

Node* search(Node *root, string symbol)
{
    if (root == NULL)
    {
        return NULL;
    }
    

    if( symbol.compare(root->symbol) == 0 )
    {
        return root;
    }
    else if(symbol.compare(root->symbol) < 0)
    {
        if(root->left == NULL)
        {
            return NULL;
        }

        return search(root->left, symbol);
    } else {
        if(root->right == NULL)
        {
            return NULL;
        }
        return search(root->right, symbol);
    }
    
}

int main()
{
    struct Node *node = NULL;

    int choice;
    string symbol, value  ;
    bool flag;

    while (true)
    {
        cout<<endl<<"******* Enter Your Choice ***********"<<endl;
        cout<<"1. Insert data"<<endl;
        cout<<"2. Search data"<<endl;
        cout<<"3. Print data in in-order traversal"<<endl;
        cout<<"4. Find height of tree"<<endl;
        cout<<"5. Exit"<<endl;
        cin>>choice;
    
        switch (choice)
        {
        case 1:
            while (true)
            {
                
                while(cout<<"Symbol: " && cin>>symbol && !((symbol[0]>='a' && symbol[0]<='z') || (symbol[0]>='A' && symbol[0]<='Z'))) {
                    cout<<"Illegal Symbol "<<endl;
                }
                if (symbol.length() > 6) {
                    cout<<"Truncating the Symbol to 6 string: ";
                    symbol = symbol.substr(0, 6);
                    cout<<symbol<<endl;
                }

                cout<<"Value: ";
                cin>>value;
                while (std::cout << "Flag: " && !(std::cin >> flag)) {
                    std::cin.clear(); //clear bad input flag
                    cin.ignore(1000, '\n'); // ignores/discards characters in the input buffer until either 1000 have been discarded, or a newline has been encountered,
                    cout << "Enter either 0 or 1\n";
                }
                
                
                if (node == NULL) {
                    node = insert(node, symbol, value, flag);
                } else {
                    insert(node, symbol, value, flag);
                }

                inorder(node);
                cout<<endl<<endl;
                // cout<<"Press enter to insert another data or 'x' to exit."<<endl;
                // string x;
                // cin>>x;
                // char ch = x[0];

                // if (ch=='x' || ch=='X') {
                //     break;
                // }
                break;
            }
            
            break;

        case 2:
        {
            cout<<"Enter the Symbol to search: ";
            cin>>symbol;
            Node *dataNode = search(node, symbol);
            if ( dataNode == NULL ) {
                cout<<"Undefined Symbol"<<endl;
            } else {
                cout<<"Symbol\t|\tValue\t|\tFlag\n";
                cout<<"-------\t-\t-------\t-\t------"<<endl;

                cout<<dataNode->symbol<<"\t|\t"<<dataNode->value<<"\t|\t"<<(dataNode->flag ? "True" : "False")<<endl;
            }
        }
            break;

        case 3:
            cout<<"The data in in-order traversal:"<<endl<<endl;
            cout<<"Symbol\t|\tValue\t|\tFlag\n";
            cout<<"-------\t-\t-------\t-\t------"<<endl;
            inorder(node);
            break;

        case 4:
            cout<<"Height of tree: "<<height(node)<<endl;
            break;

        case 5:
            exit(0);
        
        default:
            cout<<"Invalid Input"<<endl;
            break;
        }
    }
    free(node);

    return 0;
}