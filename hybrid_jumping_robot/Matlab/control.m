%% Load the Kinematics
Kinematics

%% Obtain the numerical matrices
[cm, mt] = get_CM(2*0.05, 0.4, 0.215, 0.4, 0.2, 0.4, 0.0585, 0.025);
parameters = {g, mb, mw, d, alpha, beta};
values = {9.81, mt, 2*0.3, cm, 0, 0};

A = double(subs(Ap, parameters, values));
B = double(subs(Bp, parameters, values));
