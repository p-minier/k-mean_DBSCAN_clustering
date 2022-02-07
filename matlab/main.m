%% Merwan Muller, Pierre Minier & Baptiste Roulliaux

clear; %Efface les variables de l'environnement de travail
close all; % Ferme les figures ouvertes
clc; % Efface la console

%% K-MEAN
%% Initialisation des paramètres

Y = readtable("donuts.csv");
[points, dim] = size(Y);
X = zeros(dim-1, points);
for i =1:1:points
    X(1,i) = Y.Var1(i);
end
for i =1:1:points
    X(2,i) = Y.Var2(i);
end
X2 = X;

nb_dim = 2;
nb_points = 100;
epsilon = 0.5;
points_cluster = 40;
k = 2;

%% Kmean
%% Code

[X_clusters] = kmean(X, k);

%% Affichage des courbes

[nb_dim, nb_points] = size(X2);
i=1;

color = rand(3, k);
figure,
while i <= nb_points
    repere = X_clusters(nb_dim+1, i);
    for j=1:1:k
        if repere == j
            plot(X_clusters(1,i), X_clusters(2,i), "*", "Color", color(:, j),"LineWidth",5); % Si on veut davantage remarquer les clusters : "LineWidth",5, et si à 3 dimensions : ,"ZData",X_clusters(3,i)
            hold on;
        end
    end
    i = i+1;
end

[nb_dim, nb_points_restants] = size(X);
for i = 1:1:nb_points_restants
    plot(X(1,i), X(2,i), ".", "Color", 'black'); % à 3 dimensions : ,"ZData",X(3,i)
    hold on;
end
hold off;

%% DCSBAN
%% Code

[X_clusters] = cluster_detection_2(X2, epsilon, points_cluster);


%% Affichage des courbes

[nb_dim, nb_points] = size(X2);
i=1;
figure,
while i < nb_points
    repere1 = X_clusters(nb_dim+1, i);
    if repere1 ~=0
        color = rand(1,3);
        plot(X_clusters(1,i), X_clusters(2,i), "*", "Color", color,"LineWidth",5); % Si on veut davantage remarquer les clusters : "LineWidth",5, et si à 3 dimensions : ,"ZData",X_clusters(3,i)
        hold on;
        i=i+1;
        repere2 = X_clusters(nb_dim+1, i);
        while (i < nb_points) && (repere1 == repere2)
            plot(X_clusters(1,i), X_clusters(2,i), "*", "Color", color,"LineWidth",5); % Si on veut davantage remarquer les clusters : "LineWidth",5, et si à 3 dimensions : ,"ZData",X_clusters(3,i)
            hold on;
            i = i+1;
            repere2 = X_clusters(nb_dim+1, i);
        end
    else
        break;
    end
end

[nb_dim, nb_points_restants] = size(X2);
for i = 1:1:nb_points_restants
    plot(X2(1,i), X2(2,i), ".", "Color", 'black'); % à 3 dimensions : ,"ZData",X2(3,i)
    hold on;
end
hold off;
