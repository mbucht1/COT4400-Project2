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



//void readInFile(vector<double>& seq1, vector<double>& seq2, vector<double>& target){
void readInFile(string filename, vector<double>& seq1, vector<double>& seq2, vector<double>& target){
    //final program takes input from input.txt
    //string filename = "input.txt";
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

    cout << "Solution1: ";
    cout << solution[0] << endl;
    for(int i = 1; i < n+m+1; i++){
         cout << solution[i] << " ";
    }
    cout << endl;

}



int main(){

    vector<double> seq1;
    vector<double> seq2;
    vector<double> target;
    vector<double> solution;

    //readInFile(complexInput, seq1, seq2, target);
 
 /*
    //-0.2742 0.2195 0.0291 -0.1251 -0.1341 0.0184 0.2053 -0.0918 -0.1009 0.2517 -0.1632 0.0514 0.0419 0.3797 -0.2062
    seq1.push_back(-0.2742);
    seq1.push_back(0.2195);
    seq1.push_back(0.0291);
    seq1.push_back(-0.1251);
    seq1.push_back(-0.1341);
    seq1.push_back(0.0184);
    seq1.push_back(0.2053);
    seq1.push_back(-0.0918);
    seq1.push_back(-0.1009);
    seq1.push_back(0.2517);
    seq1.push_back(-0.1632);
    seq1.push_back(0.0514);
    seq1.push_back(0.0419);
    seq1.push_back(0.3797);
    seq1.push_back(-0.2062);


    //-0.4702 -0.2227 0.2929 0.0387 -0.0131 0.0689 0.1644 0.0365 -0.3298
    seq2.push_back(-0.4702);
    seq2.push_back(-0.2227);
    seq2.push_back(0.2929);
    seq2.push_back(0.0387);
    seq2.push_back(-0.0131);
    seq2.push_back(0.0689);
    seq2.push_back(0.1644);
    seq2.push_back(0.0365);
    seq2.push_back(-0.3298);

    //-0.1513 0.1748 0.0366 -0.0787 -0.5992 -0.0785 -0.1488 0.1381 0.0329 -0.0138 0.0870 0.0113 0.1329 
    //0.2018 -0.1088 -0.0484 0.0262 -0.4134 0.3257 -0.1048 0.0377 0.0532 0.3544 -0.1801
    target.push_back(-0.1513);
    target.push_back(0.1748);
    target.push_back(0.0366);
    target.push_back(-0.0787);
    target.push_back(-0.5992);
    target.push_back(-0.0785);
    target.push_back(-0.1488);
    target.push_back(0.1381);
    target.push_back(0.0329);
    target.push_back(-0.0138);
    target.push_back(0.0870);
    target.push_back(0.0113);
    target.push_back(0.1329);
    target.push_back(0.2018);
    target.push_back(-0.1088);
    target.push_back(-0.0484);
    target.push_back(0.0262);
    target.push_back(-0.4134);
    target.push_back(0.3257);
    target.push_back(-0.1048);
    target.push_back(0.0377);
    target.push_back(0.0532);
    target.push_back(0.3544);
    target.push_back(-0.1801);

    */



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

  
    //writeToFile(sampleOutput, solution);

    return 0;
}