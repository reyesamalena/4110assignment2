#include <fstream>
#include <iostream>
using namespace std;

void counter(char *inName, char *outName)
{
	int freq[128];     // frequencies of letters
   	char ch;

	ifstream input(inName);
        if (!input)
        {
                cerr << "error: can't open file\n";
                return;
        }

  	// initialize frequency counts to zero for each possible letter
  	for (int k = 0; k < 128; k++)
  	{
  	 	freq[k] = 0;
   	}

   	// Read the file, keeping track of frequency with which each letter occurs
   	ch = input.get();
   	while (ch != EOF)
   	{
		if(isalpha(ch))	
		{
      			ch = tolower(ch);
      			freq[ch]++;
		}
      		ch = input.get();
   	}

   	input.close();      // close input file

	ofstream output(outName);
   	if (!output)
        {
                cerr << "error: can't open file\n";
                return;
        }
	
	// Print the output table
  	for (char ch = 'a'; ch <= 'z'; ch++)
  	{
      		if(freq[ch] > 0) {
      			output << ch << " " << freq[ch] << endl; }
  	}

  	output.close();
}
