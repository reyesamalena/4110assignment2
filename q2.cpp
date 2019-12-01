#include<iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cstring>

using namespace std;
  
int max(int a, int b);
  
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char *X, char *Y, int m, int n )
{
    int L[m + 1][n + 1];
    int i, j;
      
    /* Following steps build L[m+1][n+1] in
       bottom up fashion. Note that L[i][j]
       contains length of LCS of X[0..i-1]
       and Y[0..j-1] */
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
        if (i == 0 || j == 0)
            L[i][j] = 0;
      
        else if (X[i - 1] == Y[j - 1])
            L[i][j] = L[i - 1][j - 1] + 1;
      
        else
            L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
          
    /* L[m][n] contains length of LCS
    for X[0..n-1] and Y[0..m-1] */
    return L[m][n];
}
  
/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}
  
// Driver Code
int main()
{
    
    unordered_map<string, string> umap;
    string filename, name, sequence;
    ifstream inf;
    int times=1;

    string string1;
    string string2;

    cout << "Enter the .txt file to be evaluated:" << endl;
        cout << "***NOTE: the file must be formated with the name of the sequence on its own line followed by the sequence. See README.txt for example***" << endl;
    cin >> filename;
    
     inf.open(filename);
     if (!inf) {
        cout << "File cannot be opened";
        exit(1);
    }
    
    while (!inf.eof())
    {
        getline(inf, name);
        getline(inf, sequence);
        umap[name] = sequence; //adding name and sequences into
    }//an unordered map
    
    for (auto x : umap){
        string printname = x.first;
        string temp = x.second; //temp string of sequence
        
        char seqarray[temp.size() +1]; //turning it into a char
        strcpy(seqarray, temp.c_str()); //char array
        int m = strlen(seqarray);
        cout << "\033[1;33m";
        cout << printname <<endl;
        cout << "\033[0m";
        
        for(auto m:umap){
            string comparename = m.first;
            string comparetemp = m.second; //temp string of sequence
            if(printname.compare(comparename)==0){
                
            }else{
                char comp_seqarray[comparetemp.size() +1]; //turning it into a char
                strcpy(comp_seqarray, comparetemp.c_str()); //char array
                int n = strlen(comp_seqarray);
                cout << "Length of LCS for " << printname << " and " << comparename<< " is " << lcs( seqarray, comp_seqarray, temp.size() +1, comparetemp.size() +1 )<< endl;
            }
        }
    }
    
    return 0;
}
  

