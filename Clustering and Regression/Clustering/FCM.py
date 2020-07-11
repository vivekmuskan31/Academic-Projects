import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import cdist


def fcm(data, n_clusters=1, n_init=30, m=2, max_iter=300, tol=1e-16):

    for iter_init in range(n_init):

        # Randomly initialize centers
        centers = data[np.random.choice(
            data.shape[0], size=n_clusters, replace=False
            ), :]

        # Compute initial distances
        # Zeros are replaced by eps to avoid division issues
        dist = np.fmax(
            cdist(centers, data, metric='sqeuclidean'),
            np.finfo(np.float64).eps
        )

        for iter1 in range(max_iter):

            # Compute memberships       
            u = (1 / dist) ** (1 / (m-1))
            um = (u / u.sum(axis=0))**m

            # Recompute centers
            prev_centers = centers
            centers = um.dot(data) / um.sum(axis=1)[:, None]

            dist = cdist(centers, data, metric='sqeuclidean')

            if np.linalg.norm(centers - prev_centers) < tol:
                break

    return centers

data = np.random.randn(1000,100)

fcm(data, 3, 30, 2, 200)