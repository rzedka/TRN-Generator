clc
clear all
close all


% M = dlmread('.\meas\doc2.txt');

M = dlmread('.\meas\digilent_2.csv',',',10,0);

N = length(M(:,1));


%% Split into N_c channels

N_c = 16;
N_sym = floor(N/N_c);
s_mat = zeros(N_c, N_sym);
N_end = N_sym*N_c;
var_vec = zeros(N_c, 1);

for i=1:N_c
    s_mat(i,:) = M(i:N_c:(N_end-(N_c-i)),2).'; % (1 x N_sym)
    var_vec(i) = mean(abs(s_mat(i,:)).^2);
end




%% Autocovariance

N_comb = N_c*(1+N_c)/2; % Num of combinations
Cov_func_mat = zeros(N_comb, 2*N_sym-1);
idx = 1;
for i_row = 1:N_c
    
    for i_col = i_row:N_c
        
        
        Ax = fft([s_mat(i_row,:), zeros(1, N_sym-1)]); % (1 x 2*N_sym-1)
        Ay = fft([fliplr(s_mat(i_col,:)), zeros(1, N_sym-1)]); % (1 x 2*N_sym-1)
        Cov_func_mat(idx, :) = 2*real(ifft(Ax.*Ay))/sqrt(var_vec(i_row)*var_vec(i_col))/(2*N_sym-1); % (1 x 2*N_sym-1)
        
%         Cov_func_mat(idx, :) = conv(Ax,Ay)/sqrt(mean(Ax.^2)*mean(Ay.^2))/(2*N_sym-1); % (1 x 2*N_sym-1)
        

        idx = idx + 1;
    end
end

%% Covariance matrix
% To make sure the normal variables are sufficiently independent...

Rho_mat = zeros(N_c, N_c);
Rho_delay_mat = 66*ones(N_c, N_c);
idx = 1;
for i_row = 1:N_c
    
    for i_col = i_row:N_c
        
        [max_val, max_idx] = max(abs(Cov_func_mat(idx, :))); % (1 x 1)   
        Rho_mat(i_row,i_col) = max_val;   
        Rho_delay_mat(i_row,i_col) = max_idx - N_sym;
        idx = idx+1;
    end
end

%% Autocorrelation plot

f10 = figure(10);
% n_fft = (-N/2:N/2-1)/N;
corr_idx = 10;
n_atcr = (1-N_sym):(N_sym-1);
plot(n_atcr, 20*log10(abs(Cov_func_mat(corr_idx, :))),'b')
% plot(n_fft(N/2+1:end)*F_smp/1000, log10(abs(S(N/2+1:end)).^2))
% hold on
% plot(f_vec/1000, log10(PSD_vec),'r')
grid on
% hold off
x10 = xlabel('$n$ [-]','fontsize',14);
y10 = ylabel('$R_{x,y}(n)$ [dB]','fontsize',14);
ylim([-100 1 ])
xlim([-1 1]*20)
set(f10, 'position',[50 100 600 500])
set(x10,'interpreter','latex')
set(y10,'interpreter','latex')


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
nvals = hist(s_mat(1,:) ,x_cent)/N/d_x;

Navg2 = 50;
nvals_filt = filter(ones(1,Navg2)/Navg2,1,[nvals,zeros(1,Navg2)]);
nvals_filt = nvals_filt(Navg2/2+1:end-Navg2/2); % centering after filtration

sum(nvals_filt)*d_x


f_X_x = 1/sqrt(2*pi*var_meas)*exp(-(x_cent+0).^2/2/var_meas);

sum(f_X_x)*d_x

f2 = figure(2);
% plot(x_cent, nvals,'b')
plot(x_cent, nvals,'r')
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

