#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <faiss/Clustering.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		cerr << "Usage: ./run_kmeans k d n inputfile" << endl;
		return EXIT_FAILURE;
	}
	int k = atoi(argv[1]);
	int d = atoi(argv[2]);
	int n = atoi(argv[3]);
	ifstream input(argv[4]);

	string number_str;
	float *training_set = (float *)malloc(sizeof(float) * d * n);
	float *centroids = (float *)malloc(sizeof(float) * k * n);
	int idx = 0;
	while (getline(input, number_str, ','))
	{
		training_set[idx++] = stoi(number_str);
		for (int i = 1; i < d - 1; ++i)
		{
			getline(input, number_str, ',');
			training_set[idx++] = stoi(number_str);
		}
		getline(input, number_str);
		training_set[idx++] = stoi(number_str);
	}

	cout << "Running kmeans" << endl;
	faiss::kmeans_clustering(d, n, k, training_set, centroids);

	ofstream centroids_out("centroids.txt");
	for (int i = 0; i < k; ++i)
	{
		for (int j = 0; j < d - 1; ++j)
			centroids_out << centroids[i * d + j] << ",";
		centroids_out << centroids[i * d + d - 1] << endl;
	}

	return EXIT_SUCCESS;
}
