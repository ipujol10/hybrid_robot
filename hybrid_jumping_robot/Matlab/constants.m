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

%% Additional calculations
total_mass = 4*wheel_mass + extension_mass + base_mass + motor_base_mass;
maximum_length = base_length + extension_length - 0.05; % change margin
minimum_length = base_length + 0.1; % inferior limit
max_movement = maximum_length - minimum_length;

%% Global
g = 9.81;