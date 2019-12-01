// A Naive recursive C++ program to find minimum number 
// operations to convert str1 to str2 
// code contribution: https://www.geeksforgeeks.org/edit-distance-dp-5/
//#include<bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std; 

// Utility function to find minimum of three numbers 
int min(int x, int y, int z) 
{ 
return min(min(x, y), z); 
} 

int editDist(string str1 , string str2 , int m ,int n) 
{ 
	// If first string is empty, the only option is to 
	// insert all characters of second string into first 
	if (m == 0) return n; 

	// If second string is empty, the only option is to 
	// remove all characters of first string 
	if (n == 0) return m; 

	// If last characters of two strings are same, nothing 
	// much to do. Ignore last characters and get count for 
	// remaining strings. 
	if (str1[m-1] == str2[n-1]) 
		return editDist(str1, str2, m-1, n-1); 

	// If last characters are not same, consider all three 
	// operations on last character of first string, recursively 
	// compute minimum cost for all three operations and take 
	// minimum of three values. 
	return 1 + min ( editDist(str1, str2, m, n-1), // Insert 
					editDist(str1, str2, m-1, n), // Remove 
					editDist(str1, str2, m-1, n-1) // Replace 
				); 
} 

// Driver program 
int main(int argc, char *argv[]) 
{ 
       // holds the mistyped word in strs[0] and the suggestions in the remaining space
        string strs[6] = {"sdimnas","dynast","summer","dismal","dimmer","sadden"};

        // holds the number differences for each suggestion
        int diffs[5];
        // holds the lowest number of differences
        int min = 100;

        // find the differences for each suggestion
        for(int i=1;i<6;i++)
        {
                diffs[i-1] = editDistDP(strs[0], strs[i], strs[0].length(), strs[i].length());
                // find the lowest difference
                if(min > diffs[i-1])
                        min = diffs[i-1];
        }

        // print out all the suggestions and the number of differences
        cout << "Number of differences for each word candidate:" << endl;
        for(int i=0;i<5;i++)
        {
                cout << strs[i+1] << " : " << diffs[i] << endl;
        }

        // print out the words with the lowest differences
        cout << endl << "The suggested word is: " << endl;
        for(int i=0;i<5;i++)
        {
                if(diffs[i] == min)
                        cout << strs[i+1] << " : " << diffs[i] << endl;
        }


	return 0; 
} 

