/*
 * Author: Nabi Ozberkman
 * Filename: em.cpp
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


long double calculateLog(vector<long double>& arr, vector<vector<int> >& arr2, vector<int>& arr3, int n) {
    long double total = 0.0;
    long double total2 = 0.0;
    long double totalF = 0.0;
    int mistakes = 0;
    for (int j = 0; j < arr2.size(); j++) {
        long double cpt = 1.0;
        for (int i = 0; i < n; i++) {
            cpt *= pow(1.0 - arr[i], arr2[j][i]);
            //cpt2 += long double((1 - arr3[j]) * arr2[j][i]) * log(arr[i]);
        }
        cpt = 1 - cpt;
        if ((cpt >= 0.5 && arr3[j] == 0) || (arr3[j] == 1 && cpt <= 0.5))
            mistakes++;
        total = double(arr3[j]) * log(cpt);
        cpt = 1 - cpt;
        total2 = double(1-arr3[j]) * log(cpt);
        totalF += total + total2;
    }
    cout << mistakes << " Log Likelihood: ";
    return ((totalF) / double(arr2.size()));
}

int main(int argc, char* agrv[]) {
    ifstream xFile, yFile;
    string line;
    vector<vector<int > > xArr;
    vector<int> yArr;

    xFile.open("x.txt");
    yFile.open("y.txt");

    int n = 23;
    int T = 267;
    int x, y;

    for (int j = 0; j < T; j++) {
        vector<int> k;
        for (int i = 0; i < n; i++) {
            xFile >> x;
            k.push_back(x);
            if (xFile.eof()) {
                goto end;
            }
        }
        yFile >> y;
        yArr.push_back(y);
        xArr.push_back(k);
    }
end:;

    vector<long double> probArr(n, 0.05);
    int numIt = 512;

    for (int it = 0; it < numIt; it++) {
        vector<long double> prob2Arr;
        for (int i = 0; i < n; i++) {
            int t = 0;
            long double total = 0;
            long double numerator = 0;
            long double count = 0;
            for (auto iter = xArr.begin(); iter != xArr.end(); iter++) {
                if ((*iter)[i] == 1)
                    count += 1.0;
                numerator = double(yArr[t] * (*iter)[i]) * probArr[i];
                long double denominator = 1.0;
                for (int j = 0; j < n; j++) {
                    denominator *= pow((1.0 - probArr[j]), (*iter)[j]);
                }
                denominator = 1.0 - denominator;
                t++;
                total += numerator / denominator;
            }
            prob2Arr.push_back(total / count); 
        }
        //calculateLog(probArr, xArr, n);
        cout << "Iteration: " << it << " Mistakes: "<<calculateLog(probArr, xArr, yArr, n) << endl;
        probArr = prob2Arr;
    }
    cout << "Iteration: " << 512 << " Mistakes: "<<calculateLog(probArr, xArr, yArr, n) << endl;

    int l = 1;
    for (auto it = probArr.begin(); it != probArr.end(); it++) {
        cout << "p_" << l << " = " << *it << endl; 
        l++;
    }
}
