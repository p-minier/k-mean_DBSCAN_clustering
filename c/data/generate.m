%% Initialisation
close all; clear; clc;

%% Quantité de points
boucle = 2;
point  = 100;

%% Génération des formes
donuts  = vertcat(ellipse(1, boucle, point, 4, 2, 0, 2*pi, 0, 0, 0.2), ...
                  ellipse(2, boucle, point, 2, 1, 0, 2*pi, 0, 0, 0.2));

lunes   = vertcat(ellipse(1, boucle, point, 2, 8, 0*pi, 1*pi, 2, -3, 0.2), ...
                  ellipse(2, boucle, point, 2, 8, 1*pi, 2*pi, 0,  3, 0.2));

globes  = vertcat(ellipse(1, boucle, point, 2, 2, 0*pi, 2*pi,  0, 8, 1.7), ...
                  ellipse(2, boucle, point, 2, 2, 0*pi, 2*pi, -4, 0, 1.7), ...
                  ellipse(3, boucle, point, 2, 2, 0*pi, 2*pi,  4, 0, 1.7));

lignes  = vertcat(ellipse(1, boucle, point, 50, 2, 1*pi, 5/4*pi,  0,  0, 0.4), ...
                  ellipse(2, boucle, point, 50, 2, 1*pi, 5/4*pi, -4,  3, 0.4), ...
                  ellipse(3, boucle, point, 50, 2, 1*pi, 5/4*pi,  4, -3, 0.4));

%% Affichage
subplot(2, 2, 1);
plot(donuts(:, 1), donuts(:, 2), "r."); grid
title("Donuts");

subplot(2, 2, 2);
plot(lunes(:, 1), lunes(:, 2), "r."); grid
title("Lunes");

subplot(2, 2, 3);
plot(globes(:, 1), globes(:, 2), "r."); grid
title("Globes");

subplot(2, 2, 4);
plot(lignes(:, 1), lignes(:, 2), "r."); grid
title("Lignes");

%% Enregistrement
%csvwrite('donuts.csv', donuts);
%csvwrite('lunes.csv',  lunes);
%csvwrite('globes.csv', globes);
%csvwrite('lignes.csv', lignes);

%% Fonction
function points = ellipse(id, boucle, n, a, b, min, max, Cx, Cy, bruit)
    points = zeros(n * boucle, 3);
    pas = (max - min)/n;
    t = (min:pas:max-pas).';
    for i = 1:boucle
        points((i-1)*n + 1: i*n, 1:2) = [Cx + a * cos(t), Cy + b * sin(t)];
    end
    points(:, 1:2)  = points(:, 1:2) + bruit * 2*(rand(n*boucle, 2) - 1); % bruit
    points(:, 3) = id * ones(n*boucle, 1); % ajout de l'id
end