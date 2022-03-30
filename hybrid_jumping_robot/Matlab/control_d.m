%% Load the Kinematics
Kinematics_phi

%% Obtain the numerical matrices
[cm, mt] = get_CM(2*0.05, 0.4, 0.215, 0.4, 0.2, 0.4, 0.0585, 0.025);
parameters = {g, mb, mw, d, R, alpha, beta};
values = {9.81, mt, 2*0.3, cm, 0.075, 0, 0};

A = double(subs(Ap, parameters, values));
B = double(subs(Bp, parameters, values));

%% Output
C = [1 0 0 0; 0 1 0 0]; % get theta and phi as the output
% C = [0 1 0 0];
% C = [1 0 0 0];
D = 0;

%% System
sys = ss(A, B, C, D);
Sc = ctrb(sys);
So = obsv(sys);
% disp(rank(Sc));
% disp(rank(So));

if (~(rank(Sc) == 4 && rank(So) == 4))
    disp("Can't control or/and observe");
else
%     if (size(C, 1) == 1)
%         rlocus(sys);
%     end
%     x0 = [pi/2+5*pi/180 0 0 0]';
    X0 = [pi/2+5*pi/180 0 0 0]';
    pt = cell2mat(point)';
    x0 = X0 - pt;
    r = [pi/2;0;0;0];
    T = 10;
    
    %% Control
%     poles = [-3; -3; -3; -3]*.5;
%     K = acker(A, B, poles);
    Q = [1 0 0 0; 0 0.001 0 0; 0 0 0.001 0; 0 0 0 0.001];
    R = .001;
    K = lqr(A, B, Q, R);
    
%     %% Descrete
%     Ts = 0.01;
%     sys_d = c2d(sys, Ts);
%     Ad = sys_d.a;
%     Bd = sys_d.b;
%     Cd = sys_d.c;
%     Dd = sys_d.d;
%     
% %     K = lqr(Ad, Bd, Q, R);
%     poles = [-.3; -.3; -.3; -.3];
%     K = acker(A, B, poles);
    
    %% Simulate
    out = sim("model");
    
    %% Figures
    figure;
    plot(out.x);
    title("x");
    lefend = legend("$\theta$", "$\phi$", "$\dot{\theta}$", "$\dot{\phi}$");
    set(lefend, 'Interpreter','latex');
    
    figure;
    plot(out.u);
    title("u");
    
    figure;
    plot(out.error);
    title("error");
    legend = legend("$\theta$", "$\phi$", "$\dot{\theta}$", "$\dot{\phi}$");
    set(legend, 'Interpreter','latex');
end