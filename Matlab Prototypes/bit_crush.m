%Bit Crusher Prototype

clear all;
clc;

depth = 4;
N = 48000;
y = zeros(1,N);
t = linspace(0,1,N);
f = 3;
bias = 0.01;
x = sin(2*pi*f*t);
    
for n = 1:N
    y(n) = round(depth* x(n)) * (1/depth);
end

figure (1);
plot(y)
figure (2);
thd(y);
 
