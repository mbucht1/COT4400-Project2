#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <iterator>
using namespace std;

const string sample = "sample.txt";
const string sampleInput = "sample-input.txt";
const string smallInput = "small-input.txt";
const string complexInput = "complex-input.txt";
const string sampleOutput = "sample-output.txt";
const string smallOutput = "small-output.txt";
const string complexOutput = "complex-output.txt";




void readInFile(string filename, vector<double>& seq1, vector<double>& seq2, vector<double>& target){
    ifstream input(filename);
    string sizes;
    string elem;
    string space = " ";
    string newLine = "\n";
    getline(input, sizes);
    string seq1Size = sizes.substr(0, sizes.find(space)); 
    string seq2Size = sizes.substr(sizes.find(space), sizes.find(newLine)); 
    int n = stoi(seq1Size);
    int m = stoi(seq2Size);
    vector<double> arr;
    if(!input.is_open()){
        cout << "Error opening file.\n";
        return;
    }
    for(int i = 0; !input.eof(); i++){
        input >> elem;
        arr.push_back(stod(elem));
    }
    seq1.assign(arr.begin(), arr.begin() + n);
    seq2.assign(arr.begin() + n, arr.begin() + n + m);
    target.assign(arr.begin() + n + m, arr.end() - 1);
    input.close();
}

void writeToFile(string filename, vector<double>& solution){
    ofstream output(filename);
    if(!output.is_open()){
        cout << "Error opening file.\n";
        return;
    }
    output << solution[0] << "\n";
    for(int i = 1; i < solution.size(); i++){
        output << solution[i] << " ";
    }
    output << "\n";
    output.close();
}

void iterSoln(vector<double> &seq1, vector<double> &seq2, vector<double> &target, vector<double> solution, int n, int m);




void Solver(string filename){

    vector<double> seq1, seq2, target, solution;
    readInFile(filename, seq1, seq2, target);
    int n = seq1.size();
    int m = seq2.size();
    iterSoln(seq1, seq2, target, solution, n, m);
    writeToFile("output.txt", solution);

    

}


int main(){

    vector<double> seq1;
    vector<double> seq2;
    vector<double> target;
    vector<double> solution;

    solution.push_back(1);
    solution.push_back(1);
    solution.push_back(2);
    solution.push_back(1);
    solution.push_back(3);
    solution.push_back(7);
    solution.push_back(6);

    readInFile(complexInput, seq1, seq2, target);
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
  
    writeToFile(sampleOutput, solution);

    return 0;
}