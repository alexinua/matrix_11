// matrix_11.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <math.h>
#include "list_max.h"
#include <algorithm> 
using namespace std;
#include <omp.h>
const int Max_Proc = 64; // MAX number of processor expected is 64
int Length;// = 3;
int Heigh;// = 4;
int list_length;// = Length * Heigh;
clock_t begin;
bool global_prime_list[9999999999];//global array with TRUE values for primes positions
int curent_max_primes = 0;



int check_for_pros(int N){
	//function check if N is prime by deviding N by int candidate till N>candidate^2
	//return 1 if prime is confirmed
	//return 0 if prime is not confirmed
    int candidate = 2;
    int ii = 0;
	while (candidate*candidate <= N){
        ii = ii + 1;
		if (N % candidate == 0)
		{
			return 0;} // 0 - prime is not confirmed
		else 
		{
            candidate = ii * 2 + 1;
		}
	}
    return 1; // 1 - prime is confirmed
}

void print_array(int array_to_print[],int Length_of_array)
{
	//function is used to print array (int array_to_print) with length (int Length_of_array)
	for (int i=0; i<Length_of_array; i++)
	{
		cout << array_to_print[i]<<",";
	}
	cout << "\n";
}

int prepare_primes(int limit)
{
	//function prepare primes till value (int limit) and insert for them value TRUE into global array (bool global_prime_list)
	int i = 1;
	global_prime_list[2]= true;
	while (i <= limit)
	{
		i= i+2;
		//cout << i << "\n";
		if (check_for_pros(i))
		{
			global_prime_list[i]= true;
		}
	}
	cout<<"primes are ready till  "<<limit<<"\n";
	//print_array(global_prime_list,limit);
	return 0;
}

int check_combination_for_simple(int int_for_test)
{
	//function is uded to check combination of digits from matrix if it is prime
	//return 1 in case (int int_for_test) is included in global array of primes (bool global_prime_list[])
	//return 0 in case (int int_for_test) is NOT included in global array of primes (bool global_prime_list[])
	//used for speed because direct check inside (int get_all_simple()) slowdown programm
	if (global_prime_list[int_for_test])
	{
		return 1;
	}
	return 0;
}


int get_all_simple(int *list_to_work,int dont_check_1_digit, int len_of_list)
{
	/*function is making all possible combination from received string (int *list_to_work) 
	and count how many primes were found. For string [1,2,3] all possible combination will be 123,12,23,1,2,3
	(int dont_check_1_digit) is used in order to do not repeat cheking digit with lenth of 1 only
	(int len_of_list) is showing the length of received array (int *list_to_work)
	function returns number of found primes in received string (int primes_to_show)*/
	//print_array(list_to_work,len_of_list);//check what we have received
	int primes_to_show = 0;
	for(int i= 0; i<len_of_list; i++)
	{
		for (int j=1;j<len_of_list-i+1-dont_check_1_digit;j++)// j is lenth of number_for_test
		{
            int number_for_test=0;
			int k;//position of digit which will be added to number_for_test
			for (k=i;k<len_of_list-j+1;k++)
			{
				number_for_test = number_for_test*10 + list_to_work[k];//building value to test
			}
			primes_to_show = primes_to_show + check_combination_for_simple(number_for_test);
		}
	}
//cout << "primes_to_show \n"<<primes_to_show;
return (primes_to_show);
}


int get_all_simple_print(int *list_to_work,int dont_check_1_digit, int len_of_list,int *list_of_primes_found,int next_pos)
{
	//function is doing same as get_all_simple() but printing found primes for final result
	//print_array(list_to_work,len_of_list);
	int primes_to_show = 0;
	int test_succ = 0;
	for(int i= 0; i<len_of_list; i++){
		//int limit = len_of_list-i+1-dont_check_1_digit;
		for (int j=1;j<len_of_list-i+1-dont_check_1_digit;j++){
            int number_for_test=0;
			int k;
			for (k=i;k<len_of_list-j+1;k++){
            number_for_test = number_for_test*10 + list_to_work[k];
			}
			test_succ = check_combination_for_simple(number_for_test);
			if (test_succ){
				cout <<number_for_test<< ", " ;}
			primes_to_show = primes_to_show + test_succ;
		}
	}
//cout << "\n"<<primes_to_show;
return (primes_to_show);
}

