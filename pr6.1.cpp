#include <iostream>
#include <ctime>

using namespace std;

struct FloatNode
{
    double nodeValue;
    FloatNode* nextNode;
} *initialRoot=nullptr,*newRoot=nullptr;

FloatNode* push(FloatNode* root,double newValue)
{
    FloatNode* newNode;
    newNode=new FloatNode;
    newNode->nodeValue=newValue;
    newNode->nextNode=root;
    root=newNode;
    return root;
}

FloatNode* pull(FloatNode* root)
{
    FloatNode* tempNode;
    if(root==nullptr)
    {
        cout<<"The stack is empty"<<endl;
        return nullptr;
    }
    tempNode=root;
    root=root->nextNode;
    delete tempNode;
    return root;
}

double top(FloatNode* root)
{
    return root->nodeValue;
}

void printStack(FloatNode* root)
{
    FloatNode* traverseNode;
    traverseNode=root;
    if(traverseNode==nullptr)
    {
        cout<<"The stack is empty"<<endl;
        return;
    }
    while(traverseNode!=nullptr)
    {
        cout<<traverseNode->nodeValue<<" ";
        traverseNode=traverseNode->nextNode;
    }
    cout<<endl;
}

FloatNode* clearStack(FloatNode* root)
{
    while(root!=nullptr)
    {
        root=pull(root);
    }
    return root;
}

int main()
{
    int i;
    double randomValue;
    double thresholdValue;
    double currentValue;
    double elementsSum;
    int elementsCount;
    FloatNode* traverseNode;

    srand(time(0));
    for(i=0;i<10;i++)
    {
        randomValue=(rand()%1701)/100.0-6.0;
        initialRoot=push(initialRoot,randomValue);
    }

    cout<<"Initial stack:"<<endl;
    printStack(initialRoot);

    cout<<"Enter threshold value:"<<endl;
    cin>>thresholdValue;

    while(initialRoot!=nullptr)
    {
        currentValue=top(initialRoot);
        initialRoot=pull(initialRoot);
        if(currentValue>=thresholdValue)
        {
            newRoot=push(newRoot,currentValue);
        }
    }

    cout<<"New stack:"<<endl;
    printStack(newRoot);

    elementsSum=0.0;
    elementsCount=0;
    traverseNode=newRoot;
    while(traverseNode!=nullptr)
    {
        elementsSum=elementsSum+traverseNode->nodeValue;
        elementsCount=elementsCount+1;
        traverseNode=traverseNode->nextNode;
    }

    if(elementsCount>0)
    {
        cout<<"Arithmetic mean:"<<elementsSum/elementsCount<<endl;
    }
    else
    {
        cout<<"New stack is empty"<<endl;
    }

    initialRoot=clearStack(initialRoot);
    newRoot=clearStack(newRoot);
    return 0;
}