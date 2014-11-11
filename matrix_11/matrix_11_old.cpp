// matrix_11.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <ctime>
#include <iostream>
#include <algorithm> 
using namespace std;
#include <omp.h>

int Length;// = 3;
int Heigh;// = 4;
int list_length;// = Length * Heigh;
//clock_t begin = clock();
clock_t begin;
bool global_prime_list[999999999];
int curent_max_primes = 0;



int check_for_pros(int N){
	//return 1;
    int candidate = 2;
    int ii = 0;
	//int square_cand= sqrt(N);
	while (candidate*candidate <= N){
        ii = ii + 1;
		if (N % candidate == 0){
			return 0;}
		else {
            candidate = ii * 2 + 1;
		}
	}
    return 1;
}

void print_array(int array_to_print[],int Length_of_array){
	for (int i=0; i<Length_of_array; i++){
		cout << array_to_print[i]<<",";
	}
	cout << "\n";
}

int prepare_primes(int limit){
	int i = 1;
	while (i*i <= limit){
		i= i+2;
		//cout << i << "\n";
		if (check_for_pros(i)){
		global_prime_list[i]= true;
		}

	}
//print_array(global_prime_list,limit);
return 0;
}




int append_simple_to_list(int int_for_test){

	return 0;
}

int prepare_and_check_simple(int int_for_test){
	//return (1);
	if (global_prime_list[int_for_test]){
            //append_simple_to_list(int_for_test);
			//cout << "return 1 for " << int_for_test;
			//cout << "global_prime_list[int_for_test] " << global_prime_list[int_for_test];
		return 1;}
return 0;
if (int_for_test > 10)//&(int_for_test < 10000))
{
	//return 1;
	if (global_prime_list[int_for_test]){
            //append_simple_to_list(int_for_test);
			//cout << "return 1 for " << int_for_test;
			//cout << "global_prime_list[int_for_test] " << global_prime_list[int_for_test];
            return 1;
	}
}
//return 0;
/*if (int_for_test > 10000){
		if ((last_digit==5) | (int_for_test%3==0)){
                return 0;
		}
		//cout << "return" << check_for_pros(int_for_test) << "for " << int_for_test<<"\n";
        return check_for_pros(int_for_test);
}
if (int_for_test < 10){
	if (int_for_test == 2){
        append_simple_to_list(int_for_test);
        return 1;
	}
	if (int_for_test == 3){
		append_simple_to_list(int_for_test);
		return 1;
	}
	if (int_for_test == 5){
        append_simple_to_list(int_for_test);
		return 1;
	if (int_for_test == 7){
            append_simple_to_list(int_for_test);
        return 1;
	}
}
}*/
return 0;}

int get_all_simple(int *list_to_work,int dont_check_1_digit, int len_of_list,int *list_of_primes_found,int next_pos){
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
			//primes_to_show_ret = k;
			if (number_for_test%2){
			test_succ = prepare_and_check_simple(number_for_test);
			//cout << "\n"<<"test_succ " <<test_succ << " primes till now "<<primes_to_show<<"\n";
			//if (test_succ){
				//list_of_primes_found[next_pos]=number_for_test;
				//next_pos = next_pos + 1;
			primes_to_show = primes_to_show + test_succ;
			//}
			};
		}
	}
//cout << primes_to_show;
return (primes_to_show);
}