int odd_check(int last_digit)
{
	//function is used to exclude last digit from string before searching primes inside in case last digit is even
	//for string [1,2,3,4] , 4 will be not included into any of combination because all possible cases with it 1234,234,34,4
	// are not primes. 
	// function return 0 for odd digits which means that last digit shoud be included
	// function return 1 for even digits which means that last digit shoud NOT be included
	if (last_digit==1) return 0;
	if (last_digit==3) return 0;
	if (last_digit==7) return 0;
	if (last_digit==9) return 0;
	return 1;
}

int go_and_build_strings_shift (int list_to_parse[100],int shift_coming)
{
	//function is going through received matrix (int list_to_parse[100])from left to right, up-to-down, etc. and 
	//building possible strings,strings are send to find primes inside and finally number of total found primes are returned
	//function returns total number of primes inside matrix (int simle_found).
	//(int shift_coming) is not used, was used in previous version for recursion
	// cout << "we are building strings "<<shift_coming<<"\n";//test
	// print_array(list_to_parse,Heigh*Length+shift_coming);
	// int list_to_parse [12]= {2, 4, 6, 7, 8, 3, 1, 1, 5, 3, 7, 9};
	shift_coming=0; // not used in this revision
	int simle_found = 0;// total number of simple found
	int i;
	int j;

	if (odd_check(list_to_parse[list_length-1])) 
	{
		//print_array(list_to_parse,Heigh*Length+shift_coming);
		return (-1);//right down corner is  even or 5
	};
//horisontal search
	int horisontal_list[10]; // temp array for build string from matrix
	for (i=0;i<Heigh;i++)
	{     
		for (j=0;j<Length;j++)
		{
            horisontal_list[j]=list_to_parse[i*Length+j+shift_coming];
		}
			simle_found= simle_found + get_all_simple(horisontal_list,0,j);
	}        
//vertical search
    int vertical_list[10];
    for (i=0;i<Length;i++)
	{     
        for (j=0;j<Heigh;j++)
		{
			vertical_list[j]=list_to_parse[j*Length+i+shift_coming];
		}
        simle_found= simle_found + get_all_simple(vertical_list,1,j-odd_check(vertical_list[j]));
	}        
//down-right search
    for (int co=0;co<Length-1;co++)
	{  
        i = co;
        j = Heigh;
		int steps = 0;
		while ((j>0) & (i<Length))
		{
			vertical_list[steps]=list_to_parse[((j-1)*Length+i+shift_coming)];
			steps++;
            i = i + 1;
			j = j - 1;
		}
		simle_found= simle_found + get_all_simple(vertical_list,1,steps-odd_check(vertical_list[steps]));
	}
//up-right search
	int steps; // count what is the lenth of string from array
    for (int co=0;co<Length-1;co++) //co is just an index for because i and j already used
	{
        i = co;
        j = 0;
		steps = 0;
		while ((j<Heigh) & (i<Length) )
		{
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j + 1;
		}
        simle_found= simle_found + get_all_simple(vertical_list,1,steps-odd_check(vertical_list[steps]));
	}
//left-down search
	for (int co=1;co<Heigh-1;co++)
	{
        i = 0;
        j = co;
		steps = 0;
		while ((j<Heigh )&( i<Length)) 
		{
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j + 1;
		}
		simle_found= simle_found + get_all_simple(vertical_list,1,steps-odd_check(vertical_list[steps]));
	}
//left-up search
	int co; //just index because i and j already used
	for (co = 1;co < Heigh-1;co++)
	{
        i = 0;
        j = co;
		steps=0;
		while ((j>=0)&( i<Length)) 
		{
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j - 1;
		}
		simle_found= simle_found + get_all_simple(vertical_list,1,steps-odd_check(vertical_list[steps]));
	}
	return simle_found;//return number of primes found inside matrix
}


