%% Load the Kinematics
Kinematics_phi

%% Obtain the numerical matrices
[cm, mt] = get_CM(2*0.05, 0.4, 0.215, 0.4, 0.2, 0.4, 0.0585, 0.025); % get center of mass and total mass of the body
parameters = {g, mb, mw, d, R, alpha, beta};  % parameters to be substituted
values = {9.81, mt, 2*0.3, cm, 0.075, 0, 0}; % values of the paramters

A = double(subs(Ap, parameters, values)); % A matrix with numerical values
B = double(subs(Bp, parameters, values)); % B matrix with numerical values

%% Output
% C = [1 0 0 0; 0 1 0 0; 0 0 0 1]; % get theta, phi and ph1 as the output
C = eye(4);
% C = [0 1 0 0]; % get the phi as the output
% C = [1 0 0 0]; % get the theta as the output
D = 0; % D matrix

%% System
sys = ss(A, B, C, D); % construct the system
Sc = ctrb(sys); % controlability matrix 
So = obsv(sys); % observability matrix

if (~(rank(Sc) == 4 && rank(So) == 4)) % if the system is not observable and controllable throw an error
    disp("Can't control or/and observe");
else
%     if (size(C, 1) == 1)
%         rlocus(sys);
%     end
    X0 = [105*pi/180 0 0 0]'; % starting position of the system
    pt = cell2mat(point)'; % get the working point as a matrix
    x0 = X0 - pt; % obtaining the starting position in the linearized coordinates
    r = [pi/2;0;0;0]; % reference in real world coordinates
    T = 2; % simulation time
    
    %% Control
%     poles = [-3; -3; -3; -3]*.5;
%     K = acker(A, B, poles);
    Q = [50 0 0 0; 0 0.001 0 0; 0 0 1 0; 0 0 0 0.001]; % Q matrix for LQR
    R = .001; % R matrix for LQR
%     Q = eye(1);
%     R = 1;
    
    %% Descrete
    Ts = 1/100; % sample time
    sys_d = c2d(sys, Ts); % obatin the discrete system
    Ad = sys_d.a; % discrete A
    Bd = sys_d.b; % discrete B
    Cd = sys_d.c; % discrete C
    Dd = sys_d.d; % discrete D
    
    K = dlqr(Ad, Bd, Q, R); % obtain the control matrix
%     poles = [.3; .3; .3; .3]*1;
%     K = acker(Ad, Bd, poles);
    
    
    %% Observer
%     Kobs = acker(Ad', Cd', poles*0.01)';
    Kobs = dlqr(Ad', C', Q, R)'; % get the control matrix for the observer
    
    %% Simulate
    simulate = 1;
    if (simulate)
        convert_deg = diag([180/pi;180/pi;1;1]);
        out = sim("model_d");

        %% Figures
        figure;
        hold on
        yyaxis left
        plot(out.x.Time, out.x.Data(:,[1,2]));
        ylabel("Angle [º]")
        yyaxis right
        plot(out.x.Time, out.x.Data(:,[3,4]));
        ylabel("Angular velocity [$\frac{rad}{s}$]",'interpreter','latex')
        title("x");
        lefend = legend("$\theta$", "$\phi$", "$\dot{\theta}$", "$\dot{\phi}$");
        set(lefend, 'Interpreter','latex');
        hold off

        figure;
        plot(out.u);
        title("u");

    %     figure;
    %     plot(out.error);
    %     title("error");
    %     legend = legend("$\theta$", "$\phi$", "$\dot{\theta}$", "$\dot{\phi}$");
    %     set(legend, 'Interpreter','latex');
    
        figure;
        hold on
        yyaxis left
        plot(out.x_d.Time, out.x_d.Data(:,[1,2]));
        ylabel("Angle [º]")
        yyaxis right
        plot(out.x_d.Time, out.x_d.Data(:,[3,4]));
        ylabel("Angular velocity [$\frac{rad}{s}$]",'interpreter','latex')
        title("x Observer");
        lefend = legend("$\theta$", "$\phi$", "$\dot{\theta}$", "$\dot{\phi}$");
        set(lefend, 'Interpreter','latex');
        hold off
    end
end