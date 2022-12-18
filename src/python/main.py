from functions import *
import matplotlib.pyplot as plt

# Dataset generation (two concentric circles)
N = 250
mu_1 = 0.5; sigma_1 = 0.01
mu_2 = 1; sigma_2 = 0.01

data = []
for n in range(1, N+1):
    r_1 = sigma_1*np.random.randn()+mu_1
    r_2 = sigma_2*np.random.randn()+mu_2

    theta_1 = np.random.randint(0, 360)*np.pi/180
    theta_2 = np.random.randint(0, 360)*np.pi/180

    x_1 = r_1*np.cos(theta_1); y_1 = r_1*np.sin(theta_1)
    x_2 = r_2*np.cos(theta_2); y_2 = r_2*np.sin(theta_2)

    data.append([x_1, y_1])
    data.append([x_2, y_2])

# DBSCAN algorithm
epsilon = 0.2; min_pts = 2
clusters_dbscan, noises_dbscan = dbscan(data, epsilon, min_pts)

for data_id in range(len(data)):
    del data[data_id][-1]

# K-means algorithm
K = 2
clusters_k_means = k_means(data, K)

colors = ["blue", "orange", "green", "red", "purple", "brown", "pink", "gray", "olive", "cyan"]

# Results display
fig, axs = plt.subplots(1, 2)

plt.subplot(1, 2, 1)
ax = axs.flat[0]
for n in noises_dbscan:
    plt.plot(n[0], n[1], marker = "o", color = "k", markersize = 4)
for k in list(clusters_dbscan.keys()):
    for pts in clusters_dbscan[k]:
        plt.plot(pts[0], pts[1], marker = "o", color = colors[k-1], markersize = 4)
        ax.add_artist(plt.Circle((pts[0], pts[1]), epsilon, alpha = 0.1, color = colors[k-1]))
plt.title("DBSCAN")
plt.grid()

plt.subplot(1, 2, 2)
for k in list(clusters_k_means.keys()):
    for pts in clusters_k_means[k]:
        plt.plot(pts[0], pts[1], marker = "o", color = colors[k-1], markersize = 4)
plt.title("K-means")
plt.grid()

plt.show()