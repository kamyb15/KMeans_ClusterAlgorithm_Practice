#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

struct Point {
    double x, y;
};

// Function to calculate Euclidean distance between two points
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Function to assign data points to clusters based on their distances to centroids
void assign_clusters(vector<Point>& data, vector<Point>& centroids, vector<int>& clusters) {
    for (int i = 0; i < data.size(); ++i) {
        double min_dist = numeric_limits<double>::max();
        int min_index = 0;
        for (int j = 0; j < centroids.size(); ++j) {
            double dist = distance(data[i], centroids[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_index = j;
            }
        }
        clusters[i] = min_index;
    }
}

// Function to update centroids based on cluster assignments
void update_centroids(vector<Point>& data, vector<Point>& centroids, vector<int>& clusters) {
    int num_clusters = centroids.size();
    vector<int> cluster_sizes(num_clusters, 0);

    for (int i = 0; i < data.size(); ++i) {
        int cluster_index = clusters[i];
        centroids[cluster_index].x += data[i].x;
        centroids[cluster_index].y += data[i].y;
        cluster_sizes[cluster_index]++;
    }

    for (int i = 0; i < num_clusters; ++i) {
        if (cluster_sizes[i] > 0) {
            centroids[i].x /= cluster_sizes[i];
            centroids[i].y /= cluster_sizes[i];
        }
    }
}

int main() {
    // Sample data
    vector<Point> data = {{1, 2}, {2, 3}, {4, 5}, {5, 4}, {3, 3}, {6, 7}, {7, 8}, {8, 9}};

    // Initialize centroids randomly
    int num_clusters = 2;
    vector<Point> centroids(num_clusters);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0, 10);
    for (int i = 0; i < num_clusters; ++i) {
        centroids[i].x = dist(gen);
        centroids[i].y = dist(gen);
    }

    // K-Means algorithm
    vector<int> clusters(data.size());
    int num_iterations = 10;
    for (int i = 0; i < num_iterations; ++i) {
        assign_clusters(data, centroids, clusters);
        update_centroids(data, centroids, clusters);
    }

    // Print cluster assignments
    for (int i = 0; i < data.size(); ++i) {
        cout << "Data point (" << data[i].x << ", " << data[i].y << ") belongs to cluster " << clusters[i] << endl;
    }

    return 0;
}