int go_and_build_strings_print (int list_to_parse[100],int shift_coming){
	//function is doing same as function go_and_build_strings_shift() but calling get_all_simple_print() for printing primes 
	// for final answer
	cout<<"Simple found in this case: ";
	int simle_found = 0;
	int i;
	int j;
//horisontal
	int horisontal_list[10];
	int list_of_primes_found[100];
	for (i=0;i<Heigh;i++){     
		for (j=0;j<Length;j++){
            horisontal_list[j]=list_to_parse[i*Length+j+shift_coming];
		}
		simle_found= simle_found + get_all_simple_print(horisontal_list,0,j,list_of_primes_found,simle_found);
	}        
//vertical
    int vertical_list[10];
    for (i=0;i<Length;i++){     
        for (j=0;j<Heigh;j++){
			vertical_list[j]=list_to_parse[j*Length+i+shift_coming];
		}
        simle_found= simle_found + get_all_simple_print(vertical_list,1,j,list_of_primes_found,simle_found);
	}        
//down-right
    //del vertical_list[:]
    for (int co=0;co<Length-1;co++)
	{  
        i = co;
        j = Heigh;
		int steps = 0;
		while ((j>0) & (i<Length))
		{
			vertical_list[steps]=list_to_parse[((j-1)*Length+i+shift_coming)];
			steps++;
            i = i + 1;
			j = j - 1;
		}
        simle_found= simle_found + get_all_simple_print(vertical_list,1,steps,list_of_primes_found,simle_found);
	}
	int steps;
    for (int co=0;co<Length-1;co++){
        i = co;
        j = 0;
		steps = 0;
		while ((j<Heigh) & (i<Length) ){
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j + 1;
		}
        simle_found= simle_found + get_all_simple_print(vertical_list,1,steps,list_of_primes_found,simle_found);
	}
//left-down
	for (int co=1;co<Heigh-1;co++){
        i = 0;
        j = co;
		steps = 0;
		while ((j<Heigh )&( i<Length)) {
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j + 1;
		}
        simle_found= simle_found + get_all_simple_print(vertical_list,1,steps,list_of_primes_found,simle_found);
	}
//left-up
//	int ant;
	int co;
	for (co = 1;co < Heigh-1;co++){
        i = 0;
        j = co;
		steps=0;
		while ((j>=0)&( i<Length)) {
			vertical_list[steps]=list_to_parse[(j*Length+i+shift_coming)];
			steps++;
            i = i + 1;
            j = j - 1;
		}
        simle_found= simle_found + get_all_simple_print(vertical_list,1,steps,list_of_primes_found,simle_found);
	}
	cout<<"\n";
	return simle_found;		
}

void print_list(List_max *list_for_print)
{	
	// test function was used to check corectness of stored list
	// prints values for 1 object (List_max *list_for_print) including stored matrix and adresses of next and prev lists
	cout<<"we are inside print list\n";
	//list_for_print->printList_max();
	List_max* current_list =list_for_print->head;
	//current_list->printList_max();
	do {
		cout<<"max_stored"<<current_list->max_stored<<"\n";
		for (int j=0;j<current_list->list_length;j++)
		{
			cout<<current_list->saved_matrix[j];
		}
		cout<<"\n";
		if (current_list->next>NULL)
		{
			current_list=current_list->next;
		}
	} while(current_list->next>NULL);
} 

void print_results(List_max *list_for_print)
{
	//function prints all matrix with max number of primes found
	//all saved matrix are stored in objects which are connected into dynamic list (List_max *list_for_print) Each object keeps 
	// matrix, pointer to object with next stored matrix, pointer to previous matrix and pointer to head of list
	List_max* current_list =list_for_print->head;
	int i = 0;
	do //go through list and count how many total matrix are stored
	{
		i++;
		current_list=current_list->next;
	} while(current_list->next>NULL);
	current_list =list_for_print->head;
	do // printing stored matrix and primes for them
	{
		cout<<"Max of found primes is: "<<current_list->max_stored<<"\n";//confirm max number of primes are stored correctly
		for (int j=0;j<current_list->list_length;j++)
		{
			cout<<current_list->saved_matrix[j];
			if ((j+1)%Length==0){cout <<"\n";};
		}
		go_and_build_strings_print (current_list->saved_matrix,0);//searching and printing primes here for final print
		cout<<"\n";
		if (current_list->next>NULL)
		{
			current_list=current_list->next;
		}
	} while(current_list->next>NULL);

}


