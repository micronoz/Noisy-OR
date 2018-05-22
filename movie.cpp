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


bool myCompare(pair<string, long double>& a, pair<string,long double>& b) {
    return a.second < b.second;
}
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
    string s = "";
    vector<vector<int> > studentRatings(studentCount);
    for (int j = 0; j < studentCount; j++) {
        vector<int> e(movieCount);
        int k = 0;
        getline(movieRatings, s);
        for (int i = 0; i < s.length(); i++) {
            switch (int(s.at(i))) {
                case 48: 
                    e[k++] = 0;
                    continue;
                case 49: 
                    e[k++] = 1;
                    continue;
                case 63: 
                    e[k++] = -1;
                    continue;
                default: 
                    continue;

            }
        }
        studentRatings[j] = e;
    }
    vector<long double> popularity(movieCount, 0.0);
    for (auto it = studentRatings.begin(); it != studentRatings.end(); it++) {
        int k = 0;
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            if (*it2 == 1)
                movies[k].second += *it2;
            if (*it2 == 0 || *it2 == 1)
                popularity[k] += 1.0;
            k++;
        }
    }
    vector<pair<string, long double> > moviePopularity(movieCount);
    for (int k = 0; k < movieCount; k++) {
        moviePopularity[k].second = double(movies[k].second) / popularity[k];
        moviePopularity[k].first = movies[k].first;
    }

    sort(moviePopularity.begin(), moviePopularity.end(), myCompare);

    for (auto it = moviePopularity.begin(); it != moviePopularity.end(); it++) {
        cout << it->first << endl;
    }

    int numIter = 128;

    ifstream file1("rgivenz.txt");

    int categories = 4;
    vector<vector<long double> > rGivenZ(categories);


    for (int i = 0; i < movieCount; i++) {
        for (int j = 0; j < categories; j++) {
            long double k;
            file1 >> k;
            rGivenZ[j].push_back(k);
        }
    }

    ifstream file2("z.txt");

    vector<long double> zProb;
    vector<long double> zProb2(categories);
    vector<long double> zProb3(categories);

    long double l;
    for (int i = 0; i < categories; i++) {
        file2 >> l;
        zProb.push_back(l);  
    }

    for (int i = 0; i < numIter+1; i++) {
    vector<vector<long double> > zProb4(studentCount);
        cout << "Iteration " << i << ": ";
        long double logLikelihood = 0.0;
        for (int t = 0; t < studentCount; t++) {
            long double total = 0.0;
            for (int j = 0; j < categories; j++) {
                long double multiplication = 1.0;
                for (int k = 0; k < studentRatings[t].size(); k++) {
                    switch (studentRatings[t][k]) {
                        case 1:
                            multiplication *= rGivenZ[j][k];
                            continue;
                        case 0:
                            multiplication *= 1 - rGivenZ[j][k];
                            continue;
                        default:
                            continue;
                    }
                }
                total += multiplication * zProb[j];
            }
            logLikelihood += log(total);
        }
        logLikelihood /= studentCount;
        cout << logLikelihood << endl;
        for (int t = 0; t < studentCount; t++) {
            long double total = 0.0;
            for (int j = 0; j < categories; j++) {
                long double multiplication = 1.0;
                for (int k = 0; k < studentRatings[t].size(); k++) {
                    switch (studentRatings[t][k]) {
                        case 1:
                            multiplication *= rGivenZ[j][k];
                            continue;
                        case 0:
                            multiplication *= 1 - rGivenZ[j][k];
                            continue;
                        case -1:
                            continue;
                    }
                }
                total += multiplication * zProb[j];
                zProb2[j] = multiplication * zProb[j];
            }

            for (int j = 0; j < categories; j++) {
                zProb2[j] /= total;
                zProb4[t].push_back(zProb2[j]);
            }
        }
        for (int j = 0; j < categories; j++) {
            long double x = 0.0;
            for (int t = 0; t < studentCount; t++) {
                x += zProb4[t][j];
            }
            zProb[j] = x/studentCount;
            //    cout << zProb[j] << '\t';
        }
        //cout << endl;
        vector<vector<long double> > rGivenZ2(categories);
        for (int m = 0; m < movieCount; m++) {
            for (int c = 0; c < categories; c++) {
                long double total1 = 0.0;
                long double total2 = 0.0;
                long double total3 = 0.0;
                for (int t = 0; t < studentCount; t++) {
                    switch(studentRatings[t][m]) {
                        case 1:
                            total1 += zProb4[t][c];
                            goto next;
                        case 0:
                            goto next;
                        case -1:
                            total2 += zProb4[t][c] * rGivenZ[c][m];
                            goto next;

                    }
next:
                    total3 += zProb4[t][c];
                }
                rGivenZ2[c].push_back((total1 + total2)/total3);
            }
        }
        rGivenZ = rGivenZ2;

        //for (auto it = rGivenZ[0].begin(); it != rGivenZ[0].end(); it++)
        //cout << *it << endl;

    }
}
