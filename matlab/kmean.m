function [X_clusters] = kmean(X,k)
    [nb_dim, nb_points] = size(X);
    index_points = randi([1 nb_points], 1, k);
    barycentres_points = zeros(nb_dim+1, k);
    
    X_clusters = zeros(nb_dim+1, nb_points);
    count = k+1;

    for i=1:1:k
        barycentres_points(:,i) = cat(1, X(:, index_points(i)), 1);
        X_clusters(:,i) = cat(1, X(:,index_points(i)), i);
        X(:, index_points(i)) = [];
    end

    i = 1;
    distance = zeros(2,k);

    while i<=nb_points-count+1
        for j = 1:1:k
            distance(:,j) = cat(1, distance_eucli(X(:,i), barycentres_points(1:nb_dim, j), nb_dim), j);
        end
        min = distance(:,1);
        for j = 2:1:k
            if min(1) > distance(1,j)
                min = distance(:,j);
            end
        end
        X_clusters(:, count) = cat(1, X(:,i), min(2));
        count = count+1;
        for j = 1:1:nb_dim
            barycentres_points(j, min(2)) = ((barycentres_points(j, min(2)) * barycentres_points(nb_dim+1, min(2))+X(j,i))/ (barycentres_points(nb_dim+1, min(2))+1));
        end
        barycentres_points(nb_dim+1, min(2)) = barycentres_points(nb_dim+1, min(2))+1;
        X(:,i) = [];
    end

end