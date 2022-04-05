%% Close graphs and clear variables and workspace
clear;
close all;
clc;

%% Variables
syms theta(t) phi(t) d mw mb g alpha beta R Ib Iw

%% Derivatives of the states
x = -phi*R; % assuming no slipage that's how x and phi are related
x1 = diff(x, t); % dx/dt
x2 = diff(x1, t); % d²x/dt²
theta1 = diff(theta, t); % dtheta/dt
theta2 = diff(theta1, t); % d²theta/dt²
phi1 = diff(phi, t); % dphi/dt
phi2 = diff(phi1, t); % d²phi/dt²

%% Variables of the problem
vw = x1; % velocity of the wheel
xb = x - d*cos(theta); % position on the x of the body
vxb = diff(xb, t); % velocity on the x of the body
yb = d*sin(theta); % position on the y of the body
vyb = diff(yb, t); % velocity on the y of the body
vb2 = vxb^2 + vyb^2; % velocity squared of the body

%% Lagrange
T = simplify((mw*vw^2 + mb*vb2 + Ib*theta1^2 + Iw*phi1^2)/2); % kinetic energy
V = mb*g*d*sin(theta); % potential energy
L = T - V; % Lagrange equation

Qtheta = simplify(diff(diff(L, theta1), t) - diff(L, theta)); % d/t*dL/dtheta1 - dL/dtheta
Qphi = simplify(diff(diff(L, phi1), t) - diff(L, phi)); % d/t*dL/dphi1 - dL/dphi
Q = [Qtheta; Qphi]; % have both terms on a matrix to have it easier to derivate and obtain both equations of motion

%% EQs
q = [theta; phi]; % the states
q1 = diff(q, t); % the derivate respect time of the states

M = simplify([diff(Q, theta2), diff(Q, phi2)]); % obtain the friction matrix
M1 = simplify(inv(M)); % inverse of M
h = simplify(subs(Q, {theta2, phi2}, {0, 0}) + diag([alpha beta])*q1); % corriolis, gravity effect and inertia
gq = [0; 1]; % the input matrix

Anl = [q1; simplify(-M1*h)]; % The A matrix on the non-linear form
Bnl = [0; 0; simplify(M1*gq)]; % The B matrix on the non-linear form

point = {pi/2, 0, 0, 0}; % The point of work
vars = {theta, phi, theta1, phi1}; % the states

A_theta = subs(diff(Anl, theta), vars, point); % get derivative respect theta
A_theta1 = subs(diff(Anl, theta1), vars, point); % get derivative respect theta1
A_phi = subs(diff(Anl, phi), vars, point); % get derivative respect phi
A_phi1 = subs(diff(Anl, phi1), vars, point); % get derivative respect phi1

Ap = simplify([A_theta, A_phi, A_theta1, A_phi1]); % linearized A matrix with parameters
Bp = simplify(subs(Bnl, vars, point)); % linearized B matrix with parameters