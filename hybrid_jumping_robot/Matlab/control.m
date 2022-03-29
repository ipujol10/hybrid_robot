%% Load the Kinematics
Kinematics

%% Obtain the numerical matrices
[cm, mt] = get_CM(2*0.05, 0.4, 0.215, 0.4, 0.2, 0.4, 0.0585, 0.025);
parameters = {g, mb, mw, d, alpha, beta};
values = {9.81, mt, 2*0.3, cm, 0, 0};

A = double(subs(Ap, parameters, values));
B = double(subs(Bp, parameters, values));

%% Output
C = [0 1 0 0]; % get theta as the output
D = 0;

%% System
sys = ss(A, B, C, D);
Sc = ctrb(sys);
So = obsv(sys);
disp(rank(Sc));
disp(rank(So));