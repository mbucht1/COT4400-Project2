#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <iterator>
#define INFINITY
#define DOWN     1
#define RIGHT    2
using namespace std;

const string sample = "sample.txt";
const string sampleInput = "sample-input.txt";
const string smallInput = "small-input.txt";
const string complexInput = "complex-input.txt";
const string sampleOutput = "sample-output.txt";
const string smallOutput = "small-output.txt";
const string complexOutput = "complex-output.txt";


void readInFile(string filename, vector<double>& seq1, vector<double>& seq2, vector<double>& target) {
    ifstream ifile;
    ifile.open(filename);
    if (!ifile){
    cout << "File name: " << filename << " does not exist" << endl;
    exit(1);
    }

    int n,m;
    double t;
    
    ifile >> n;
    ifile >> m;


    for (int i = 0; i <n; i++){
        ifile >> t;
        seq1.push_back(t);
    }

    for (int i = 0; i <m; i++){
        ifile >> t;
        seq2.push_back(t);
    }

    for (int i = 0; i <n+m; i++){
        ifile >> t;
        target.push_back(t);
    }
}


void writeToFile(string filename, vector<double>& solution, int n, int m){
    ofstream output(filename);
    if(!output.is_open()){
        cout << "Error opening file.\n";
        return;
    }
    output << solution[0] << "\n";
    for(int i = 1; i < n+m+1; i++){
        output << solution[i] << " ";
    }
    output << "\n";
    output.close();
}

void iterSoln(vector<double> &seq1, vector<double> &seq2, vector<double> &target, vector<double> &solution, int n, int m){

    vector<vector <double> > arr;
    vector<vector<int> > arr2;

    for (int i = 0; i <= n; i++){
        arr.push_back(vector<double>());
        arr2.push_back(vector<int>());
        for (int j = 0; j <= m; j++){
            arr[i].push_back(-1);
            arr2[i].push_back(-1);
        }
    }

    int k;
    for (int i = n; i >= 0; i--){
        k = i + m;
        for (int j = m; j >= 0; j--, k--){
            if (k == n+m){
                arr[i][j] = 0;
                arr2[i][j] = 0;
            } else if (i == n){
                arr[i][j] = (target[k] * seq2[j]) + arr[i][j+1];
                arr2[i][j] = DOWN;
            } else if (j == m){
                arr[i][j] = (target[k] * seq1[i]) + arr[i+1][j];
                arr2[i][j] = RIGHT;
            } else {
                double max1 = target[k] * seq1[i] + arr[i+1][j];
                double max2 = target[k] * seq2[j] + arr[i][j+1];
                if (max1 >= max2){
                    arr[i][j] = max1;
                    arr2[i][j] = RIGHT;

                } else{
                    arr[i][j] = max2;
                    arr2[i][j] = DOWN;
                }
            }
        }
    }

    int i =0, j = 0;
    solution.push_back(arr[0][0]);
    while (j+i <= n+m+1){
        if (arr2[i][j] == RIGHT){
            solution.push_back(seq1[i]);
            i++;
        } else{
            solution.push_back(seq2[j]);
            j++;
        }
    }
}



int main(){

    vector<double> seq1;
    vector<double> seq2;
    vector<double> target;
    vector<double> solution;

    readInFile("input.txt", seq1, seq2, target);


    int n = seq1.size();
    int m = seq2.size();

    iterSoln(seq1, seq2, target, solution,n,m);



//printing out solution for testing
    cout << "Sequence 1: ";
    for(int i = 0; i < seq1.size(); i++){
         cout << seq1[i] << " ";
    }
    cout << endl;
    cout << "Sequence 2: ";
    for(int i = 0; i < seq2.size(); i++){
         cout << seq2[i] << " ";
    }
    cout << endl;
    cout << "Target: ";
    for(int i = 0; i < target.size(); i++){
         cout << target[i] << " ";
    }
    cout << endl;

    cout << "Solution: ";
    cout << solution[0] << endl;
    for(int i = 1; i < n+m+1; i++){
         cout << solution[i] << " ";
    }
    cout << endl;

  
    writeToFile(sampleOutput, solution, n, m);

    return 0;
}