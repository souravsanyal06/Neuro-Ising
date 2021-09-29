# Neuro-Ising
Acelerating Travelling Salesman Problems via Graph Neural Network guided localized Ising Solvers

This work divides a Travelling Salesman Problem(TSP) by applying clustering to divide it into two systems
  1) Neuro Layer -- consisting of cluster centroids
  2) Ising Layer -- consisting of the clusters themselves
  
The Neuro Layer is built on top of the repo https://github.com/chaitjo/graph-convnet-tsp, which uses a Graph Neural Network (GNN) to generate TSP solutions of the cluster centroids.

The Ising Layer is implemented in C++ and the following source files are in the directory Ising_Layer.
ising is the executable in root directory, which is copied there after generating from Ising_Layer.
For each cluster, an Ising solver is invoked to obtain within-cluster local tours.

gen_cluster.ipynb is responsible for clustering and visualizing the clusters.

main.ipynb generates the final TSP Solution.


