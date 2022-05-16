%% Total inertia of the front wheels
Iw_val = 2 * 0.00105082037;

%% Inertias of each part of the body
% Inertia back wheels
I_bw_cm = 2 * 0.00036114559;

% Inertia motors
I_m_cm = 0.00059331;

% Inertia high base
base_high_height = 0.0801;
I_bh_cm = inertia_box(base_high_mass, base_high_height, base_high_length);

% Inertia short base
base_short_height = 0.012;
I_bs_cm = inertia_box(base_short_mass, base_short_height, base_short_length);

%% Individual Inertia of the body
% I = Icm + m*d^2

% Inertia of the motors
% Same: the rotation point is at the CM of the motor --> d = 0
I_m = I_m_cm;

% Inertia of the high base
I_bh = I_bh_cm + base_high_mass * cm_bh^2;

% Inertia of the short base
I_bs = I_bs_cm + base_short_mass * cm_bs^2;

% Inertia of the back wheels
I_bw = I_bw_cm + 2 * back_wheels_mass * cm_w^2;

%% Inertia of the body
Ib_val = I_m + I_bh + I_bs + I_bw;

%% Function to get the inertia of a box
function I = inertia_box(mass, height, length)
I = 1/12*mass*(height^2 + length^2);
end