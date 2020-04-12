#include <iostream>
#include <vector>
#include <string>
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

    int shift = 0, remain = n-m;

    while(shift<=remain){

        int j = m-1;

        while( j>=0 && pattern[j] == text[shift+j]) j--;

        if(j<0){
            string currStep="";
          //  cout << "\n\n";
            currStep += "\t\t > Match at index "+to_string(shift)+"\n";
            currStep += "\t\t"+text+"\n\t\t" + spaces(shift) + pattern;
           // cout << currStep << "\n";

            // add the match and step
            matches.push_back(shift);
            steps.push_back(currStep);
            // check if arrived in the end of text
            if( shift + m < n ) shift += m - badChar[ text [ shift + m ] ];
            else shift++;
        }

        else{
            string currStep="";
            shift += max(1, j - badChar[ text [ shift + j ] ]);
            //cout<<"\n\n";
            currStep += " > Shift to index "+to_string(shift)+"\n"+ text+"\n"+spaces(shift)+pattern;
            //cout<<currStep;
            steps.push_back(currStep);
        }
    }
    cout<<"> Search finished...\n\n";

}


int main(){
    //freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    string text,pattern;
    do{
        cerr << "\n > Enter the text: ";       getline(cin,text);
        cerr << "\n > Enter the pattern: ";    getline(cin,pattern);

        if(text.length() < pattern.length())
            cerr << "\nPattern length is greater than text...\n\n";

    }while( text.length() < pattern.length() );

    cout << "\n -> Boyer-Moore Algorithm illustration <-\n\n";
    cout << "******* Program starts here *******\n\n";
    cout << "\tText: " << text << "\n";
    cout << "\tPattern: " << pattern << "\n\n";
    // call Bayer-Moore Algorithm
    searchBM(text,pattern);

    int totalMatches = (int)matches.size();

    if( totalMatches == 0 )
        cout << "No matches for the pattern \'" << pattern << "\'\n";

    else{

        for(int i=0;i<=(int)text.length();i++) cout << "- "; cout << endl;

        cout << "Pattern \'" << pattern << "\' occurs " << totalMatches << " time(s) in the text.\n";
        cout << "Position(s): ";

        for( int x : matches )cout << x << " ";

        cout << "\n\n\n> Matching Position(s) below...";
        cout << "\n\n\t\t" << text << "\n";

        int it = 1;
        for( int x : matches ){
            cout<<"\t\t" << spaces(x) << pattern << "\n";
        }
        for( int i=0 ; i <=(int)text.length(); i++ ) cout << "- " ; cout << endl;
    }



    string choice;
    cerr << "\n > Show all steps (Y/N): ";
    bool showSteps=0;
    while(true){

        cin >> choice;
        if( choice == "Y" ){ showSteps=1; break;}
        if( choice == "N" )break;
        else cerr << "\nEnter Y or N > ";
    }

    if( choice == "Y" ){
        cout<<"\nSteps below...";
        for( string step : steps ){
            cout << "\n\n" << step;
        }
        cout << "\n\n ******* End of steps *******\n\n";
        cerr << "\n * Steps successfully added in the end of the output file! *\n";
    }
    return 0;
}
