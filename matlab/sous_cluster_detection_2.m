function [X_clusters_int,X,count,nb_points_cluster,numero_cluster] = sous_cluster_detection_2(i,count, ...
    epsilon,numero_cluster,nb_points_cluster,nb_dim,nb_points,X,X_clusters_int,X_i)

    j = i;
    while j < nb_points-count+1
        [sum] = distance_eucli(X_i, X(:, j), nb_dim);
        if (sum <= epsilon)
            X_clusters_int(:, nb_points_cluster) = X(:,j);
            X(:, j) = [];
            nb_points_cluster = nb_points_cluster+1;
            count = count+1;
            [X_clusters_int,X,count,nb_points_cluster,numero_cluster] = sous_cluster_detection_2(i, ...
                count,epsilon,numero_cluster,nb_points_cluster,nb_dim,nb_points,X, ...
                X_clusters_int,X_clusters_int(:, nb_points_cluster-1));
        end
        j = j+1;
    end
end