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


// Reading from a file to get the seq1, seq2 and target values
void readInFile(string filename, vector<double>& seq1, vector<double>& seq2, vector<double>& target) {
    ifstream ifile;
    ifile.open(filename);
    //if reading file gives error, return does not exist
    if (!ifile){
    cout << "File name: " << filename << " does not exist" << endl;
    exit(1);
    }

    int n,m;
    double t;
    //writing to numbers for size of the arrays
    ifile >> n;
    ifile >> m;

    //for loop to get the seq1
    for (int i = 0; i <n; i++){
        ifile >> t;
        seq1.push_back(t);
    }
    //for loop to get the seq2
    for (int i = 0; i <m; i++){
        ifile >> t;
        seq2.push_back(t);
    }
    //for loop to get the target
    for (int i = 0; i <n+m; i++){
        ifile >> t;
        target.push_back(t);
    }
}

//writing the solution to output file
void writeToFile(string filename, vector<double>& solution, int n, int m){
    ofstream output(filename);
    //if file gives error, return couldnt open the file
    if(!output.is_open()){
        cout << "Error opening file.\n";
        return;
    }
    output << solution[0] << "\n";
    //for loop to copy the solution into output file
    for(int i = 1; i < n+m+1; i++){
        output << solution[i] << " ";
    }
    output << "\n";
    output.close();
}
//main function to get the solution based on sequences and target
void iterSoln(vector<double> &seq1, vector<double> &seq2, vector<double> &target, vector<double> &solution, int n, int m){

    vector<vector <double> > arr;
    vector<vector<int> > arr2;
    //loop searching through the arrays to find the correct decision
    for (int i = 0; i <= n; i++){
        arr.push_back(vector<double>());
        arr2.push_back(vector<int>());
        for (int j = 0; j <= m; j++){
            arr[i].push_back(-1);
            arr2[i].push_back(-1);
        }
    }

    int k;
    //for loop getting every number for solution based on target and sequences
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
    //pushing back the solution for final answer
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
    //creating the vectors so the answers can be get done
    vector<double> seq1;
    vector<double> seq2;
    vector<double> target;
    vector<double> solution;

    //reding the file
    readInFile("input.txt", seq1, seq2, target);

    /setting the size of arrays
    int n = seq1.size();
    int m = seq2.size();

    //getting the solution
    iterSoln(seq1, seq2, target, solution,n,m);
    
    //writing the solution to file
    writeToFile("output.txt", solution, n, m);

    return 0;
}