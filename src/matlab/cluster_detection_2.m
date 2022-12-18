function [X_clusters, X] = cluster_detection_2(X, epsilon, points_cluster)
    [nb_dim, nb_points] = size(X);
    
    X_clusters = zeros(nb_dim+1, nb_points);
    numero_cluster = 1;
    count = 1;
    i = 1;
    while i < nb_points-count
        nb_points_cluster = 1;
        X_clusters_int = zeros(nb_dim, nb_points);
        X_clusters_int(:, 1) = X(:,i);
        X(:,i) = [];
        count = count+1;
        nb_points_cluster = nb_points_cluster+1;
        [X_clusters_int,X,count,nb_points_cluster,numero_cluster] = sous_cluster_detection_2(i, ...
                    count,epsilon,numero_cluster,nb_points_cluster,nb_dim,nb_points, ...
                    X,X_clusters_int,X_clusters_int(:,1));
        
        if nb_points_cluster >= points_cluster
            while nb_points_cluster > 1
                X_clusters(:,count-nb_points_cluster+1) = cat(1, X_clusters_int(:, nb_points_cluster-1), numero_cluster);
                nb_points_cluster = nb_points_cluster-1;
            end
            numero_cluster = numero_cluster+1;
        else
            i = i+nb_points_cluster;
            count = count - nb_points_cluster;
            while nb_points_cluster > 0
                X = cat(2, X_clusters_int(:, nb_points_cluster), X);
                nb_points_cluster = nb_points_cluster -1;
            end
        end
    end
end