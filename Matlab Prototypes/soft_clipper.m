%Soft Clipper Prototype

clear all;
clc;
N = 48000;
y = zeros(N, 1);
t = linspace(0,1,N);
f = 300;

kPos = 10; 
kNeg = 10;
posThresh = 1;
negThresh = 1;

x = sin(2*pi*f*t);    
for n = 1:N
      if x(n)>= 0
        y(n) = (posThresh/atan(kPos))*atan(kPos*x(n));
       else
        y(n) = (negThresh/atan(kNeg))*atan(kNeg*x(n));  
       end
    
end
y = y';
figure(1);
plot(y);
figure(2);
thd(y);
     
    