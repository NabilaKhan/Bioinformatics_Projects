//*******************************************************************************
/*
File: Gotoh's Algorithm on O(N) space
Author: Nabila Shahnaz Khan
Source: Research Paper, title -> "Optimal alignments in linear space", algorithm in Figure 3
Date: 9/4/19
Purpose: Calculates the minimum conversion cost and finds out the optimum conversion approach for converting string A to string B
Input: File: string1.txt, string2.txt
Output:
(1)Displays the maximum string length the program can handle
(2)Displays the input string A and B
(3)Displays steps of optimal solution for converting A to B
(4)Displays inter array "S" which keeps track of how many replace, insert and delete operations have been performed
    and in which sequence
(5)Prints alignment sequence for the optimum conversion method of A to B
(6)Calculates and prints optimum cost for conversion of A to B
*/
//*******************************************************************************

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<float.h>
#include<string>
#include <cmath>
#include <fstream>
using namespace std;

#define NMAX 999999 //Possible maximum length of input string, if input string's length exceeds "NMAX" then function DIFF will return -1.0
const double g=2;
const double h=0.5; // g and h are positive constants that are used to calculate gap(k) affine function where gap(k) = g + hk;
int Delete = 0, Insert = 0, Match = 0, Replace = 0;

int Array_index=0; //used for calculation of integer array "S"
int S[NMAX];

//Function Prototypes
double gap(int k);
double w(char a, char b);
void print_array(int L, double Arr[]);
double DIFF(string A, string B, int M, int N);
void diff(string A, string B, int M, int N, double tb, double te);
void DISPLAY(string A, string B, int M, int N);


int main(int argc, char **argv)
{
    if(argc < 3) {
        cout << "Please provide the filepaths of the two files you wish to compare" << endl;
        return 2;
    }
    
    //cout<<"Maximum Possible String Length: "<<NMAX<<endl<<endl;
    string A, B, line;

    //Taking string input from text files 'string1.txt' and 'string2.txt'
    ifstream fin1,fin2;
    fin1.open(argv[1]);
    fin2.open(argv[2]);

    if (fin1.is_open())
    {
        while (getline (fin1,line) )
        {
            A = A + line;
        }

        fin1.close();
    }
    if (fin2.is_open())
    {
        while (getline (fin2,line) )
        {
            B = B + line;
        }

        fin2.close();
    }

    int M, N, max_length;
    M=A.length(); // M is length of 1st string
    N=B.length(); // N is length of 2nd string

    //max_length=max(M,N);


    double optimum_cost=DIFF(A,B,M,N);
    cout<<"Insert: "<<Insert<<endl;
    cout<<"Delete: "<<Delete<<endl;
    cout<<"Match: "<<Match<<endl;
    cout<<"Replace: "<<Replace<<endl;
    cout<<"Minimum cost "<<optimum_cost<<endl; //prints the minimum conversion cost

    double identity = ((Match)/double(Match+Replace+Insert+Delete))*100;
    cout<<"Percent Sequence identity "<<identity<<endl;
    return 0;
}

//affine function. gap(k) = g + hk; Here, g and h are positive constants
double gap(int k){
    if(k>0)
        return g + h * k;
    return 0;
}

double w(char a, char b){
    if(a==b)
        return 0;
    return 1;

}

//"print_array" function print a double array. Here L is the array length
void print_array(int L, double Arr[]){

    for(int i=0;i<=L;i++){
        printf("%.1lf ",Arr[i]);
    }
    printf("\n");
}

/*"DIFF" function compares sequence A[1....M] with sequence B[1.....N] and returns minimum conversion cost. If input string length greater than "NMAX"
then it returns -1.0
 Here,  if match, cost = w(a,a) = 0
        if replace, cost = w(a,b) = 1
        if insert/ delete (indel), cost= gap(k) = g + h*k; opening up a gap costs g and each symbol in gap costs h
*/
double DIFF(string A, string B, int M, int N){

    if(M>NMAX || N>NMAX) return -1;  // check if the input string length is greater than "NMAX"

    cout<<endl<<"Optimal solution for converting A to B ->"<<endl<<endl;
    diff(A,B,M,N,g,g); //see the function for explanation


/* "Array" keeps track of replacement, insertion or deletion operation. If a[i] is replaced by b[j] then "Array" holds "0",
if k symbols are deleted then "+k" is inserted into "Array" and if k symbols are deleted then "-k" is inserted into "Array".
Here,
0 => replace
-k => delete k symbols
+k => insert k symbols

"Array_index" keeps track of the current size of "Array"

"Array" must have the following properties:
1) Inserts are never followed by inserts
2) Deletes are never followed by deletes or inserts
So, all the consecutive negative values have been summed, kept to one index and the array has been left-shifted. Similarly, all the consecutive
positive values have been summed, kept to one index and the array has been left-shifted.
*/
    for(int i=1;i<Array_index;i++){
        if(S[i-1]<0 && S[i]<0){
            S[i-1]=S[i-1]+S[i];
            for(int j=i+1;j<=Array_index;j++){
                S[j-1]=S[j];
            }
            Array_index--;
            i--;
        }
        else if(S[i-1]>0 && S[i]>0){
            S[i-1]=S[i-1]+S[i];
            for(int j=i+1;j<=Array_index;j++){
                S[j-1]=S[j];
            }
            Array_index--;
            i--;
        }
    }


 /*   cout<<endl<<"Integer Array S: "<<endl;
    for(int i=0;i<Array_index;i++){
        cout<<S[i]<<"  ";
    }
    cout<<endl<<endl<<"Here,"<<endl<<"0 => replace"<<endl<<"-k => delete k symbols"<<endl<<"+k => insert k symbols"<<endl;*/

    /* Calculates the optimum conversion cost using the "S" array. "S" array keeps track of how many replace, insert and delete operations have been performed
    and in which sequence*/
    double optimum_cost=0;
    for(int i=0,a=0,b=0;i<Array_index;i++){
        if(S[i]==0){
            if(A[a]!=B[b])
            optimum_cost=optimum_cost+1;

        a++;
        b++;
        }
        else{
            //double gap=2;

            int indel=abs(S[i]);
            if(S[i]>0) b=b+indel;
            else a=a+indel;
           /* for(int j=1;j<=indel;j++){
               gap=gap+h;

            }*/
            if(i!=0 && S[i-1]!=0) optimum_cost=optimum_cost+h*indel;
            else optimum_cost=optimum_cost+gap(indel);
        }
    }


    DISPLAY(A,B,M,N); // This function prints Final display of the conversion implied by the alignment

    return optimum_cost; // returns optimum conversion cost
}

