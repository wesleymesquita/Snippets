% Plotting for Introduction to Linear Algebra, 4th edition
% author : Wesley Mesquita (wesleymesquita@gmail.com) 

%Exercise 17 :
% By the proportions showed in figure 1.5 a, lets assume w = [1 4]'
% and v = [4 1]'

w = [1 4]';
v = [4 1]';

hold on
%plot w
quiver(0,0, w(1), w(2), 0, 'LineWidth', 3);

%plot v
quiver(0,0,v(1), v(2), 0, 'LineWidth', 3);

%plot the dashed line (w-v) from v
line([v(1) w(1)], [v(2), w(2)], 'LineStyle', '--');

p = 1/3*v + 1/3*w;
plot(p(1), p(2), "s", 'LineWidth', 3);
p = 2/3*v + 2/3*w;
plot(p(1), p(2), "s", 'LineWidth', 3);

for c = -1:0.5:1
   z = c*v + c*w;
   quiver(0,0,z(1), z(2),0);    
end

legend("w", "v", "w-v", "1/3*v + 1/3*w", "2/3*v + 2/3*w"); 

hold off