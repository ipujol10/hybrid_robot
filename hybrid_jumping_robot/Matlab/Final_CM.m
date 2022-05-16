% motor part
motor_mass = 0.73466;
motor_length = 0.0585;

% base
base_short_mass = 0.035787182587666264;
base_short_length = 0.14;

base_high_mass = 0.017062817412333738;
base_high_length = 0.01;

%back wheels
back_wheels_mass = 0.09589;

% center of mass
mb_val = motor_mass + base_short_mass + base_high_mass + 2*back_wheels_mass; % mass of the body

cm_bh = (motor_length + base_high_length)/2; % the position of the center of mass of the base_high
bhc = cm_bh * base_high_mass; % contribution to the cm of the base_high

cm_bs = cm_bh + (base_high_length + base_short_length)/2; % the position of the center of mass of the base_short
bsc = cm_bs * base_short_mass; % contribution to the cm of the base_short

cm_w = cm_bs + base_short_length/2 - 0.01; % the position of the center of mass of the wheels
wc = cm_w * 2*back_wheels_mass; % contribution to the cm of the wheels

cm = (bhc + bsc + wc)/mb; % the center of mass of the body
