// Homework4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

//print preferences table functions
void printBoyPreferencesTable(vector <vector<int>> preferences, vector <string>boyNames, vector <string>girlNames) {
    cout << endl <<"Printing Boy Preference Table......................." << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Boy Name | Girl Names By Preference (Highest -> Lowest)" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < boyNames.size(); i++) {
        cout << boyNames.at(i) << " | ";
        for (int j = 0; j < girlNames.size(); j++) {
            if (j != girlNames.size() - 1) {
                cout << girlNames.at(preferences[i][j] - 1) << ", ";
            }
            else {
                cout << girlNames.at(preferences[i][j] - 1) << endl;
            }
        }
        cout << "-----------------------------------------------------------------------------------------" << endl;
    }
}
void printGirlPreferencesTable(vector <vector<int>> preferences, vector <string>boyNames, vector <string>girlNames) {
    cout << endl << "Printing Girl Preference Table......................." << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << "Girl Name | Boy Names By Preference (Highest -> Lowest)" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < girlNames.size(); i++) {
        cout << girlNames.at(i) << " | ";
        for (int j = 0; j < boyNames.size(); j++) {
            if (j != boyNames.size() - 1) {
                cout << boyNames.at(preferences[i][j] - 1) << ", ";
            }
            else {
                cout << boyNames.at(preferences[i][j] - 1) << endl;
            }
        }
        cout << "-----------------------------------------------------------------------------------------" << endl;
    }
}

//helps with structure/readability of Gale-Shapley algorithm
struct person {
    bool isFree = true; 
    vector<int> preferences;
    int preferenceIndex = 0; //for boys to keep track of who hasnt rejected them yet
    int id; // for boys when they get assigned to a couple and they lose their permutation
};
struct couple { //edge
    person boy; 
    person girl;
};

int main()
{
    //START USER INPUT SECTION ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //variable declarations
    int numCouples;
    vector <string> boyNames;
    vector <string> girlNames;
    //temp variable for various user input
    string temp;
    //prevents many possible bugs
    cout << "Please input the desired number of happy couples: " << endl;
    cin >> numCouples;
    //initializes appropriatley sized 2D vectores 
    vector <int> emptyVector;
    vector <vector<int>> boyPreferences(numCouples, emptyVector);
    vector <vector<int>> girlPreferences(numCouples, emptyVector);

    //input boy and girl names
    for (int i = 0; i < numCouples; i++) {
        cout << "Please input Boy #" << i+1 << "'s name: (first names only please)" << endl;
        cin >> temp;
        boyNames.push_back(temp);
    }
    for (int i = 0; i < numCouples; i++) {
        cout << "Please input Girl #" << i + 1 << "'s name: (first names only please)" << endl;
        cin >> temp;
        girlNames.push_back(temp);
    }
    cout << endl;
    cin.ignore();

    //input preferences
    for (int i = 0; i < numCouples; i++) {
        cout << "Enter the preference list for "<< boyNames.at(i) << ": (delimited by spaces using a permutation of numbers 1, 2, 3, 4, ..n where n represetns the nth girl inputted, highest preference first)" << endl;
        getline(cin, temp);
        stringstream iss(temp);
        int number;
        while (iss >> number)
        {
            boyPreferences[i].push_back(number);
        }
    }
    for (int i = 0; i < numCouples; i++) {
        cout << "Enter the preference list for " << girlNames.at(i) << ": (delimited by spaces using a permutation of numbers 1, 2, 3, 4, ..n where n represetns the nth boy inputted, highest preference first)" << endl;
        getline(cin, temp);
        stringstream iss(temp);
        int number;
        while (iss >> number)
        {
            girlPreferences[i].push_back(number);
        }
    }

    //print preference tables
    printBoyPreferencesTable(boyPreferences, boyNames, girlNames);
    printGirlPreferencesTable(girlPreferences, boyNames, girlNames);

    //START GALE-SHAPELY ALGORITHM SECTION -----------------------------------------------------------------------------------------------------------------------------------------------------------------

    //make people and couples for algorithm
    person emptyPerson;
    couple emptyCouple;
    vector<person> Boys(numCouples, emptyPerson);
    vector<person> Girls(numCouples, emptyPerson);
    vector<couple> Couples(numCouples, emptyCouple); //edges

    //populate Boys
    for (int i = 0; i < numCouples; i++) {
        Boys.at(i).preferences = boyPreferences[i];
        Boys.at(i).id = i;
    }

    //populate Girls
    for (int i = 0; i < numCouples; i++) {
        Girls.at(i).preferences = girlPreferences[i];
        Girls.at(i).id = i; 
    }

    //put all girls in a couple ******** Note: girls and couples will always have the same index *************
    for (int i = 0; i < numCouples; i++) {
        Couples.at(i).girl = Girls.at(i);
    }
    
    //Gale-Shapley Algorithm
    bool isDone = false;
    while (!isDone) {
        for (int i = 0; i < Boys.size(); i++) {
            //some boy b is unmatched and hasn’t proposed to every girl
            if (Boys.at(i).isFree && Boys.at(i).preferenceIndex < Girls.size()) { 
                //first girl on boy’s list to whom b has not yet proposed
                int girlIndex = Boys.at(i).preferences.at(Boys.at(i).preferenceIndex) - 1; 
                //girl is unmatched
                if (Couples.at(girlIndex).girl.isFree) {
                    Boys.at(i).isFree = false;
                    Couples.at(girlIndex).boy = Boys.at(i);
                    Couples.at(girlIndex).girl.isFree = false;
                }
                else {
                    //checks to see who is higher on the preference list (poorly optimized for scale but I see no requirement for this being optimized anywhere)
                    for (int j = 0; j < Girls.at(girlIndex).preferences.size(); j++) {
                        //g prefers b to current partner b’ 
                        if (Girls.at(girlIndex).preferences.at(j) - 1 == Boys.at(i).id) {
                            Boys.at(Couples.at(girlIndex).boy.id).isFree = true; // ditches currently coupled boy
                            Boys.at(Couples.at(girlIndex).boy.id).preferenceIndex += 1;
                            Boys.at(i).isFree = false;
                            Couples.at(girlIndex).boy = Boys.at(i); //couples with boy who just proposed
                            break; //exit for loop
                        }
                        //g prefers current partner b’  to b
                        else if (Girls.at(girlIndex).preferences.at(j) - 1 == Couples.at(girlIndex).boy.id) {
                            Boys.at(i).preferenceIndex += 1; // rejects boy who proposed
                            break; //exit for loop
                        }
                    }
                }
                
            }
        }
        //checks to see if done with algorithm
        isDone = true;
        for (int i = 0; i < Boys.size(); i++) {
            if (Boys.at(i).isFree && Boys.at(i).preferenceIndex < Girls.size()) {
                isDone = false;
            }
        }
    }

    //print happy couples
    cout << endl << "Printing final happy couple relations.............................." << endl;
    for (int i = 0; i < Couples.size(); i++) {
        cout << "( " << boyNames.at(Couples.at(i).boy.id) << ", " << girlNames.at(Couples.at(i).girl.id) << " )" << endl;
    }

}
