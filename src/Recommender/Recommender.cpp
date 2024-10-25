#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include "Recommender.h"

using namespace std;


void NearestNeighbour::vectorizer(const string& fPath) {
    ifstream file(fPath);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line, movieId, movieTitle, movieTags;
    int index = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        
        // Extract movie_id, title, and tags from the CSV
        getline(ss, movieId, ',');  // Read movie_id 
        getline(ss, movieTitle, ',');  // Read movie title
        getline(ss, movieTags, ',');  // Read movie tags/description

        movies.push_back(movieTitle);  // Store the movie title

        stringstream descStream(movieTags);
        string word;
        vector<int> wordVector(wordIndex.size(), 0);  // Initialize the bag-of-words vector

        // Tokenize the movie description (tags)
        while (descStream >> word) {
            if (wordIndex.find(word) == wordIndex.end()) {
                // New word, assign an index and expand all word vectors
                wordIndex[word] = index++;
                for (auto &vec : bagOfWords) {
                    vec.push_back(0);  // Add new element for existing vectors
                }
                wordVector.push_back(1);
            } else {
                // Word already exists, update its count in the vector
                wordVector[wordIndex[word]]++;
            }
        }

        // Add the vectorized tags for this movie to the bagOfWords
        bagOfWords.push_back(wordVector);
    }

    file.close();
}

float NearestNeighbour::cosineSimilarity(const vector<int>& vec1, const vector<int>& vec2) {
    float dotProduct = 0.0, magnitude1 = 0.0, magnitude2 = 0.0;

    for (size_t i = 0; i < vec1.size(); ++i) {
        dotProduct += vec1[i] * vec2[i];
        magnitude1 += vec1[i] * vec1[i];
        magnitude2 += vec2[i] * vec2[i];
    }

    float denominator = sqrt(magnitude1) * sqrt(magnitude2);
    return (denominator == 0) ? 0 : (dotProduct / denominator);  // Avoid division by zero
}


void NearestNeighbour::recommendMovies(const string& movieTitle) {
    auto it = find(movies.begin(), movies.end(), movieTitle);
    if (it == movies.end()) {
        cout << "Movie not found!" << endl;
        return;
    }

    // Get index of the input movie
    int movieIndex = distance(movies.begin(), it);
    vector<int> movieVec = bagOfWords[movieIndex];

    vector<pair<float, string>> similarityScores;

    // Compute similarity with all other movies
    for (size_t i = 0; i < movies.size(); ++i) {
        if (i != movieIndex) {
            float similarity = cosineSimilarity(movieVec, bagOfWords[i]);
            similarityScores.push_back(make_pair(similarity, movies[i]));
        }
    }

    // Sort based on similarity in descending order
    sort(similarityScores.begin(), similarityScores.end(), greater<>());

    // Display top 5 recommendations
    cout << "Top 5 recommended movies similar to '" << movieTitle << "':" << endl;
    for (int i = 0; i < 5 && i < similarityScores.size(); ++i) {
        cout << similarityScores[i].second << " (Similarity: " << similarityScores[i].first << ")" << endl;
    }
}


int main() {
    NearestNeighbour nn;
    
    // Path to the dataset file
    nn.vectorizer("mov.csv");

    // Recommend movies similar to a given title
    nn.recommendMovies("Fight Club");

    return 0;
}
