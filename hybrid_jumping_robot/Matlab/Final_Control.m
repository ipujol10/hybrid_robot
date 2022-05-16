%% Load the Kinematics
Good_kinmeatics

%% Get center of mass
Good_CM

%% Get inertias
Good_Inertias

%% Obtain the numerical matrices
parameters = {d, mw, mb, g, alpha, beta, Iw, Ib, R};
values = {cm, 2*0.279, mb_val, 9.81, 0, 0, 0, 0, 0.075};