int go_and_build_strings_shift (int list_to_parse[100],int shift_coming){
	//return 1;
	//cout << "we are building strings "<<shift_coming<<"\n";
	//print_array(list_to_parse,Heigh*Length+shift_coming);
	int simle_found = 0;
	int i;
	int j;

	int horisontal_list[10];
	int list_of_primes_found[100];
	for (i=0;i<Heigh;i++){     
		for (j=0;j<Length;j++){
            horisontal_list[j]=list_to_parse[i*Length+j+shift_coming];
		}
		simle_found= simle_found + get_all_simple(horisontal_list,0,j,list_of_primes_found,simle_found);
	}
        
//vertical
    int vertical_list[10];
    for (i=0;i<Length;i++){     
        for (j=0;j<Heigh;j++){
			vertical_list[j]=list_to_parse[j*Length+i+shift_coming];
		}
        simle_found= simle_found + get_all_simple(vertical_list,1,j,list_of_primes_found,simle_found);
	}
        
//down-right
    //del vertical_list[:]
    for (int co=0;co<Length-1;co++){  
        i = co;
        j = Heigh;
		int steps = 0;
		while ((j>0) & (i<Length)){
			vertical_list[steps]=list_to_parse[((j-1)*Length+i+shift_coming)];
			steps++;
            i = i + 1;
			j = j - 1;}
        simle_found= simle_found + get_all_simple(vertical_list,1,steps,list_of_primes_found,simle_found);
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
        simle_found= simle_found + get_all_simple(vertical_list,1,steps,list_of_primes_found,simle_found);
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
        simle_found= simle_found + get_all_simple(vertical_list,1,steps,list_of_primes_found,simle_found);
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
        simle_found= simle_found + get_all_simple(vertical_list,1,steps,list_of_primes_found,simle_found);
	}
	int new_simple_check = simle_found;
	//if (simle_found>34) {
	//	cout << "simle_found" <<simle_found<<"\n";}
	/*if (simle_found>curent_max_primes){
        curent_max_primes = simle_found;
		cout << "curent_max_primes" <<curent_max_primes<<"\n";
		print_array(list_to_parse,list_length);
		//print_array(list_of_primes_found,simle_found);
	}*/

		//if (shift_coming > 1)
		//{
		//	new_simple_check = go_and_build_strings_shift(list_to_parse,shift_coming-1);
		//}
		//if (simle_found>new_simple_check){ return simle_found;};
		//print_array(list_to_parse,list_length);
		//cout << "new_simple_check:"<<new_simple_check<<"\n";
//	cout << simle_found<<"\n";
return simle_found;		}


int shift_array(int *matrix_list){
	//print_array(matrix_list,list_length);
	//cout << "shift array started" ;
	//print_array(matrix_list,list_length);
	int temp_matrix[99]={};
	for (int i=0;i<2*list_length;i++){
			temp_matrix[i]= matrix_list[i%list_length];
	}
	//#pragma omp parallel for
	int simple_max = 0;
	for (int i=list_length;i>0;i--){
	int temp_list[200]={};	
			//print_array(matrix_list,list_length*2);
	int simple=go_and_build_strings_shift (temp_matrix, i);
	if (simple>simple_max){simple_max=simple;}
	}
	//cout <<simple_max<<"\n";
	return simple_max;
}

int combine_digits(int list_of_digits_rec[],int N_iteration,int *matrix_list, int &local_max,int shift){
//    #build_list_of_digits = [2, 2, 1, 1, 1, 1, 1, 1, 1, 1]
	//int list_of_digits_rec[20]={};
	//for (int i =0;i<20;i++){
	//list_of_digits_rec[i]=list_of_digits_rec2[i];
	//};
	//cout << "we come to build allowed list of digits, N_iteration =" << N_iteration<< "\n";
	//print_array(list_of_digits_rec, 10);
	//int dre;
	//cin >> dre;
	int ret_0; /// used for matrix shift optimization, so we can go out very fast
	if (N_iteration == 0){
		//cout << "we going now to read possible primes, N_iteration = " << N_iteration<< "\n";
		//go_and_build_strings_shift(matrix_list,0);
		int received_max=shift_array(matrix_list);
		//cout<<" recived max "<<received_max<<"current max "<<local_max<<"\n";
		if (received_max>local_max) {(local_max=received_max);
		print_array(matrix_list, list_length);
		cout<<" recived max "<<received_max<<"current max "<<local_max<<"\n";}
        return local_max;}
	else {
		int i = 1+shift;
		while (i < 10+shift){
			if (list_of_digits_rec[i]>0){
                matrix_list[list_length-N_iteration]= i-shift;
                list_of_digits_rec[i]--;
				//cout << i <<" i ";
                ret_0 = combine_digits (list_of_digits_rec,N_iteration - 1,matrix_list,local_max,shift);
				//cout << "we are back from recursion" << N_iteration<<"\n";
				list_of_digits_rec[i]++;
				if (ret_0==0){return 0;}
			}
			if (N_iteration==list_length){
					//int dela;
					//print_array(list_of_digits_rec, 10);
					//print_array(matrix_list, list_length);
					//cin >> dela;
					//print_array(matrix_list,11);
					return 0;}
			i = i + 1;
		}
		}
	//cout << local_max<<"\n";
	return (local_max);
}
        
