#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

struct IntNode
{
    int nodeValue;
    IntNode* nextNode;
} *firstInitial=nullptr,*lastInitial=nullptr,*firstNew=nullptr,*lastNew=nullptr;

IntNode* enqueueInitial(IntNode* firstNode,int newValue)
{
    IntNode* newNode;
    newNode=new IntNode;
    newNode->nodeValue=newValue;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastInitial=newNode;
        return firstNode;
    }
    lastInitial->nextNode=newNode;
    lastInitial=newNode;
    return firstNode;
}

IntNode* enqueueNew(IntNode* firstNode,int newValue)
{
    IntNode* newNode;
    newNode=new IntNode;
    newNode->nodeValue=newValue;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastNew=newNode;
        return firstNode;
    }
    lastNew->nextNode=newNode;
    lastNew=newNode;
    return firstNode;
}

IntNode* dequeueInitial(IntNode* firstNode)
{
    IntNode* tempNode;
    if(firstNode==nullptr)
    {
        cout<<"Queue is empty"<<endl;
        return nullptr;
    }
    tempNode=firstNode;
    firstNode=firstNode->nextNode;
    if(firstNode==nullptr)
    {
        lastInitial=nullptr;
    }
    delete tempNode;
    return firstNode;
}

int frontValue(IntNode* firstNode)
{
    return firstNode->nodeValue;
}

void printQueue(IntNode* firstNode)
{
    IntNode* traverseNode;
    traverseNode=firstNode;
    while(traverseNode!=nullptr)
    {
        cout<<traverseNode->nodeValue<<" ";
        traverseNode=traverseNode->nextNode;
    }
    cout<<endl;
}

int main()
{
    int i;
    int randomValue;
    int currentValue;
    double logSum;
    int elementsCount;
    IntNode* traverseNode;
    IntNode* tempNode;

    srand(time(0));
    for(i=0;i<8;i++)
    {
        randomValue=rand()%50+1;
        firstInitial=enqueueInitial(firstInitial,randomValue);
    }
    
    cout<<"Initial queue:"<<endl;
    printQueue(firstInitial);
    
    while(firstInitial!=nullptr)
    {
        currentValue=frontValue(firstInitial);
        firstInitial=dequeueInitial(firstInitial);
        firstNew=enqueueNew(firstNew,currentValue);
        if(currentValue%2==0)
        {
            firstNew=enqueueNew(firstNew,100);
        }
    }
    
    cout<<"New queue:"<<endl;
    printQueue(firstNew);
    
    logSum=0.0;
    elementsCount=0;
    traverseNode=firstNew;
    while(traverseNode!=nullptr)
    {
        logSum=logSum+log(traverseNode->nodeValue);
        elementsCount=elementsCount+1;
        traverseNode=traverseNode->nextNode;
    }
    
    if(elementsCount>0)
    {
        cout<<"Geometric mean:"<<exp(logSum/elementsCount)<<endl;
    }
    else
    {
        cout<<"New queue is empty"<<endl;
    }
    
    while(firstInitial!=nullptr)
    {
        firstInitial=dequeueInitial(firstInitial);
    }
    while(firstNew!=nullptr)
    {
        tempNode=firstNew;
        firstNew=firstNew->nextNode;
        delete tempNode;
    }
    lastNew=nullptr;

    return 0;
}