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
        for (int i = 0; i < s.length(); i++) {
            switch (s.at(i)) {
                case '0': e.push_back(0);
                case '1': e.push_back(1);
                case '?': e.push_back(-1);
                case '\t': ;
            }
        }
        studentRatings[j] = e;
    }

    for (auto it = studentRatings.begin(); it != studentRatings.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++)
            cout << *it2 << " ";
        cout << endl;
    }
}
