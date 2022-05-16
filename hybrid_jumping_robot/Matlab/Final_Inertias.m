%% Total inertia of the front wheels
Iw_val = 2 * 0.00105082037;

%% Inertia of the body
% Inertia back wheels
Ibw = 2 * 0.00036114559;

% Inertia motors
I_m = 0.00059331;

% Inertia high base
base_high_height = 0.0801;
I_bh = inertia_box(base_high_mass, base_high_height, base_high_length);

% Inertia short base
base_short_height = 0.012;
I_bs = inertia_box(base_short_mass, base_short_height, base_short_length);













function I = inertia_box(mass, height, length)
I = 1/12*mass*(height^2 + length^2);
end
