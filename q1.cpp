#include <iostream>
using namespace std;

typedef struct {
   int v;
   int w;
   float d;
} Item;


bool compare(Item i1, Item i2) {
   return (i1.d > i2.d);
}
float fracknapsack(Item items[], int n, int W) {
   int i, j, pos;
   Item mx, temp;
   float totalValue = 0, totalWeight = 0;
   for (i = 0; i < n; i++) {
       
      items[i].d = items[i].v / items[i].w;
       
   }
   sort(items, items+n, compare);
   for(i=0; i<n; i++) {
       
      if(totalWeight + items[i].w<= W) {
         totalValue += items[i].v ;
         totalWeight += items[i].w;
      } else {
         int wt = W-totalWeight;
         totalValue += (wt * items[i].d);
         totalWeight += wt;
         break;
      }
   }
  // cout << "total weight in bag " << totalWeight<<endl;
   return totalValue;
}
int max(int x, int y) {
   return (x > y) ? x : y;
}
int knapSack(int W, int w[], int v[], int n, char type[], int frac[], Item items[]) {
    int i, wt;
   int K[n + 1][W + 1];
   for (i = 0; i <= n; i++) {
      for (wt = 0; wt <= W; wt++) {
         if (i == 0 || wt == 0)
         K[i][wt] = 0;
         else if (w[i - 1] <= wt)
            K[i][wt] = max(v[i - 1] + K[i - 1][wt - w[i - 1]], K[i - 1][wt]);
         else
        K[i][wt] = K[i - 1][wt];
      }
   }
   return K[n][W];
}
int comboknapSack(int W, int w[], int v[], int n, char type[], int frac[], Item items[]) {
   int i, wt;
   int K[n + 1][W + 1];
   Item mx, temp;
    
   float totalValue = 0, totalWeight = 0;
   for (i = 0; i < n; i++) {
       
      items[i].d = items[i].v / items[i].w;
       
   }
    if(type[W-1] == 'F'){  //if the max weight we are looking for if a fractional knapsack problem
        sort(items, items+n, compare);  //we can start to sort in descending
        for(i=0; i<n; i++) {            //order of the ratios of items/id structs
       
            if(totalWeight + items[i].w<= W) {
                totalValue += items[i].v ;
                totalWeight += items[i].w;
            } else {
                int wt = W-totalWeight;
                totalValue += (wt * items[i].d);
                totalWeight += wt;
                break;
            }
        }
        cout <<"it ended in fractional" << endl;
        return totalValue;
    }
    
   for (i = 0; i <= n; i++) {

           for (wt = 0; wt <= W; wt++) {
               if (i == 0 || wt == 0){
                   K[i][wt] = 0;
               }
               else if (w[i - 1] <= wt){
                   K[i][wt] = max(items[i - 1].v + K[i - 1][wt - items[i - 1].w], K[i - 1][wt]);
               }
               else{
                   K[i][wt] = K[i - 1][wt];
               }
               
           }
       
       
   }
   return K[n][W];
}
int main() {
  // cout << "Enter the number of items in a Knapsack: ";
   int n, W;
    char type[] = {'W','W','W','W','W','W','F','F', 'F','F'};
    int v[]= {50,25,60,15,40,30,50,30,50,10};
    int  w[] = {3,2,4,1,3,2,3,2,4,1};
    int d[10];
    n = 10;
    int fW;
    Item items[10];
    for(int i = 0; i < 10; i++) {
        
        items[i].v = v[i];
        items[i].w = w[i];
        d[i] = v[i]/w[i];
    }

   cout <<endl<< "Enter the capacity of 0/1 knapsack "<< endl;
   cin >> W;
 
   cout <<endl<<"Max value for  0/1 knapsack is "<< knapSack(W, w, v, n, type, d, items);
    

    cout<< endl<<"Enter the capacity of fractional Knapsack \n";
    cin >> fW;
    float mxVal = fracknapsack(items, 10, fW);
    cout <<endl <<"Max value for fractional Knapsack is "<< mxVal;
    
    cout<<endl <<"Enter the capacity of combo Knapsack \n";
    cin >> fW;
    float cxVal = fracknapsack(items, 10, fW);
   cout <<endl<<"Max value for  combo Knapsack is "<< comboknapSack(W, w, v, n, type, d, items);
   return 0;
}
