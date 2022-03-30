clear;
close all;
clc;

%% Var
syms theta(t) phi(t) d mw mb g alpha beta R

%% Der
x = -phi*R;
x1 = diff(x, t);
x2 = diff(x1, t);
theta1 = diff(theta, t);
theta2 = diff(theta1, t);
phi1 = diff(phi, t);
phi2 = diff(phi1, t);

%% Var
vw = x1;
xb = x - d*cos(theta);
vxb = diff(xb, t);
yb = d*sin(theta);
vyb = diff(yb, t);
vb2 = vxb^2 + vyb^2;

%% L
T = simplify((mw*vw^2 + mb*vb2)/2);
V = mb*g*d*sin(theta);
L = T - V;

Qtheta = simplify(diff(diff(L, theta1), t) - diff(L, theta));
Qphi = simplify(diff(diff(L, phi1), t) - diff(L, phi));
Q = [Qtheta; Qphi];

%% EQs
q = [theta; phi];
q1 = diff(q, t);

M = simplify([diff(Q, theta2), diff(Q, phi2)]);
M1 = simplify(inv(M));
h = simplify(subs(Q, {theta2, phi2}, {0, 0}) + diag([alpha beta])*q1);
gq = [0; 1];

Anl = [q1; simplify(-M1*h)];
Bnl = [0; 0; simplify(M1*gq)];

point = {pi/2, 0, 0, 0};
vars = {theta, phi, theta1, phi1};

A_theta = subs(diff(Anl, theta), vars, point);
A_theta1 = subs(diff(Anl, theta1), vars, point);
A_phi = subs(diff(Anl, phi), vars, point);
A_phi1 = subs(diff(Anl, phi1), vars, point);

Ap = simplify([A_theta, A_phi, A_theta1, A_phi1]);
Bp = simplify(subs(Bnl, vars, point));