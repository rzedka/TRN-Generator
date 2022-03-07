clc
clear all
close all


M = dlmread('.\meas\doc2.txt');

Nbins= 1024;
xvals = 0:1023;
[nvals,~] = hist(M,xvals);

figure(1)
plot(xvals, nvals)
grid on