int shift_digits_allowed (int *digits_to_use){
//int temp_list[20]={};
	for (int i=10;i<19;i++){
			digits_to_use[i]= digits_to_use[i-9];
			//print_array(digits_to_use,19);
	}
	print_array(digits_to_use,19);
	//#pragma omp parallel for
	for (int i=9;i>0;i--){
	int matrix_list[200];// max is 100 digits x 2 for shift
	int digit_use_tmp[10]={};
	for (int j=1;j<10;j++){
		digit_use_tmp[j]=digits_to_use[j+i];	
	}
	int local_max=1;
	int local_matrix_max = combine_digits(digit_use_tmp, list_length, matrix_list,local_max,0);
	
	}
	return 1;
}


int prepare_N_digits(int *max_and_min_digits_allowed, int N__digit_iteration, int *digits_to_use){
// function receive's array max_and_min_digits_allowed {0, 6, 3, 0, 0, 0, 0, 0, 0, 0}
// which shows that 6 digits will be used 1 time (6 in position 1) and 3 digit will
// be repeated 2 times (3 in position 2).
// using recursion, function will build all possible combination when 6 digit included 
// once and 3 digit included 2 times.
// first array to build will be matrix_list[10] = [0,2,2,2,1,1,1,1,1,1]
// [0,2,2,2,1,1,1,1,1,1]  means -->>> 
// digit 0 is used 0 times ( 0 on position 0), 
// digit 1 is used 2 times ( 2 on position 1), 
// digit 2 is used 2 times ( 2 on position 2), 
// digit 3 is used 2 times ( 2 on position 3), 
// digit 4 is used 1 times ( 1 on position 4), , etc......
// array matrix_list[10] will be sent to function combine_digits in order to build a matrix
	//cout << "we come to N digit";	
	//print_array(max_and_min_digits_allowed, 10);
	int retH_0 = 0;
    if (N__digit_iteration == 0) 
	{
		int matrix_list[200];// max is 100 digits x 2 for shift
        cout << "we have ready list for matrix\n";
		print_array(max_and_min_digits_allowed, 10);
		print_array(digits_to_use, 10);
		int local_max=1;
		//shift_digits_allowed(digits_to_use);
        local_max = combine_digits(digits_to_use, list_length, matrix_list,local_max,0);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "time consumed:"<<elapsed_secs<<"\n";
		cout << local_max<<" local prime MAX "<<local_max<<"\n";
		//cout << elapsed_secs<<" locL MAX "<<local_matrix_max<<"\n";
		//int dela;
		//cin >> dela;
        return 0;
	}
    else{
        int i = 1;
        while (i < 10) 
		{
            if (max_and_min_digits_allowed[i]>0)
			{
                digits_to_use[N__digit_iteration] = i;
                max_and_min_digits_allowed[i] --;
                retH_0=prepare_N_digits (max_and_min_digits_allowed,N__digit_iteration - 1,digits_to_use);
				max_and_min_digits_allowed[i] ++;
				//if (retH_0==-1){return -1;}
			}
			//if (N__digit_iteration==9){
			//		int dela;
			//		return -1;}
			i ++;
		}
		return 0;
        }
}

