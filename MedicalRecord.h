#pragma once
#include <string>
#include <stdexcept>

#include "Baby.h"

using namespace std;

class MedicalRecord {
public:
	// default constructor
	MedicalRecord() { //TBC
		lowWeight = 0;
		n = 0;
		name = new string[200000];			//dynamic data b/c of large size
		weight = new int[200000];
	}

	// destructor
	~MedicalRecord() {
		
	}

	// Load information from a text file with the given filename.
	void buildMedicalRecordfromDatafile(string filename) {
		ifstream myfile(filename);

		if (myfile.is_open()) {
			cout << "Successfully opened file " << filename << endl;
			string name;
			int weight;
			while (myfile >> name >> weight) {
				//cout << name << " " << weight << endl; // was commented
				Baby b(name, weight);
				addEntry(b);
			}
			myfile.close();
		}
		else
			throw invalid_argument("Could not open file " + filename);
	}

	// return the most frequently appearing name in the text file
	string mostPopularName() {
		string nameHolder;
		int mostCount = 0;
		int tempCount;
		int placeU = 0; // limits the max loop
		string uName[1000];
		for (int i = 0; i < n; i++) {
			tempCount = 0;
			for (int j = 0; j <= placeU; j++) {
				if (name[i] == uName[j])	//Checks if the name is unique! If not, it breaks and goes to i loop
					break;
				else if (uName[j] == "") {
					uName[j] = name[i];
					placeU++;				//If it is unique , placeU increments
					for (int k = 0; k < n; k++) { //Loop to count how many of the same name in text
						if (uName[j] == name[k])
							tempCount++;
					}
					if (tempCount > mostCount) {	//see if the new Unique name is more popular the currect holder
						nameHolder = uName[j];
						mostCount = tempCount;
					}
					break;						//Breaks out of j loop and straight to i loop
				}
			}
		}
		

		return nameHolder;
	}

	// return the number of baby records loaded from the text file
	int numberOfBirths() {
		return n;
	}

	// return the number of babies who had birth weight < 2500 grams
	int numberOfBabiesWithLowBirthWeight() {
		for (int i = 0; i < n; i++) {
			if (weight[i] < 2500)
				lowWeight++;
		}
		return lowWeight;
	}

	// return the number of babies who have the name contained in string s
	int numberOfBabiesWithName(string s) {
		for (int i = 0; i < n; i++) {
			if (name[i] == s)
				x++;
		}
		return x;
	}

private:
	// update the data structure with information contained in Baby object
	void addEntry(Baby b) {
		name[n] = b.getName();
		weight[n] = b.getWeight();
		n++;
	}

	// Add private member variables for your data structure along with any 
	// other variables required to implement the public member functions
	int *weight;
	string *name;
	int lowWeight;
	int n; //number of births
	int x = 0; //count for  numberOfBabiesWithName(string s)
};
