
close all; clear all; clc;

reference = 3.72;

measured_voltage = zeros(1,10000);
for i=1:10000
    measured_voltage(i) = 5 ;%+ 0.0001*i;
end

error = zeros(1,10000);
previous_error = 0;
previous_output = 0;
output = zeros(1,10000);
kp = 0.1819;
ki = 10.3902;
Ts = 0.000332;

for i=1:10000
        
    error(i) = reference - measured_voltage(i);
    output(i) = kp*(error(i) - previous_error) + ki*Ts*0.5*(error(i) + previous_error) + previous_output;
    previous_error = error(i);
    previous_output = output(i);
end

plot(1:10000, output/5);