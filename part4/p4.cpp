// C program for Huffman Coding 
// contribution from: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
#include <stdio.h> 
#include <stdlib.h> 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "counter.cpp"

using namespace std;

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 

// A Huffman tree node 
struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child of this node 
	struct MinHeapNode *left, *right; 
}; 

// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap { 

	// Current size of min heap 
	unsigned size; 

	// capacity of min heap 
	unsigned capacity; 

	// Array of minheap node pointers 
	struct MinHeapNode** array; 
}; 

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp 
		= (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity) 

{ 

	struct MinHeap* minHeap 
		= (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	// current size is 0 
	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array 
		= (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, 
					struct MinHeapNode** b) 

{ 

	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx) 

{ 

	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], 
						&minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap) 
{ 

	return (minHeap->size == 1); 
} 

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 

{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] 
		= minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, 
				struct MinHeapNode* minHeapNode) 

{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap) 

{ 

	int n = minHeap->size - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

// A utility function to print an array of size n 
void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		printf("%d", arr[i]); 

	printf("\n"); 
} 

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root) 

{ 

	return !(root->left) && !(root->right); 
} 

// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 

{ 

	struct MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 

// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 

{ 
	struct MinHeapNode *left, *right, *top; 

	// Step 1: Create a min heap of capacity 
	// equal to size. Initially, there are 
	// modes equal to size. 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) { 

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		// Step 3: Create a new internal 
		// node with frequency equal to the 
		// sum of the two nodes frequencies. 
		// Make the two extracted node as 
		// left and right children of this new node. 
		// Add this node to the min heap 
		// '$' is a special value for internal nodes, not used 
		top = newNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	// Step 4: The remaining node is the 
	// root node and the tree is complete. 
	return extractMin(minHeap); 
} 

// Prints huffman codes from the root of Huffman Tree. 
// It uses arr[] to store codes 
void printCodes(struct MinHeapNode* root, int arr[], int top) 

{ 

	// Assign 0 to left edge and recur 
	if (root->left) { 

		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	// Assign 1 to right edge and recur 
	if (root->right) { 

		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 

	// If this is a leaf node, then 
	// it contains one of the input 
	// characters, print the character 
	// and its code from arr[] 
	if (isLeaf(root)) { 

		printf("%c: ", root->data); 
		printArr(arr, top); 
	} 
} 

// The main function that builds a 
// Huffman Tree and print codes by traversing 
// the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size) 

{ 
	// Construct Huffman Tree 
	struct MinHeapNode* root 
		= buildHuffmanTree(data, freq, size); 

	// Print Huffman codes using 
	// the Huffman tree built above 
	int arr[MAX_TREE_HT], top = 0; 

	printCodes(root, arr, top); 
} 

// Driver program to test above functions 
int main() 
{ 
	//Input txt files
	char threeMEng[25] = "3MusketeersEnglish.txt";
	char threeMFren[25] = "3MusketeersFrench.txt";
	char threeMSpan[25] = "3MusketeersSpanish.txt";
	char mobyEng[25] = "MobyDickEnglish.txt";
	char mobyFren[25] = "MobyDickFrench.txt";
	char mobySpan[25] = "MobyDickSpanish.txt";
	char donQEng[25] = "DonQuixoteEnglish.txt";
	char donQFren[25] = "DonQuixoteFrench.txt";
	char donQSpan[25] = "DonQuixoteSpanish.txt";
	
	//pointers
	char *threeMEnglish = threeMEng;
	char *threeMFrench = threeMFren;
	char *threeMSpanish = threeMSpan;
	char *mobyEnglish = mobyEng;
	char *mobyFrench = mobyFren;
	char *mobySpanish = mobySpan;
	char *donQEnglish = donQEng;
	char *donQFrench = donQFren;
	char *donQSpanish = donQSpan;
	
	//Output txt files
	char out3MEng[25] = "3MusketEnglishHist.txt";
	char out3MFren[25] = "3MusketFrenchHist.txt";
	char out3MSpan[25] = "3MusketSpanishHist.txt";
	char outMobyEng[25] = "MobyEnglishHist.txt";	
	char outMobyFren[25] = "MobyFrenchHist.txt";	
	char outMobySpan[25] = "MobySpanishHist.txt";	
	char outDonQEng[25] = "DonEnglishHist.txt";
	char outDonQFren[25] = "DonFrenchHist.txt";
	char outDonQSpan[25] = "DonSpanishHist.txt";

	//pointers
	char *out3MEnglish = out3MEng;
	char *out3MFrench = out3MFren;
	char *out3MSpanish = out3MSpan;
	char *outMobyEnglish = outMobyEng;
	char *outMobyFrench = outMobyFren;
	char *outMobySpanish = outMobySpan;
	char *outDonQEnglish = outDonQEng;
	char *outDonQFrench = outDonQFren;
	char *outDonQSpanish = outDonQSpan;

	//Analyzer 2k words from books and create output files
	//3 Musketeers
	counter(threeMEnglish,out3MEnglish); 
	counter(threeMFrench,out3MFrench);
	counter(threeMSpanish,out3MSpanish);	
	//Moby Dick
	counter(mobyEnglish,outMobyEnglish);	
	counter(mobyFrench,outMobyFrench);
	counter(mobySpanish,outMobySpanish);
	//Don Quixote
	counter(donQEnglish,outDonQEnglish);
	counter(donQFrench,outDonQFrench);
	counter(donQSpanish,outDonQSpanish);


	//read output files into char array and freq array
	char c;
	int f;
	//3 Musketeers
	vector<char> vec3ME, vec3MF, vec3MS;
	vector<int> fvec3ME, fvec3MF, fvec3MS;
	
	//English
	ifstream i1(out3MEnglish);
	while(i1 >> c >> f)
	{
		vec3ME.push_back(c);
		fvec3ME.push_back(f);
	}
	i1.close();
	//French
	ifstream i2(out3MFrench);
	while(i2 >> c >> f)
	{
		vec3MF.push_back(c);
		fvec3MF.push_back(f);
	}
	i2.close();
	//Spanish
	ifstream i3(out3MSpanish);
	while(i3 >> c >> f)
	{
		vec3MS.push_back(c);
		fvec3MS.push_back(f);
	}
	i3.close();
		
	//Moby Dick
	vector<char> vecMDE, vecMDF, vecMDS;
	vector<int> fvecMDE, fvecMDF, fvecMDS;
	//English
	ifstream i4(outMobyEnglish);
	while(i4 >> c >> f)
	{
		vecMDE.push_back(c);
		fvecMDE.push_back(f);
	}
	i4.close();
	//French
	ifstream i5(outMobyFrench);
	while(i5 >> c >> f)
	{
		vecMDF.push_back(c);
		fvecMDF.push_back(f);
	}
	i5.close();
	//Spanish
	ifstream i6(outMobySpanish);
	while(i6 >> c >> f)
	{
		vecMDS.push_back(c);
		fvecMDS.push_back(f);
	}
	i6.close();

	//Don Quixote
	vector<char> vecDQE, vecDQF, vecDQS;
	vector<int> fvecDQE, fvecDQF, fvecDQS;
	//English
	ifstream i7(outDonQEnglish);
	while(i7 >> c >> f)
	{
		vecDQE.push_back(c);
		fvecDQE.push_back(f);
	}
	i7.close();
	//French
	ifstream i8(outDonQFrench);
	while(i8 >> c >> f)
	{
		vecDQF.push_back(c);
		fvecDQF.push_back(f);
	}
	i8.close();
	//Spanish
	ifstream i9(outDonQSpanish);
	while(i9 >> c >> f)
	{
		vecDQS.push_back(c);
		fvecDQS.push_back(f);
	}
	i9.close();

	//copy vectors into arrays for HuffmanCodes
	// 3 Musketeers	
	char arr3ME[vec3ME.size()], arr3MF[vec3MF.size()], arr3MS[vec3MS.size()];
	int freq3ME[fvec3ME.size()], freq3MF[fvec3MF.size()], freq3MS[fvec3MS.size()];
	copy(vec3ME.begin(),vec3ME.end(),arr3ME);
	copy(vec3MF.begin(),vec3MF.end(),arr3MF);
	copy(vec3MS.begin(),vec3MS.end(),arr3MS);
	copy(fvec3ME.begin(),fvec3ME.end(),freq3ME);
	copy(fvec3MF.begin(),fvec3MF.end(),freq3MF);
	copy(fvec3MS.begin(),fvec3MS.end(),freq3MS);
	// Moby Dick
	char arrMDE[vecMDE.size()], arrMDF[vecMDF.size()], arrMDS[vecMDS.size()];
	int freqMDE[fvecMDE.size()], freqMDF[fvecMDF.size()], freqMDS[fvecMDS.size()];
	copy(vecMDE.begin(),vecMDE.end(),arrMDE);
	copy(vecMDF.begin(),vecMDF.end(),arrMDF);
	copy(vecMDS.begin(),vecMDS.end(),arrMDS);
	copy(fvecMDE.begin(),fvecMDE.end(),freqMDE);
	copy(fvecMDF.begin(),fvecMDF.end(),freqMDF);
	copy(fvecMDS.begin(),fvecMDS.end(),freqMDS);
	// Don Quixote
	char arrDQE[vecDQE.size()], arrDQF[vecDQF.size()], arrDQS[vecDQS.size()];
	int freqDQE[fvecDQE.size()], freqDQF[fvecDQF.size()], freqDQS[fvecDQS.size()];
	copy(vecDQE.begin(),vecDQE.end(),arrDQE);
	copy(vecDQF.begin(),vecDQF.end(),arrDQF);
	copy(vecDQS.begin(),vecDQS.end(),arrDQS);
	copy(fvecDQE.begin(),fvecDQE.end(),freqDQE);
	copy(fvecDQF.begin(),fvecDQF.end(),freqDQF);
	copy(fvecDQS.begin(),fvecDQS.end(),freqDQS);

	//Get size of arrays
	//3 Musketeers
	int size3ME = sizeof(arr3ME) / sizeof(arr3ME[0]); 
	int size3MF = sizeof(arr3MF) / sizeof(arr3MF[0]); 
	int size3MS = sizeof(arr3MS) / sizeof(arr3MS[0]); 
	//Moby Dick
	int sizeMDE = sizeof(arrMDE) / sizeof(arrMDE[0]); 
	int sizeMDF = sizeof(arrMDF) / sizeof(arrMDF[0]); 
	int sizeMDS = sizeof(arrMDS) / sizeof(arrMDS[0]); 
	//Don Quixote
	int sizeDQE = sizeof(arrDQE) / sizeof(arrDQE[0]); 
	int sizeDQF = sizeof(arrDQF) / sizeof(arrDQF[0]); 
	int sizeDQS = sizeof(arrDQS) / sizeof(arrDQS[0]); 

	cout << "Original Languages Codes:" << endl;
	cout << "Three Musketeers in French: " << endl;
	HuffmanCodes(arr3MF, freq3MF, size3MF); 
	cout << "Moby Dick in English: " << endl;
	HuffmanCodes(arrMDE, freqMDE, sizeMDE); 
	cout << "Don Quixote in Spanish: " << endl;
	HuffmanCodes(arrDQS, freqDQS, sizeDQS); 
	
	cout << endl << "Translated into Different Languages: " << endl;
	cout << "Three Musketeers in English: " << endl;
	HuffmanCodes(arr3ME, freq3ME, size3ME); 
	cout << "Three Musketeers in Spanish: " << endl;
	HuffmanCodes(arr3MS, freq3MS, size3MS); 
	
	cout << "Moby Dick in Spanish: " << endl;
	HuffmanCodes(arrMDS, freqMDS, sizeMDS); 
	cout << "Moby Dick in French: " << endl;
	HuffmanCodes(arrMDF, freqMDF, sizeMDF); 
	
	cout << "Don Quixote in English: " << endl;
	HuffmanCodes(arrDQE, freqDQE, sizeDQE); 
	cout << "Don Quixote in French: " << endl;
	HuffmanCodes(arrDQF, freqDQF, sizeDQF); 

	return 0; 
} 


