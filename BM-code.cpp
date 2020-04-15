#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;

                        // Boyer-Moore Algorithm

vector<int>matches;  // Store the matching positions here.
vector<string>steps; // Store all the steps here.
unordered_map<char,int> lastPos;

void prepTable(string pattern, string text){
    int it = 0;
    // Store last position of every character.
    for( char ch : text )
        lastPos[ch] = -1;
    for( char ch : pattern )
        lastPos[ch] = it++;
}

// Just a function to help in formating.
string spaces(int n){
    string toReturn = "";
    while(n--)toReturn += " ";
    return toReturn;
}

void searchBM(string text, string pattern){

    int n = text.length();
    int m = pattern.length();

    prepTable(pattern,text); // Prepare the table which helps shifting.
    int shift = 0, remain = n - m;

    while( shift <= remain ){

        int check = m - 1;

        while( check >= 0 && pattern[check] == text[ shift + check ]) check--; // Decrement [check] until a mismatch.

        string currStep = "";

        if(check<0){  // If check < 0 then we have a match.

            // Below lines for formating...
            currStep += "\t\t + Match at index " + to_string(shift) + "\n";
            currStep += "\t\t" + text + "\n\t\t" + spaces(shift) + pattern;

            // Add the match and step.
            matches.push_back(shift);
            steps.push_back(currStep);

            if( shift + m < n ) shift += m - lastPos[ text [ shift + m ] ]; // Shift by [m] - the value in [lastPos] table of mismatched char.
            else shift++;
        }

        else{

            shift += max(1, check - lastPos[ text [ shift + check ] ]);
            // Below lines used for formating...
            currStep += " > Shift to index " + to_string(shift) + "\n" + text + "\n" + spaces(shift) + pattern;
            steps.push_back(currStep);
        }
    }
}


int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    string text,pattern;
    do{
        cout << "\n > Enter the text: ";       getline(cin,text);
        cout << "\n > Enter the pattern: ";    getline(cin,pattern);

        if(text.length() < pattern.length())
            cerr << "\nPattern length is greater than text...\n\n";

    }while( text.length() < pattern.length() );

    ofstream toFile("illustrator.txt");

    toFile << "\n -> Boyer-Moore Algorithm illustration <-\n\n";
    toFile << "******* Program starts here *******\n\n";
    toFile << "\tText: " << text << "\n";
    toFile << "\tPattern: " << pattern << "\n\n";
    // call Bayer-Moore Algorithm
    searchBM(text,pattern);

    int totalMatches = (int)matches.size();

    if( totalMatches == 0 )
        toFile << "\n\n No matches for the pattern \'" << pattern << "\'\n";

    else{

        for(int i=0;i<=(int)text.length();i++) toFile << "- "; toFile << endl;

        toFile << "Pattern \'" << pattern << "\' occurs " << totalMatches << " time(s) in the text.\n";
        toFile << "Position(s): ";

        for( int x : matches )toFile << x << " ";

        toFile << "\n\n\n> Matching Position(s) below...";
        toFile << "\n\n\t\t" << text << "\n";

        int it = 1;
        for( int x : matches ){
            toFile<<"\t\t" << spaces(x) << pattern << "\n";
        }
        for( int i=0 ; i <=(int)text.length(); i++ ) toFile << "- " ; toFile << "\n";
    }

    toFile.close();

    ofstream toSteps("steps.txt"); // store here the steps



    // Prints the lastPos table [124-142]

    string toShow="";
    unordered_map<char,bool>usedChar;

    for( char ch : pattern){
        if( !usedChar[ch] )
            usedChar[ch] = 1,
            toShow += ch;
    }

    sort(toShow.begin(),toShow.end());
    toSteps << "\n\n + Last position table...\n\t\t\t\t\t\t|\t";
    for( char ch : toShow )
        toSteps << ch << "\t|\t";
    toSteps << "\n\t\t\t\t\t\t|\t";
    for( char ch : toShow )
        toSteps << lastPos[ch] << "\t|\t";



    toSteps << "\nSteps below\n\t ...";
    for( string step : steps ){
        toSteps << "\n\n" << step;
    }
    toSteps << "\n\n ******* End of steps *******\n\n";

    cout << "\n * Files \'steps.txt\' and \'illustrator.txt\' created! *\n";
    toSteps.close();

    return 0;
}