int combine_digits2(int list_of_digits_rec[],int local_max1, List_max *saved_lists)
{	
	//function is receiving matrix as string like 1234 and doing iteration till it gets 4321, 
	//so all possible combination will be checked
	//for each combination all primces will be found and max of primes will be returned
	//cout <<"we are inside 2"<<"\n";
	//print_array(list_of_digits_rec, 10);
	int local_max=local_max1;
	int i = 0;
	int j = 1;
	int matrix_list1[100]; // this is a copy of matrix which will be used for modification 
	int dela;//test variable
	while (i<list_length)
	{
		while (j<10)
		{
			if(list_of_digits_rec[j]>0)
			{
				matrix_list1[i]=j;
				list_of_digits_rec[j]--;
				i++;
			} 
			else 
			{
				j++;
			}
		}
	}
	dela=matrix_list1[1];//test variable
	int max_val;
	int changes_to_max_happened=0;//will track if new max number of primes was found
	do {
		//dela++;//tests
		//if (dela%288159000==0){print_array(matrix_list1, list_length);cout <<local_max<<"\n";};//tests
		//if (dela>288159){print_array(matrix_list1, list_length);cin >> dela;};//tests
		//if (matrix_list1[0]>dela){print_array(matrix_list1, list_length);dela=matrix_list1[0];};//tests
		//if (matrix_list1[0]=2){print_array(matrix_list1, list_length);};//tests
		int received_max=go_and_build_strings_shift(matrix_list1, 0); // go and found all primes for matrix matrix_list1
		if (received_max==local_max)// same max of primes was found, matix needs to be stored into object (List_max* saved_lists)
		{	
			local_max=received_max;
			saved_lists->add_matrix(matrix_list1,local_max,0);
			List_max* new_list = new List_max(list_length);
			saved_lists->next = new_list;
			new_list->prev = saved_lists;
			new_list->head=saved_lists->head;
			saved_lists=new_list;
			changes_to_max_happened=1;
		}
		if (received_max>local_max) //new max of primes was found, matix needs to be stored inside object (List_max* saved_lists)
		{
			//cout<<" recived > max "<<received_max<<"current max "<<local_max<<"\n";//test
			//print_array(matrix_list1, list_length);//test
			//cout<<"max dela="<<dela<<"\n";//test
			//saved_lists->printList_max();//test
			local_max=received_max;
			changes_to_max_happened=1;
			saved_lists=saved_lists->head;
			saved_lists->add_matrix(matrix_list1,local_max,0);
			List_max* new_list = new List_max(list_length);
			saved_lists->next = new_list;
			new_list->prev=saved_lists;
			new_list->head=saved_lists->head;
			saved_lists=new_list;	
		}
	} while (std::next_permutation(matrix_list1,matrix_list1+list_length));
	if (changes_to_max_happened==0) {local_max=0;};
	return local_max;
}


int prepare_N_digits_mod(int *max_and_min_digits_allowed, int N__digit_iteration, int *digits_to_use)
{
	//function will build number of matrix ecual to used processor and then each processor will start 
	// making for all possible combination and check number of primes
	int i = 9;
	int j = 9;
	int matrix_list[10];
	while ((i>1)&&i>(10-list_length)){
		while (j>0)
		{
			if(max_and_min_digits_allowed[j]>0)
			{
				matrix_list[i]=j;
				max_and_min_digits_allowed[j]--;
				i--;
			} else 
			{
				j--;
			}
		}
	}
	int max_thred=omp_get_max_threads();
	int local_max[Max_Proc]={};
	int final_max=1;
	List_max* max_lists = new List_max(list_length);
	max_lists->head=max_lists;
	bool next_shift_possible;
	do { //create severa matrix based on number of processors
		int matrix_list1[Max_Proc][100]={};
		int matrix_list_copy[Max_Proc][100]={};
		int iii=0;//just an index
		do {
			//cout<<"inside do max_thred:"<<max_thred<<"\n";
			for(int jjj=0;jjj<10;jjj++)
			{
				matrix_list_copy[iii][jjj]=matrix_list[jjj];
			}
			next_shift_possible=std::next_permutation(matrix_list+1,matrix_list+10);
			iii++;
		} while ((next_shift_possible)&&(iii<max_thred));
		int nn=0;//just an index for making parralel calculation inside for loop
		//print_array(matrix_list_copy[nn],10);
		List_max* saved_lists [Max_Proc];
		#pragma omp parallel for
		for (nn=0;nn<iii;nn++)
		{
			print_array(matrix_list_copy[nn],10);
			saved_lists[nn] = new List_max(list_length);//list to save matrix with max primes
			saved_lists[nn]->head=saved_lists[nn];
			local_max[nn]=combine_digits2(matrix_list_copy[nn],local_max[nn],saved_lists[nn]); //max of primes come back here
		};
		int max_index=-1;//check if number of new max primes was found 
		for (int nn=0;nn<iii;nn++)
		{
			if (local_max[nn]>final_max) 
			{	
				final_max=local_max[nn];
				max_index=nn;
			};
		}

		if (max_index>=0)// max primes is bigger than current max of primes, no clean for previous stored lists
		{
			max_lists=max_lists->head;
			max_lists->next=NULL;
		}
		for (int nn=0;nn<iii;nn++){
			if (local_max[nn]==final_max) 
			{
				//add will be here
				//cout << "local_max[nn]==final_max happened\n";
				//cout<<"local_max["<<nn<<"]:"<<local_max[nn]<<"final_max:"<<final_max<<"\n";
				//cout<<"\n";
				do 
				{
					//cout<<"max_lists list\n";max_lists->printList_max();
					//cout<<"current list\n"; saved_lists[nn]->printList_max();
					max_lists->copy_1_List_max(saved_lists[nn]);
					List_max* new_list_tmp = new List_max(list_length);
					max_lists->next = new_list_tmp;
					new_list_tmp->prev = max_lists;
					new_list_tmp->head=max_lists->head;
					//cout<<"updated max list\n";max_lists->printList_max();
					max_lists=new_list_tmp;
					//cout<<"new max list\n";max_lists->printList_max();
					if (saved_lists[nn]->next>NULL)
					{
						saved_lists[nn]=saved_lists[nn]->next;
					}
				} while(saved_lists[nn]->next>NULL);				
			}
			else {local_max[nn]=final_max;};
		}
	clock_t end = clock();//show progress
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;//show progress
	cout << "time consumed:"<<elapsed_secs<<"\n";//show progress
	} while (next_shift_possible);

//-----------------------------------------------------------------FINAL RESULT PRINTS HERE-----------------
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "time consumed:"<<elapsed_secs<<"\n";
	cout << "we have finished calculation\n"; 
	print_results(max_lists);
	//print_list(max_lists);
	return final_max;
}


