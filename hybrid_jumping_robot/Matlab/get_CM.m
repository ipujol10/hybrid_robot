function [CM, total_mass] = get_CM(mass_wheels, mass_base, length_base, mass_extension, length_extension, mass_motor, length_motor, extension_extension)
d_base = (length_base + length_motor)/2;
d_extension = length_motor/2 + length_base - length_extension/2 + extension_extension;
d_wheels = d_extension + length_extension/2;
total_mass = mass_wheels + mass_base + mass_extension + mass_motor;
CM = (d_base*mass_base + d_extension*mass_extension + d_wheels*mass_wheels)/total_mass;