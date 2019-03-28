//memory requirement: O(n)
//time requirement: O(n^2)

#include <limits.h> 
#include <stdio.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
#define INF INT_MAX 
using namespace std;


int print(int p[], int n, vector<string> &words, string& result){ //gets all necessary info to output the neccessary info
    int x = 0;
    int count;
    int cost = 0;
    while (x < n){
        count = 0;
        for(int y = (x); y <= (p[x]); y++){
            result += words[y] + " ";
            count += words[y].length() + 1;
        }
	result = result.substr(0, result.size()-1); //cant use pop_back because afs is on an older version of G++ compiler
        x = p[x] + 1;
        if(x < n){
        cost += pow(60 - (count-1),3);
        result += '\n';
        }       
    }
    return cost;
}
  
void solveProblem (vector<int> &lengths, int n, int M, vector<string> &words) 
{ 
    
    int i, j; 
    int cLength; 
    int cost;   //variables for current length, cost, and the i j iterators used to iterate through the words
    int costAr[n];
    int answer[n]; //new arrays for the cost of the current word to word J, and the minimum cost (answer)
    costAr[n - 1] = 0; 
    answer[n - 1] = n - 1; 
    for (i = n - 2; i >= 0; i--) { 
        cLength = -1; 
        costAr[i] = INT_MAX; 
        for (j = i; j < n; j++) { //calcultes costs from words i to j until the current length is greater than M which is 60 for this application
            cLength += (lengths[j] + 1); 
            if (cLength > M) 
                break; 
            if (j == n - 1) 
                cost = 0; 
            else
                cost = (M - cLength) * (M - cLength) + costAr[j + 1];  
            if (cost < costAr[i]) { 
                costAr[i] = cost; 
                answer[i] = j; 
            } 
        } 
    } 
    string result = "";
    int finalcost = print(answer, n, words, result);
    ofstream out;
    out.open("zeffiro_answer");
    out << finalcost << endl << result;
    cout << "Answer output to file named \"zeffiro_answer\"" << endl; 
    
}
string slurp(ifstream& in) {
 
    return static_cast<stringstream const&>(stringstream() << in.rdbuf()).str();
}

int main(int argc,char *argv[] ) 
{ 
    if(argc < 2) {
    cout << "Pass a Filename as an argument" << endl;
    }

    ifstream file;
    file.open(argv[1]);
    string str = slurp(file);
    std::replace(str.begin(),str.end(),'\n',' ');
    stringstream s(str);
    string word;
    vector<int> lengths;
    vector<string> words;
    while(s >> word){
        lengths.push_back(word.length());
        words.push_back(word);
    }
    int n = lengths.size(); 
    int M = 60; 
    solveProblem(lengths, n, M, words); 
    return 0; 
} 
