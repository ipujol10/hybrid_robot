function [CM, total_mass] = get_CM(mass_wheels, mass_base, length_base, mass_extension, length_extension, mass_motor, length_motor, extension_extension)
% extension_extension how much the extension is seeing over the base
d_base = (length_base + length_motor)/2; % distance of the CM of the base to the front wheels
d_extension = length_motor/2 + length_base - length_extension/2 + extension_extension; % distance of the CM of the extension to the front wheels
d_wheels = d_extension + length_extension/2; % distance of the CM of the rear wheels to the front wheels
total_mass = mass_wheels + mass_base + mass_extension + mass_motor; % total mass
CM = (d_base*mass_base + d_extension*mass_extension + d_wheels*mass_wheels)/total_mass; % center of mass