/* "diff" function is the recursive function. It finds the midpoint of an optimal conversion using a forward and reverse application of the linear
cost-only variation. The approach is described below.
*/
void diff(string A, string B, int M, int N, double tb, double te){


    if(N==0){ // if B string is empty then it deletes the A string completely for converting A to B
        if(M>0) {

            Delete=Delete+A.length();
        }
        S[Array_index]=-M;
        Array_index++;
    }
    else if(M==0){ // if A string is empty then it inserts the B string completely for converting A to B

        S[Array_index]=N;
        Insert=Insert+N;
        Array_index++;
    }
    else if(M==1){// if A array contains only 1 element
        double temp3, temp4, min_cost, min_val, min_index;

        /*calculates cost for two possible approaches for converting a(1) to B
        Approach 1: delete a1 and insert B
        Approach 2: find b(j) for which replacing cost of a1 to b(j) is minimum. Now, insert all the elements up to b(j-1). Replace a(1) with b(j). Again,
                    insert all the elements from b(j+1) up to b(N)
        if cost of Approach1 less than Approach 2, it deletes a(1) and inserts all elements of B. Else, it inserts all elements up to b(j-1), replaces a(1)
        with b(j) and then inserts all elements upto b(N). */
      /*  for(int j=1;j<=N;j++){
            gap_N=gap_N+gap(j);
        }*/

        temp3=min(tb,te)+h+gap(N);

        //min_val=1000000;

        min_val=DBL_MAX;
        for(int j=1;j<=N;j++){

            temp4= gap(j-1)+w(A[0],B[j-1])+gap(N-j);

            if(min_val>temp4){
                min_val=temp4;
                min_index=j;
            }
        }


        int index;
        if(min_val<temp3){
            for(int j=0;j<min_index-1;j++){

                Insert++;
            }
            if(min_index-1>0){
                S[Array_index]=min_index-1;
                Array_index++;
            }

            if(A[0]==B[min_index-1]){
                Match++;
                S[Array_index]=0;
                Array_index++;

            }
            else {

                S[Array_index]=0;
                Replace++;
                Array_index++;
            }


            for(int j=min_index;j<N;j++){

                Insert++;
            }
            if(min_index<N){
                S[Array_index]=N-min_index;
                Array_index++;
            }
        }
        else{

            S[Array_index]=-1;
            Array_index++;
            Delete++;

            for(int j=0;j<N;j++){

                Insert++;
            }
            if(N>0){
                S[Array_index]=N;
                Array_index++;
            }
        }
    }
    else{ /* This divides the A string into two parts. Then it calculates the optimum cost for converting the forward part using CC & DD. Later, it
            calculates optimum cost for converting the backward part using RR & SS. It calculates the total cost by adding the optimum costs for the both parts.
            This function recursively divides the strings using the divide-and-conquer algorithm and keeps breaking until string A contains single element. Then
            it finds out the cost and path to convert that array A containing single element to array Bj*. Here, j* is represents the division point of array B */

        int i_asteric=floor(M/2);//This finds the middle point i* of the string A.
        double t,s,c,e;

        //calculating CC and DD in forward phase
        double CC[N+1],DD[N+1];

        CC[0]=0;//initializing value of CC[0] and DD[0]
        t=g;

        //Calculating the initial values of CC and DD
        for(int j=1;j<=N;j++){
            CC[j]=t=t+h;
            DD[j]=t+g;
        }

        t=tb;  // replacing t<-g with t<-tb
        for(int i=1;i<=i_asteric;i++){

            s=CC[0];
            CC[0]=c=t=t+h;
            DD[0]=CC[0];
            e=t+g;

            for(int j=1;j<=N;j++){

                double temp;
                temp=c+g;
                e=min(e,temp)+h;
                temp=CC[j]+g;
                DD[j]=min(DD[j],temp)+h;
                temp=s+w(A[i-1],B[j-1]);   //Considering w(ai,bj)=1 and w(a,a)=0
                c=std::min(std::min(DD[j], e), temp);
                s=CC[j];
                CC[j]=c;
            }

        }

        /*calculating RR and SS in reverse phase. RR[N-j] contains the minimum cost of conversion of Ai*T to BjT ; SS[N-j] contains the minimum cost of
        conversion of Ai*T to BjT  that begins with a delete */
        double RR[N+1],SS[N+1];
        RR[0]=0;
        t=g;
        //Calculating the initial values of RR and SS
        for(int j=1;j<=N;j++){
            RR[j]=t=t+h;
            SS[j]=t+g;
        }

        t=te; // replacing t<-g with t<-te
        for(int i=1;i<=(M-i_asteric);i++){

            s=RR[0];
            RR[0]=c=t=t+h;
            SS[0]=RR[0];
            e=t+g;

            for(int j=1;j<=N;j++){

                double temp;
                temp=c+g;
                e=min(e,temp)+h;
                temp=RR[j]+g;
                SS[j]=min(SS[j],temp)+h;
                temp=s+w(A[M-i],B[N-j]);   //Considering w(ai,bj)=1 and w(a,a)=0
                c=std::min(std::min(SS[j], e), temp);
                s=RR[j];
                RR[j]=c;
            }
        }
        //find j*. the index of B for which the cost of converting a1 to b(j) is minimum. Using j*, the B array is divided into two parts
        double temp1, temp2,type;
        int j_asteric;
        double minimum=DBL_MAX;
        double mini;


        for(int j=0;j<=N;j++){
           temp1=CC[j]+RR[N-j];
           temp2=DD[j]+SS[N-j]-g;
           mini=min(temp1,temp2);
           if(mini<minimum){
                minimum=mini;
                j_asteric=j;

                if(temp1<temp2) type=1;
                else type=2;
           }
        }



        if(type==1){// type1 means the cost of converting A to B is less than the cost of converting A to B that ends with a delete

            //recursive calls for type1

            diff(A.substr (0,i_asteric),B.substr (0,j_asteric),i_asteric, j_asteric,tb,g);
            diff(A.substr (i_asteric,M-i_asteric),B.substr (j_asteric,N-j_asteric),M-i_asteric,N-j_asteric,g,te);

        }
        else if(type==2){// type2 means the cost of converting A to B is greater than the cost of converting A to B that ends with a delete

            //recursive calls for type2
            diff(A.substr (0,i_asteric-1),B.substr (0,j_asteric),i_asteric-1,j_asteric,tb,0);
            Delete= Delete+2;
            S[Array_index]=-2;
            Array_index++;
            diff(A.substr (i_asteric+1,M-i_asteric-1),B.substr (j_asteric,N-j_asteric),M-i_asteric-1,N-j_asteric,0,te);

        }

    }
}

