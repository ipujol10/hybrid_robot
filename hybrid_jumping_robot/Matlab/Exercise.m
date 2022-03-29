clear;
close all;
clc;

%% Var
syms mp mc x(t) L theta(t) g alpha beta u(t)

%% Der
x1 = diff(x, t);
theta1 = diff(theta, t);

%% Var
% vc = x1;
ppx = x - L*sin(theta);
vpx = diff(ppx, t);
ppy = L*cos(theta);
vpy = diff(ppy, t);
vp2 = vpx^2 + vpy^2;

%% L
T = (mp*vp2 + mc*x1^2)/2;
T = simplify(T);
V = mp*g*L*cos(theta);
Lag = T - V;

Qtheta = diff(diff(Lag, theta1), t) - diff(Lag, theta);
Qtheta = simplify(Qtheta);

Qx = diff(diff(Lag, x1), t) - diff(Lag, x);
Qx = simplify(Qx);

%% EQs
q = [theta; x];
q1 = diff(q, t);

M = simplify([mp*L^2, -mp*L*cos(theta); -L*mp*cos(theta), mc+mp]);
M1 = simplify(inv(M));
h = simplify([-g*mp*L*sin(theta); L*mp*sin(theta)*theta1^2] + [alpha*theta1; beta*x1]);
gp = [0; 1];

A_nl = [q1; simplify(-M1*h)];
B_nl = [0; 0; simplify(M1*gp)];

A_nl_theta = subs(simplify(diff(A_nl, theta)), {theta, theta1, x, x1}, {0, 0, 0, 0});
A_nl_theta1 = subs(diff(A_nl, theta1), {theta, theta1, x, x1}, {0, 0, 0, 0});
A_nl_x = subs(diff(A_nl, x), {theta, theta1, x, x1}, {0, 0, 0, 0});
A_nl_x1 = subs(diff(A_nl, x1), {theta, theta1, x, x1}, {0, 0, 0, 0});

A = simplify([A_nl_theta A_nl_x A_nl_theta1 A_nl_x1]);

B = subs(B_nl, {theta, theta1, x, x1}, {0, 0, 0, 0});