#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;


class NearestNeighbour {
    private:
        vector <string> movies;
        vector <vector<int>> bagOfWords;
        map <string, int> wordIndex;

    public:
        void vectorizer(const string &fPath);
        float cosineSimilarity(const vector<int> &vec1, const vector<int> &vec2);
        void recommendMovies(const string &movieTitle);

};