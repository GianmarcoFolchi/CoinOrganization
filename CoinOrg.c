#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
typedef long long int lli; 
typedef struct {
    char *name;
    lli tokens, bills; 
    int index; 
} Person;

//function declarations
Person createNew(char name[], lli tokens, lli bills, int index); 
void printArr(Person arr[], int n);
void convert(Person arr[], int n, lli t, lli b); 
void mergeSort(Person arr[], int n); 


int main() {
    int n, i, index;
    lli tokens, bills, t, b;  
    char name[20]; 

    //scan in the number of people
    printf("Input the number of people \n"); 
    scanf("%d", &n); 

    Person arr[n+1];

    //for loop to create the person structs and scan in the data  
    for (i = 0; i < n; i++) {
        printf("Input the name: \n"); 
        scanf(" %s", name); 

        printf("Input the number of tokens: \n"); 
        scanf(" %lli", &tokens);

        printf("Input the number of bills: \n"); 
        scanf(" %lli", &bills);

        index = i; 
        arr[index] = createNew(name, tokens, bills, index); 
    }

    //scan in the conversion values 
    printf("enter the conversion values:\n"); 
    scanf(" %lli", &t); 
    scanf(" %lli", &b); 

    //equalize all values through the function 
    convert(arr, n, t, b); 

    //sort the objects into the correct order using the merge sort
    mergeSort(arr, n); 
    //print the final result
    printArr(arr, n); 

    return 0; 
}



Person createNew(char name[], lli tokens, lli bills, int index) { 
    Person p; //create the instance
    p.name = malloc(20*sizeof(char)); //create the space for the name of the instance
    strcpy(p.name, name); //attach the name into the instance
    //fill out the rest of the values for the struct
    p.tokens = tokens; 
    p.bills = bills; 
    p.index = index;
    return p; 
}

void printArr(Person arr[], int n) {
    int i; 
    for (i = 0; i < n; i++) 
        printf("the %dth object's name = %s, tokens = %lli, bills = %lli \n", i, arr[i].name, arr[i].tokens, arr[i].bills); 
}

void convert(Person arr[], int n, lli t, lli b) {
    int i; 
    for (i = 0; i < n; i++) {
        arr[i].tokens = arr[i].tokens * b + arr[i].bills * t; //account for both unit types and add those into the tokens variable
    }
}

void mergeSort(Person arr[], int n) {
    int mid, i; 
    if (n <= 1) {  //base case
        return; 
    }

    mid = n / 2; //find the midpoint in order to divide the list

    //recursive calls
    mergeSort(arr, mid); 
    mergeSort(arr+mid, n - mid);

    Person *ans = calloc(n, sizeof(Person)); //create space for the answer to be stored in 
    int fptr = 0; 
    int bptr = mid; 

    for (i = 0; i < n; i++) {
        if (fptr != mid && bptr != n && arr[fptr].tokens <= arr[bptr].tokens) { //check the pointers are in the correct space and add the corresponding value into the ans array
            ans[i] = arr[bptr]; 
            bptr++; 
        } else if (fptr != mid && bptr != n && arr[fptr].tokens >= arr[bptr].tokens) { //check the pointers are in the correct space and add the corresponding value into the ans array
            ans[i] = arr[fptr]; 
            fptr++;
        } else if (fptr == mid) { //add the rest of the values from the back pointer
            ans[i] = arr[bptr]; 
            bptr++; 
        } else if (bptr == n) { //add the rest of the values from the front pointer
            ans[i] = arr[fptr]; 
            fptr++; 
        }
    }
    memcpy(arr, ans, sizeof(Person) * n); //copy ans to arr
    free(ans); //free the created space that is no longer needed
}