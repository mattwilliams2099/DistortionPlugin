%Wave Folder Prototype

clear all;
clc;
N = 48000;
t = linspace(0,1,N);
f = 50;
bias = 0.01;
x = sin(2*pi*f*t);
y = zeros(1,N);
folds = 4;%max 8

 for n = 1:N
     if (x(n) >= 0) && (x(n) <= (1/folds))
         y(n) = x(n);
     
     elseif (x(n) > (1/folds)) && (x(n) <= (2/folds))
         y(n) = -x(n) + 2/folds;
     
     elseif (x(n) > (2/folds)) && (x(n) <= (3/folds))
         y(n) = x(n) - (2/folds);
     
     elseif (x(n) > (3/folds)) && (x(n) <= (4/folds))
         y(n) = -x(n) + (4/folds);
     
     elseif (x(n) > (4/folds)) && (x(n) <= (5/folds))
         y(n) = x(n) - (4/folds); 
     
     elseif (x(n) > (5/folds)) && (x(n) <= (6/folds))
         y(n) = -x(n) + (6/folds);
     
     elseif (x(n) > (6/folds)) && (x(n) <= (7/folds))
         y(n) = x(n) - (6/folds);
     
     elseif (x(n) > (7/folds))
         y(n) = -x(n) + (8/folds);

         
     elseif (x(n) < 0) && (x(n) >= (-1/folds))
         y(n) = x(n);
     
     elseif (x(n) < (-1/folds)) && (x(n) >= (-2/folds))
         y(n) = -x(n) - 2/folds;
     
     elseif (x(n) < (-2/folds)) && (x(n) >= (-3/folds))
         y(n) = x(n) + (2/folds);
     
     elseif (x(n) < (-3/folds)) && (x(n) >= (-4/folds))
         y(n) = -x(n) - 4/folds;
     
     elseif (x(n) < (-4/folds)) && (x(n) >= (-5/folds))
         y(n) = x(n) + (4/folds); 
     
     elseif (x(n) < (-5/folds)) && (x(n) >= (-6/folds))
         y(n) = -x(n) - 6/folds;
     
     elseif (x(n) < (-6/folds)) && (x(n) >= (-7/folds))
         y(n) = (x(n) + (6/folds));
     
     elseif (x(n) < (-7/folds)) && (x(n) >= (-1))
         y(n) = (-1/folds) - (x(n) + (7/folds));
     end
 
end


figure (1);
plot (y);
figure (2);
thd (y);


