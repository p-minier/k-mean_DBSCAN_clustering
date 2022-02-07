import numpy as np

# Functions related to the DBSCAN algorithm

def find_neighbours(data, center, epsilon):
    """Return the epsilon-neighborhood of center"""

    neighbours = []

    for element in data:
        if element is not center:
            distance = np.linalg.norm(np.array(center[:-1]) - np.array(element[:-1]))
            if distance <= epsilon:
                neighbours.append(element)

    return neighbours


def extend_cluster(data, core, core_neighbours, c, clusters, epsilon, min_pts):
    """Find all the elements that are density-connected via the cluster of core"""

    core[-1] = "cluster"
    clusters[c].append(core)

    for element in core_neighbours:
        if element[-1] == "unvisited":
            element_neighbours = find_neighbours(data, element, epsilon)

            if core in element_neighbours:
                element_neighbours.remove(core)

            if len(element_neighbours) >= min_pts:
                for new_element in element_neighbours:
                    if new_element not in core_neighbours:
                        core_neighbours.append(new_element)

        if element[-1] != "cluster":
            element[-1] = "cluster"
            clusters[c].append(element)


def dbscan(data, epsilon, min_pts):
    """Apply the DBSCAN algorithm to a dataset and return its clusters and noises"""

    N = len(data)

    for data_id in range(N):
        data[data_id].append("unvisited")

    clusters = {}
    noises = []

    c = 0
    for data_id in range(N):
        if data[data_id][-1] == "unvisited":
            neighbours = find_neighbours(data, data[data_id], epsilon)
            if len(neighbours) < min_pts:
                data[data_id][-1] = "noise"
                noises.append(data[data_id])
            else:
                c = c + 1
                clusters[c] = []
                extend_cluster(data, data[data_id], neighbours, c, clusters, epsilon, min_pts)
    
    return clusters, noises

# Function related to the K-means algorithm

def k_means(data, K):
    """Apply the K-means algorithm to a dataset and return its clusters"""

    (N, dimension) = np.shape(data)
    mu = np.random.rand(K, dimension)
    r = np.zeros([N, K])

    for n in range(N):
        euclidian_distances = np.zeros(K)

        argmin = 0
        min = np.linalg.norm(np.array(data[n]) - mu[argmin])**2

        for k in range(1, K):
            euclidian_distances[k] = np.linalg.norm(np.array(data[n]) - mu[k])**2
            if euclidian_distances[k] < min:
                argmin = k

        r[n][argmin] = 1

    for k in range(K):
        sum_numerator = np.zeros(dimension)
        sum_denominator = 0
        for n in range(N):
            sum_numerator = sum_numerator + r[n][k]*np.float64(data[n])
            sum_denominator = sum_denominator + r[n][k]
        
        mu[k] = sum_numerator/sum_denominator

    clusters = {}

    for k in range(1, K+1):
        clusters[k] = []
    for n in range(N):
        for k in range(K):
            if r[n][k] == 1.0:
                cluster_id = k+1
                clusters[cluster_id].append(data[n])

    return clusters