#include <iostream>
#include <string>

using namespace std;

struct TeamNode
{
    string teamName;
    string cityName;
    int teamPoints;
    TeamNode* nextNode;
} *firstInit=nullptr,*lastInit=nullptr,*firstUnique=nullptr,*lastUnique=nullptr,*firstHigh=nullptr,*lastHigh=nullptr,*firstTemp=nullptr,*lastTemp=nullptr;

TeamNode* enqueueInit(TeamNode* firstNode,string name,string city,int points)
{
    TeamNode* newNode;
    newNode=new TeamNode;
    newNode->teamName=name;
    newNode->cityName=city;
    newNode->teamPoints=points;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastInit=newNode;
        return firstNode;
    }
    lastInit->nextNode=newNode;
    lastInit=newNode;
    return firstNode;
}

TeamNode* enqueueUnique(TeamNode* firstNode,string name,string city,int points)
{
    TeamNode* newNode;
    newNode=new TeamNode;
    newNode->teamName=name;
    newNode->cityName=city;
    newNode->teamPoints=points;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastUnique=newNode;
        return firstNode;
    }
    lastUnique->nextNode=newNode;
    lastUnique=newNode;
    return firstNode;
}

TeamNode* enqueueHigh(TeamNode* firstNode,string name,string city,int points)
{
    TeamNode* newNode;
    newNode=new TeamNode;
    newNode->teamName=name;
    newNode->cityName=city;
    newNode->teamPoints=points;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastHigh=newNode;
        return firstNode;
    }
    lastHigh->nextNode=newNode;
    lastHigh=newNode;
    return firstNode;
}

TeamNode* enqueueTemp(TeamNode* firstNode,string name,string city,int points)
{
    TeamNode* newNode;
    newNode=new TeamNode;
    newNode->teamName=name;
    newNode->cityName=city;
    newNode->teamPoints=points;
    newNode->nextNode=nullptr;
    if(firstNode==nullptr)
    {
        firstNode=newNode;
        lastTemp=newNode;
        return firstNode;
    }
    lastTemp->nextNode=newNode;
    lastTemp=newNode;
    return firstNode;
}

TeamNode* dequeueInit(TeamNode* firstNode)
{
    TeamNode* tempNode;
    if(firstNode==nullptr)
    {
        return nullptr;
    }
    tempNode=firstNode;
    firstNode=firstNode->nextNode;
    if(firstNode==nullptr)
    {
        lastInit=nullptr;
    }
    delete tempNode;
    return firstNode;
}

TeamNode* dequeueTemp(TeamNode* firstNode)
{
    TeamNode* tempNode;
    if(firstNode==nullptr)
    {
        return nullptr;
    }
    tempNode=firstNode;
    firstNode=firstNode->nextNode;
    if(firstNode==nullptr)
    {
        lastTemp=nullptr;
    }
    delete tempNode;
    return firstNode;
}

void printQueue(TeamNode* firstNode)
{
    TeamNode* traverseNode;
    traverseNode=firstNode;
    while(traverseNode!=nullptr)
    {
        cout<<traverseNode->teamName<<" ("<<traverseNode->cityName<<") - "<<traverseNode->teamPoints<<" pts"<<endl;
        traverseNode=traverseNode->nextNode;
    }
}

int main()
{
    int maxPoints;
    int minPoints;
    string leaderTeam;
    string outsiderTeam;
    int thresholdPoints;
    bool isCityFound;
    bool isFirstElement;
    TeamNode* traverseNode;
    string currentName;
    string currentCity;
    int currentPoints;
    
    firstInit=enqueueInit(firstInit,"Eagles","Kyiv",25);
    firstInit=enqueueInit(firstInit,"Lions","Lviv",18);
    firstInit=enqueueInit(firstInit,"Sharks","Odesa",30);
    firstInit=enqueueInit(firstInit,"Titans","Kyiv",15);
    firstInit=enqueueInit(firstInit,"Bulls","Lviv",22);
    
    thresholdPoints=20;
    isFirstElement=true;
    
    while(firstInit!=nullptr)
    {
        currentName=firstInit->teamName;
        currentCity=firstInit->cityName;
        currentPoints=firstInit->teamPoints;
        
        if(isFirstElement==true)
        {
            maxPoints=currentPoints;
            minPoints=currentPoints;
            leaderTeam=currentName;
            outsiderTeam=currentName;
            isFirstElement=false;
        }
        else
        {
            if(currentPoints>maxPoints)
            {
                maxPoints=currentPoints;
                leaderTeam=currentName;
            }
            if(currentPoints<minPoints)
            {
                minPoints=currentPoints;
                outsiderTeam=currentName;
            }
        }
        
        isCityFound=false;
        traverseNode=firstUnique;
        while(traverseNode!=nullptr)
        {
            if(traverseNode->cityName==currentCity)
            {
                isCityFound=true;
            }
            traverseNode=traverseNode->nextNode;
        }
        if(isCityFound==false)
        {
            firstUnique=enqueueUnique(firstUnique,currentName,currentCity,currentPoints);
        }
        
        if(currentPoints>thresholdPoints)
        {
            firstHigh=enqueueHigh(firstHigh,currentName,currentCity,currentPoints);
        }
        
        firstTemp=enqueueTemp(firstTemp,currentName,currentCity,currentPoints);
        firstInit=dequeueInit(firstInit);
    }
    
    while(firstTemp!=nullptr)
    {
        currentName=firstTemp->teamName;
        currentCity=firstTemp->cityName;
        currentPoints=firstTemp->teamPoints;
        firstInit=enqueueInit(firstInit,currentName,currentCity,currentPoints);
        firstTemp=dequeueTemp(firstTemp);
    }

    cout<<"Leader:"<<leaderTeam<<" with "<<maxPoints<<" points"<<endl;
    cout<<"Outsider:"<<outsiderTeam<<" with "<<minPoints<<" points"<<endl;
    cout<<"---"<<endl;
    cout<<"Unique city queue:"<<endl;
    printQueue(firstUnique);
    cout<<"---"<<endl;
    cout<<"High points queue (>"<<thresholdPoints<<"):"<<endl;
    printQueue(firstHigh);
    cout<<"---"<<endl;
    cout<<"Restored initial queue:"<<endl;
    printQueue(firstInit);
    
    return 0;
}