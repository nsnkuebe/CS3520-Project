#include <iostream>

using namespace std;

bool verifyBiometric(int arr1[], int arr2[], int size){
	int boolCount = 0;
	for(int i = 0; i < size; i++){
		if(arr1[i] == arr2[i]){
			boolCount++;
		}
	}
	return (boolCount == size);
}

int main(){
	int storedBiometric[5] = {1, 3, 5, 7, 9};
	
	int size = 5;
	int *currentBiometric = new int[size];
	
	cout << "Biometric Requires Five(5) Intergers" << endl;
	cout << endl;
	for(int i = 0; i < size; i++){
		cout << "Enter the integer: ";
		cin >> currentBiometric[i];
	}
	cout << endl;
	
	if(verifyBiometric(storedBiometric, currentBiometric, size)){
		cout << "Access Granted!" << endl;
	}
	else{
		cout << "Access Denied!" << endl;
	}
} 
