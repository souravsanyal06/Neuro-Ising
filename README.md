# Neuro-Ising
Acelerating Travelling Salesman Problems via Graph Neural Network guided localized Ising Solvers

This work divides a Travelling Salesman Problem(TSP) by applying clustering to divide it into two systems
  1) Neuro Layer -- consisting of cluster centroids
  2) Ising Layer -- consisting of the clusters themselves
  
The Neuro Layer uses a Graph Neural Network (GNN) to generate TSP solutions of the cluster centroids.

The Ising Layer is implemented in C++ and the following source files are in the directory Ising_Layer.
ising is the executable in root directory, which is copied there after generating from Ising_Layer.
For each cluster, an Ising solver is invoked to obtain within-cluster local tours.

gen_cluster.ipynb is responsible for clustering and visualizing the clusters.

main.ipynb generates the final TSP Solution.

Before starting

create a directory called tsplib in the root, and add the tsp .txt benchmark files inside it.

Inside Neuro_Layer/

create a directory called tsp-models/
Inside it you can store your trained models. 
Pretrained models can be downloaded from https://drive.google.com/file/d/1qmk1_5a8XT_hrOV_i3uHM9tMVnZBFEAF/view 

Extract the .tar.gz file and place each directory in the /logs directory. 


# If you find this code useful, please cite the following paper:

S. Sanyal and K. Roy, "Neuro-Ising: Accelerating Large-Scale Traveling Salesman Problems via Graph Neural Network Guided Localized Ising Solvers," in IEEE Transactions on Computer-Aided Design of Integrated Circuits and Systems, vol. 41, no. 12, pp. 5408-5420, Dec. 2022, doi: 10.1109/TCAD.2022.3164330.

https://ieeexplore.ieee.org/abstract/document/9747927


