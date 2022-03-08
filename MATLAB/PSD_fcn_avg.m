function [f,PSD] = PSD_fcn_avg(s,F,Navg)
% Author: Radim Zedka
% Date: 13.11.2019
% Description:
% This function calculates the Power Spectral Density of a discrete signal
% in [V^2] with additional function of averaging (Moving average filter) 
% over "Navg" samples. "Navg" must be EVEN.
% It also creates the frequency vector of length N from -F/2 to 
% F/2 where "F" is the sampling frequency.
% In order to get PSD in [V^2/Hz], multiply the result by 1/F.

N = length(s);
f = (-N/2:(N/2-1))/N*F; % frequency from -F/2 to F/2
%============== Averaging ==============================
PSD_x = [fftshift(abs(fft(s)).^2)/N,zeros(1,Navg)]; % [V^2]
if Navg >= 1
    PSD_y = filter(ones(1,Navg)/Navg,1,PSD_x);
    PSD = PSD_y(Navg/2+1:end-Navg/2); % centering after filtration
else
    PSD = PSD_x(1:N);
end
