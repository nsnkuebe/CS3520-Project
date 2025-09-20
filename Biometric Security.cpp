#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

// Simulate captured face feature vector
std::vector<float> captureFaceFeatures() {
    std::vector<float> features(128); // 128-d feature vector (common size)
    for (auto& f : features) f = static_cast<float>(rand()) / RAND_MAX;
    return features;
}

// Cosine similarity between two feature vectors
float cosineSimilarity(const std::vector<float>& a, const std::vector<float>& b) {
    float dot = 0.0f, normA = 0.0f, normB = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        dot += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }
    return dot / (std::sqrt(normA) * std::sqrt(normB));
}

int main() {
    auto enrolled = captureFaceFeatures(); // Stored template
    auto current  = captureFaceFeatures(); // New scan

    float similarity = cosineSimilarity(enrolled, current);

    std::cout << "Cosine Similarity: " << similarity << std::endl;
    if (similarity > 0.8f) {
        std::cout << "Authentication Successful\n";
    } else {
        std::cout << "Authentication Failed\n";
    }

    return 0;
}
