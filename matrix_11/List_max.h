#pragma once
#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <algorithm>
using namespace std;

class List_max
{ 
public:
	int max_stored;
	int list_length;
	int saved_matrix[100];
	List_max* head;
	List_max* next;
	List_max* prev;
	
	List_max(int list_length);


void add_matrix(int *matrix, int max_received,int printAllow)
{	
	max_stored = max_received;
	if(printAllow)
	{
		cout<<"saving martix: "<<list_length<<"\n";
	}
	for (int i=0;i<list_length;i++)
	{
		saved_matrix[i]=matrix[i];
		if(printAllow)
		{
			cout<<saved_matrix[i]<<",";
		}
		
	}
} 

void copy_1_List_max(List_max* source)
{	
	max_stored=source->max_stored;
	list_length=source->list_length;
	for(int i=0;i<list_length;i++)
	{
		saved_matrix[i]=source->saved_matrix[i];
	}
}


void printList_max()
{	
 	cout<<"head address: "<<head<<" next: "<<next<<" prev address: "<<prev;
	cout<<"max_stored: "<<max_stored<<"\n";
	for (int i=0;i<list_length;i++)
	{
		cout<<saved_matrix[i]<<",";
	}
	cout<<"\n";
} 



public:
	~List_max(void);
};