int prepare_digit_allowed(int *max_and_min_digits_allowed)
{
	//function is checking how many digits are allowed min and max for matrix list and sill them
	// for matrix 3x4 12 digits are allowed, so it will 6 digits used 1 time and 3 digit used 2 times
	// array will be created [0,6,3,0,0,...] which shows that 1 digit used 6 times and 2 digits used 3 times
	//later this array will be converted into matrix  [1,2,3,4,5,6,7,7,8,8,9,9] which has 6 digits uniqe and 3 digits repeaed
	int min_digit_use = int((list_length-list_length%9)/9);
	int max_digit_use = min_digit_use+1;
	//cout <<"min_digit_use:"<< min_digit_use<<"  max_digit_use:"<<max_digit_use <<"\n";
	//cout <<"number_of_min:"<< number_of_min<<"\n";//11223344556789//
	int number_of_max;
	int number_of_min;
	if (list_length<9)
	{
		number_of_max=list_length;
		number_of_min=0;
	}
	else
	{
		number_of_max = int(list_length-min_digit_use*9);
		number_of_min = int((list_length-number_of_max*max_digit_use)/min_digit_use);
	}
	for (int i = 0;i<10;i++)
	{
		max_and_min_digits_allowed[i]=0;
	}
	max_and_min_digits_allowed[min_digit_use]=number_of_min;
	max_and_min_digits_allowed[max_digit_use]=number_of_max;
	//print_array(max_and_min_digits_allowed,9);
return 0;
}

//----------------------------------------------------------main is here --------------------
int main (){

//----------------------- INITIATE DATA--------------------------------------- ------------------------
	do{
		cout <<"Please enter length M less then 11:";
		cin >> Length;
	} while (Length>10&&Length<1);
	do{
		cout << "Please enter heigh N:";
		cin >> Heigh;
	} while (Heigh>10&&Heigh<1);
//-----------------------------------------start clock--------------------------------------------------
begin = clock();
list_length = Length * Heigh;
clock_t begin = clock();

//-----------------------------------------initiate arrays with allowed digits to keep conditions-------
int allowed_digits_to_use [20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};// 10 digits from 0 to 9
int max_and_min_digits_allowed [10]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//will be coverted into [0,1,1,1,1,1,1,2,2,2] for 3x4 matrix
prepare_digit_allowed(max_and_min_digits_allowed);
//-----------------------------------------initiate primes ---------------------------------------------
if (Length>Heigh)
{
	prepare_primes((int)pow((float)10,Length));
}
else {
	prepare_primes((int)pow((float)10,Heigh));
}
//---------------------------------END OF DATA INITIATION ----------------

//--------------------------GO PREPARE DIGITS AND MAKE ALL COMBINATION----------------- 
prepare_N_digits_mod(max_and_min_digits_allowed,9,allowed_digits_to_use);
//----------------------------------------- end -------------------
cout << "Enter something to finish :\n";
int amba;
cin >> amba;
return 0;
}

