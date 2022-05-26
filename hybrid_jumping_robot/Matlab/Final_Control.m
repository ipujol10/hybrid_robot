%% Load the Kinematics
Final_Kinematics

%% Get center of mass
Final_CM

%% Get inertias
Final_Inertias

%% Obtain the numerical matrices
parameters = {d, mw, mb, g, alpha, beta, Iw, Ib, R};
% values = {cm, 2*0.279, mb_val, 9.81, 0, 0, Iw_val, Ib_val, 0.075};
values = {cm, 2*back_wheels_mass, mb_val, 9.81, 0, 0, Iw_val, Ib_val, 0.075};

A = double(subs(Ap, parameters, values)); % A matrix with numerical values
B = double(subs(Bp, parameters, values)); % B matrix with numerical values

%% Output
C = eye(4);
D = 0; % D matrix

%% System
sys = ss(A, B, C, D); % construct the system
Sc = ctrb(sys); % controlability matrix 
So = obsv(sys); % observability matrix

if (~(rank(Sc) == 4 && rank(So) == 4)) % if the system is not observable and controllable throw an error
    disp("Can't control or/and observe");
else
    X0 = [105*pi/180 0 0 0]'; % starting position of the system
    pt = cell2mat(point)'; % get the working point as a matrix
    x0 = X0 - pt; % obtaining the starting position in the linearized coordinates
    r = [pi/2;0;0;0]; % reference in real world coordinates
    T = 2; % simulation time
    
    %% Control
    Q = [50 0 0 0; 0 0.001 0 0; 0 0 1 0; 0 0 0 0.001]; % Q matrix for LQR
    R = .001; % R matrix for LQR
    
    %% Discrete
    Ts = 1/100; % sample time
    sys_d = c2d(sys, Ts); % obatin the discrete system
    Ad = sys_d.a; % discrete A
    Bd = sys_d.b; % discrete B
    Cd = sys_d.c; % discrete C
    Dd = sys_d.d; % discrete D
    
    K = dlqr(Ad, Bd, Q, R); % obtain the control matrix
    
    %% Observer
    L = dlqr(Ad', C', Q, R)'; % get the control matrix for the observer
end
