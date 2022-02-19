#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<stdio.h>
//#include<conio.h>
#include <string>
#include <sstream>
using namespace std;

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */

fstream outfile;
fstream temp;
fstream reversed;

void lcs(string X, string Y, int m, int n)
{

   int LL[3][n+1];


//*******************calculating cost of LCS using 2 rows************************************
   for (int j=0; j<=n; j++)
   {
        LL[0][j] = 0;

   }
   LL[1][0]=0;



    for (int i=1; i<=m; i++)
    {
        outfile << LL[1][0]<<" ";
        for (int j=1; j<=n; j++)
        {
            if (X[i-1] == Y[j-1])
            LL[1][j] = LL[0][j-1] + 1;
            else
            LL[1][j] = max(LL[0][j], LL[1][j-1]);

            outfile << LL[1][j]<<" ";
        }
        outfile<<endl;


        for(int j=1; j<=n; j++)
        {
            LL[0][j]=LL[1][j];
        }

    }


//**********************copying the LL array in reverse order to another file************************************
    outfile.close();
    outfile.open("output1.txt");
    reversed.open("output3.txt");
    reversed<<"start"<<endl;

    string line2;
    while(getline(outfile,line2)){

      temp.open("output2.txt");
      temp<<line2<<endl;
     // cout<<line2<<endl;
      //cout<<"ok"<<endl;
      reversed.seekg(0);
      temp << reversed.rdbuf();

      temp.seekg(0);
      reversed.close();
      reversed.open("output3.txt");

      string line3;
      while(getline(temp,line3)){
          //cout<<"kkk"<<endl;
          reversed<<line3<<endl;
      }

      temp.close();

    }
    reversed.close();


   // Followieng code is used to print LCS


     // Followieng code is used to print LCS

   reversed.open("output3.txt");
   string line4;
   getline(reversed,line4);
   getline(reversed,line4);
      int len=line4.length();
      //cout<<len<<endl;

      int d=0;
      for(int l=0;l<len-1;l++){
         int value =0;
         int val;
         int mul=1;
         while(line4[l]!=' '){
           val = line4[l]- 48;
           value=value*mul+val;
           mul=mul*10;
           l++;
        }

        //cout<<value<<endl<<"see val"<<endl;
        LL[0][d]= value;
        d++;

      }

   int index2 = LL[1][n];

   // Create a character array to store the lcs string
   char lcs2[index2+1];
   lcs2[index2] = '\0'; // Set the terminating character

   // Start from the right-most-bottom-most corner and
   // one by one store characters in lcs[]

     /*for(int p=0;p<2;p++){
        for(int q=0;q<=n;q++){
            cout<<LL[p][q]<<" ";
        }
        cout<<endl;
      }
      cout<<"fff"<<endl;*/

   int i = m, j = n;
   while (i > 0 && j > 0)
   {




    /* for(int p=0;p<2;p++){
        for(int q=0;q<=n;q++){
            cout<<LL[p][q]<<" ";
        }
        cout<<endl;
      }
      cout<<"fff"<<endl;*/


      // If current character in X[] and Y are same, then
      // current character is part of LCS

      if (X[i-1] == Y[j-1])
      {

          lcs2[index2-1] = X[i-1]; // Put current character in result
          i--; j--; index2--;     // reduce values of i, j and index



          getline(reversed,line4);
          int len=line4.length();
      //cout<<len<<endl;

          int d=0;
          for(int l=0;l<len-1;l++){
            int value =0;
            int val;
            int mul=1;
            while(line4[l]!=' '){
            val = line4[l]- 48;
            value=value*mul+val;
            mul=mul*10;
            l++;
           }

        //cout<<value<<endl<<"see val"<<endl;
           LL[0][d]= value;
           d++;

           }



           for(int k=0;k<=n;k++){
           LL[1][k]=LL[0][k];
      }
      }

      // If not same, then find the larger of two and
      // go in the direction of larger value
      else if (LL[0][j] > LL[1][j-1])
         i--;
      else
         j--;



   }

   int lcs2len = strlen(lcs2);
   // Print the lcs
   cout <<lcs2<<endl;
   cout << lcs2len << endl;
   reversed.close();
}

/* Driver program to test above function */
int main(int argc, char **argv)
{
  //char X[] = "AGGTAB";
  //char Y[] = "GXTXAYB";
  if(argc < 3) {
    cout << "Please provide the filepaths of the two files you wish to compare" << endl;
    return 2;
  }
  
  outfile.open("output1.txt");

  string line, X, Y;

  ifstream f1 (argv[1]);
  if (f1.is_open())
  {
    while (getline (f1,line) )
    {
      X = X + line;
    }
  //  cout<<X<<endl;
    f1.close();
  }

  ifstream f2 (argv[2]);
  if (f2.is_open())
  {
    while (getline (f2,line) )
    {
      Y = Y + line;
    }
  //  cout<<Y<<endl;
    f2.close();
  }

  int m = X.length();
  int n = Y.length();
  cout<<m<<endl;
  cout<<n<<endl;


  lcs(X, Y, m, n);

    outfile.close();
   // outfile2.close();



    return 0;
}
