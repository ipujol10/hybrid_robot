clear;
close all;
clc;

%% Var
syms theta(t) x(t) d mw mb g alpha beta

%% Der
x1 = diff(x, t);
theta1 = diff(theta, t);

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
Qx = simplify(diff(diff(L, x1), t) - diff(L, x));

%% EQs
q = [theta; x];
q1 = diff(q, t);

M = simplify([mb*d^2, d*mb*sin(theta); d*mb*sin(theta), mb+mw]);
M1 = simplify(inv(M));
h = simplify([d*g*mb*cos(theta); d*mb*cos(theta)*theta1^2] + [alpha*theta1; beta*x1]);
gq = [0; -1];

Anl = [q1; simplify(-M1*h)];
Bnl = [0; 0; simplify(M1*gq)];

point = {pi/2, 0, 0, 0};
vars = {theta, x, theta1, x1};

A_theta = subs(diff(Anl, theta), vars, point);
A_theta1 = subs(diff(Anl, theta1), vars, point);
A_x = subs(diff(Anl, x), vars, point);
A_x1 = subs(diff(Anl, x1), vars, point);

A = simplify([A_theta, A_x, A_theta1, A_x1]);
B = simplify(subs(Bnl, vars, point));