int prepare_N_digits_mod(int *max_and_min_digits_allowed, int N__digit_iteration, int *digits_to_use){
int i = 1;
int j = 0;
int matrix_list[10];
while (i<10){
	while (j<10){
		if(max_and_min_digits_allowed[j]>0){
		
		matrix_list[i]=j;
		max_and_min_digits_allowed[j]--;
		i++;
		print_array(matrix_list, 12);
		print_array(max_and_min_digits_allowed, 9);
		cout<<"i "<<i<<" j "<<j<<"\n";
		} else {
			j++;
		}
	}

}


print_array(matrix_list, 12);

cout <<"we are out of cycle";
print_array(max_and_min_digits_allowed, 9);
print_array(matrix_list, 12);
		int local_max[4]={1,1,1,1};
		int final_max=1;
		std::cout << "The 3! possible permutations with 3 elements:\n";
		//for(int jjj=0;jjj<10;jjj++){
		//std::next_permutation(matrix_list+1,matrix_list+10);
		//print_array(matrix_list,10);}

	do {
		print_array(matrix_list, 10);
		int matrix_list1[16][100]={};
		int matrix_list_copy[16][100]={};
		for(int jjj=0;jjj<10;jjj++){matrix_list_copy[0][jjj]=matrix_list[jjj];}
		print_array(matrix_list_copy[0],10);
		std::next_permutation(matrix_list+1,matrix_list+10);
		for(int jjj=0;jjj<10;jjj++){matrix_list_copy[1][jjj]=matrix_list[jjj];}
		print_array(matrix_list_copy[1],10);
		std::next_permutation(matrix_list+1,matrix_list+10);
		for(int jjj=0;jjj<10;jjj++){matrix_list_copy[2][jjj]=matrix_list[jjj];}
		print_array(matrix_list_copy[2],10);
		std::next_permutation(matrix_list+1,matrix_list+10);
		for(int jjj=0;jjj<10;jjj++){matrix_list_copy[3][jjj]=matrix_list[jjj];}
		print_array(matrix_list_copy[3],10);
		//std::next_permutation(matrix_list+1,matrix_list+10);

		#pragma omp parallel for
		for (int nn=0;nn<4;nn++){
		combine_digits(matrix_list_copy[nn], list_length, matrix_list1[nn],local_max[nn],0);
		};
		for (int nn=0;nn<4;nn++){
			if (local_max[nn]>final_max) {final_max=local_max[nn];}
			else {local_max[nn]=final_max;};
		}
		print_array(local_max,4);
		//if (local_max[0]>final_max) {final_max=local_max[0];
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "time consumed:"<<elapsed_secs<<"\n";
		cout << local_max<<" local final_max "<<final_max<<"\n";
	} while ( std::next_permutation(matrix_list+1,matrix_list+10) );

		//cout << elapsed_secs<<" locL MAX "<<local_matrix_max<<"\n";
		//int dela;
		//cin >> dela;*/
		return final_max;
}


int prepare_digit_allowed(int *max_and_min_digits_allowed){
//int list_length=12;
int min_digit_use = int((list_length-list_length%9)/9);
int max_digit_use = min_digit_use+1;
int number_of_max = int(list_length-min_digit_use*9);
int number_of_min = int((list_length-number_of_max*max_digit_use));
//cout <<"min_digit_use:"<< min_digit_use<<"  max_digit_use:"<<max_digit_use  << " number_of_max:" << number_of_max<<"\n";
//cout <<"number_of_min:"<< number_of_min<<"\n";//11223344556789//
for (int i = 0;i<10;i++){
	max_and_min_digits_allowed[i]=0;}
max_and_min_digits_allowed[min_digit_use]=number_of_min;
max_and_min_digits_allowed[max_digit_use]=number_of_max;
print_array(max_and_min_digits_allowed,9);

return 0;

}

int main (){

//----------------------- initiate data ------------------------
	cout <<"Please enter length M:";
		cin >> Length;
	cout << "Please enter heigh N:";
		cin >> Heigh;
begin = clock();
	list_length = Length * Heigh;

//int test_list[12] = {0,0,1,1,2,3,4,5,6,7,8,9};
int allowed_digits_to_use [20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
// list_of_binar_rec_glob will be converted into [0,2,2,2,1,1,1,1,1,1]
int max_and_min_digits_allowed [10]= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//6 digits 1 time and 3 digit 3 times
// list_of_binar_rec_glob will be coverted into [0,2,2,2,1,1,1,1,1,1] for 3x4 matrix
prepare_digit_allowed(max_and_min_digits_allowed);
prepare_primes(10000);
clock_t begin = clock();
//-----------------------end of data initiation ----------------

//--------------------------go and build matrix----------------- 
//cout << " matrix is ready ";
omp_set_num_threads(4);
	printf("Starting Program!\n");

	#pragma omp parallel
	{
		// This statement will run on each thread.
		// If there are 4 threads, this will execute 4 times in total
		printf("Running on multiple threads\n");
	}
	


int a = prepare_N_digits_mod(max_and_min_digits_allowed,9,allowed_digits_to_use);


//--------------time consumed----------
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//--------------------------------------
//-------------- end -------------------
cout << elapsed_secs << " enter something to finish :\n";
int amba;
cin >> amba;
return 0;
}

