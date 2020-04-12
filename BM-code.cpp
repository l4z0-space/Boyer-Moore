#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

                        // Boyer-Moore Algorithm

vector<int>matches;  // Store the matching positions here.
vector<string>steps; // Store all the steps here.
int badChar[256];

void badCharH(string word){
    int sz = (int)word.length();

    for(int i=0;i<256;i++) // all possible chars
        badChar[i]=-1;

    for(int i=0;i<sz;i++)
        badChar[(int)word[i]]=i;
}

string spaces(int n){
    string toReturn="";
    while(n--)toReturn+=" ";
    return toReturn;
}

void searchBM(string text, string pattern){

    int n = text.length();
    int m = pattern.length();

    badCharH(pattern);
    int shift = 0, remain = n - m;

    while( shift <= remain ){

        int j = m - 1;

        while( j >= 0 && pattern[j] == text[ shift + j ]) j--;

        string currStep = "";

        if(j<0){
            currStep += "\t\t > Match at index " + to_string(shift) + "\n";
            currStep += "\t\t" + text + "\n\t\t" + spaces(shift) + pattern;

            matches.push_back(shift);  // add the match and step
            steps.push_back(currStep); // check if arrived in the end of text

            if( shift + m < n ) shift += m - badChar[ text [ shift + m ] ];
            else shift++;
        }

        else{
            shift += max(1, j - badChar[ text [ shift + j ] ]);
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

    toSteps << "\nSteps below\n\t ...";
    for( string step : steps ){
        toSteps << "\n\n" << step;
    }
    toSteps << "\n\n ******* End of steps *******\n\n";

    cout << "\n * Files \'steps.txt\' and \'illustrator.txt\' created! *\n";

    toSteps.close();
    return 0;
}