/* It prints the optimum conversion method in the following way:
                                A G T A C
                                ! - - ! |
                                A     A G
*/
void DISPLAY(string A, string B, int M, int N){

    string display_format, display_A, display_B;
    int index=0, A_index=0,B_index=0;
    int max_length=max(M,N);

    while(A_index<M || B_index<N){

        if(S[index]==0){
            display_A+=A[A_index];
            display_B+=B[B_index];

            if(A[A_index]==B[B_index]) display_format+='!';
            else display_format+='|';

            A_index++;
            B_index++;
            index++;

            //display_A+=' ';
            //display_B+=' ';
            //display_format+=' ';
        }
        else if(S[index]<0){

            for(int j=1;j<=abs(S[index]);j++){
                display_A+=A[A_index];
                display_B+=' ';
                display_format+='-';

                //display_A+=' ';
                //display_B+=' ';
                //display_format+=' ';

                A_index++;
            }
            index++;

        }
        else{
            for(int j=1;j<=abs(S[index]);j++){
                display_A+=' ';
                display_B+=B[B_index];
                display_format+='-';

                //display_A+=' ';
                //display_B+=' ';
                //display_format+=' ';

                B_index++;
            }
            index++;
        }
    }
    
    cout<<"Final display of the conversion implied by the alignment:"<<endl<<endl;

    for(int i=0;i<display_A.length();i=i+210){

        for(int j=i;j<i+210;j++){
            if(j==display_A.length()) break;
            cout<<display_A[j];
        }
        cout<<endl;
         for(int j=i;j<i+210;j++){
            if(j==display_format.length()) break;
            cout<<display_format[j];
        }
        cout<<endl;
         for(int j=i;j<i+210;j++){
            if(j==display_B.length()) break;
            cout<<display_B[j];
        }
        cout<<endl;

        cout<<endl;
        cout<<endl;
    }
}
