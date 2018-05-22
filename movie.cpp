/*
 * Author: Nabi Ozberkman
 * Filename: movie.cpp
 */
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


int main(int argc, char* agrv[]) {
    ifstream movieNames, movieRatings;

    movieNames.open("titles.txt");
    movieRatings.open("ratings.txt");
    string k;
    vector<pair<string, int> > movies;

    while (!movieNames.eof()) {
        movieNames >> k;
        movies.push_back(make_pair(k, 0));
    }

    int studentCount = 117;
    int movieCount = 61;
    string s;
    vector<vector<int> > studentRatings(studentCount);
    for (int j = 0; j < studentCount; j++) {
        vector<int> e;
        getline(movieRatings, s);
        cout << s;
        cout << endl << endl;
        for (int i = 0; e.size() != movieCount; i++) {
          cout << s.at(i);
            switch (s.at(i)) {
                case '0': e.push_back(0);
                case '1': e.push_back(1);
                case '?': e.push_back(-1);
                default: ;
            }
        }
        studentRatings[j] = e;
        cout << endl << endl;
        break;
    }

    /*for (auto it = studentRatings.begin(); it != studentRatings.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
            cout << *it2 << " ";
        cout << endl;
    }*/

    for (auto it = studentRatings[0].begin(); it != studentRatings[0].end(); it++)
      cout << *it << '\t';
    cout << endl;
    cout << studentRatings[0].size() << endl;
}
