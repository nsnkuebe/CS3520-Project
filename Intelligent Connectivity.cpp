#include <iostream>
using namespace std;

string chooseBestNetwork(int signals[],string names[], int size){
	int bestIndex = 0;
	for(int i=0; i< size; i++){
		if(signals[i]> signals[bestIndex]){
			bestIndex = i;
		}
	}
	return names[bestIndex];
}

int main(){
	const int SIZE= 3; 
	int signals[SIZE];
	string names[SIZE]= {"WiFi","Mobile Data","Satallite"};
	
	cout << "Connectivity Options" << endl;
	cout << endl;
	
	cout<<"Enter WiFi siganal strengh: ";
	cin >> signals[0];
	cout<< "Enter Mobile Data signal strengh: ";
	cin>> signals[1];
	cout<< "Enter Satallite signal strength: ";
	cin>> signals[2];
	cout << endl;
	
	cout<< "Intellegent connectivity: Best Network is "
	    <<chooseBestNetwork(signals,names, SIZE)<< endl;
	return 0;    
}
