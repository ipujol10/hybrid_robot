%% Constants
wheel_r = 0.075;
wheel_width = 0.03;
wheel_mass = 0.025;
base_length = 0.25;
base_width = 0.15;
base_height = 0.04;
base_mass = 0.4;
extension_length = 0.2;
extension_width = 0.13;
extension_height = 0.03;
extension_mass = 0.4;
motor_base_length = 0.04;
motor_base_width = base_width;
motor_base_height = base_height;
motor_base_mass = 0.4;

%% Initial conditions
extension0 = -0.1;

x0 = 0;
z0 = 0;
phi0 = 0;
l0 = motor_base_length + base_length + max([0 (base_length-extension_length+abs(extension0))]);
theta0 = 0;

%% Mass
mb = 2*wheel_mass + base_mass + extension_mass + motor_base_mass; % mass body
mt = 2*wheel_mass + mb; % mass wheels front (touching ground)

%% Simulation
out = sim("brake");