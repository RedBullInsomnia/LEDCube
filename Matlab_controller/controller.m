close all; clear all; clc;

%---------------------------------------------------
% Reference voltage
%---------------------------------------------------
reference = 3.72;

%---------------------------------------------------
% Simulation of the measured voltage
%---------------------------------------------------
Vg = 20;
n = 0.4714;
measured_voltage = zeros(1,10000);
%for i=1:10000
%    measured_voltage(i) = 5 ;%+ 0.0001*i;
%end

%---------------------------------------------------
% Parameters for the controller
%---------------------------------------------------
kp = 0.1819;
ki = 10.3902;
Ts = 0.000332;

%---------------------------------------------------
% Variables to store values
%---------------------------------------------------
error = zeros(1,10000);
previous_error = 0;
integral = 0;
previous_output = 0;
u = zeros(1,10000);

for i=1:10000
    if(i==1)
        measured_voltage = 0;
    else
        measured_voltage(i) = n * Vg * u(i-1) / ( 1 - u(i-1) );
    end;
    
    error(i) = reference - measured_voltage(i);
    u(i) = kp*(error(i) - previous_error) + ki*Ts*0.5*(error(i) + previous_error) + previous_output;
    %integral = integral + error(i) * Ts;
    %u(i) = kp * error(i) + ki * integral;
    previous_error = error(i);
    previous_output = u(i);
    
    if(u(i) > 0.9)
        u(i) = 0.9;
    elseif(u(i) < 0.1)
        u(i) = 0.1;
    end;
end
figure
plot(1:10000, u);%/5);
figure
plot(1:10000, measured_voltage);
measured_voltage(1:30).'




