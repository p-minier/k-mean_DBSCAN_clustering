function [value] = distance_eucli(X, Y, nb_dim)
    value = 0;
    for k = 1:1:nb_dim
        value = (X(k) - Y(k)) ^ 2 + value;
    end
    value = sqrt(value);
end