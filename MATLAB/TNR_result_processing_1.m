clc
clear all
close all


% M = dlmread('.\meas\doc2.txt');

M = dlmread('.\meas\digilent_1.csv',',',10,0);

N = length(M(:,1));

%% DFT

d_t = M(2,1) - M(1,1); % Time domain resolution

t_vec = (0:N-1)*d_t;
F_smp = 1/d_t;
s_t = M(:,2).'; % (1 x N)

var_meas = mean(abs(s_t).^2);

S = fftshift(fft(s_t));

[f_vec,PSD_vec] = PSD_fcn_avg(s_t,F_smp,200);

f1 = figure(1);
n_fft = (-N/2:N/2-1)/N;

% plot(n_fft*F_smp/1000, log10(abs(S).^2),'b')
plot(f_vec(N/2+1:end)/1000, log10(PSD_vec(N/2+1:end)/F_smp),'b')
% plot(n_fft(N/2+1:end)*F_smp/1000, log10(abs(S(N/2+1:end)).^2))
% hold on
% plot(f_vec/1000, log10(PSD_vec),'r')
grid on
% hold off
x1 = xlabel('$f$ [kHz]','fontsize',14);
y1 = ylabel('$PSD\ [dB\ V^2/Hz]$','fontsize',14);
ylim([-7 -4 ])
set(f1, 'position',[50 100 600 500])
set(x1,'interpreter','latex')
set(y1,'interpreter','latex')

%%
Nbins= 1024;
x_cent = linspace(-3,3,Nbins);
d_x = x_cent(2) - x_cent(1);
nvals = hist(M(:,2) ,x_cent)/N/d_x;

Navg2 = 50;
nvals_filt = filter(ones(1,Navg2)/Navg2,1,[nvals,zeros(1,Navg2)]);
nvals_filt = nvals_filt(Navg2/2+1:end-Navg2/2); % centering after filtration

sum(nvals_filt)*d_x


f_X_x = 1/sqrt(2*pi*var_meas)*exp(-(x_cent+0.06).^2/2/var_meas);

sum(f_X_x)*d_x

f2 = figure(2);
% plot(x_cent, nvals,'b')
plot(x_cent, nvals_filt,'r')
grid on
hold on
% plot(x_cent, nvals_filt,'r')
plot(x_cent, f_X_x,'k--')
hold off
x2 = xlabel('$x$ [V]','fontsize',14);
y2 = ylabel('$f_X(x)$ [1/V]','fontsize',14);
lgd2 = legend('meas-filtered','theory','fontsize',14);
set(f2, 'position',[750 100 600 500])
set(x2,'interpreter','latex')
set(y2,'interpreter','latex')
set(lgd2,'interpreter','latex')