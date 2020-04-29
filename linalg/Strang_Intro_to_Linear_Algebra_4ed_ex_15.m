% Plotting for Introduction to Linear Algebra, 4th edition
% author : Wesley Mesquita (wesleymesquita@gmail.com) 

%Exercise 15 :
% By the proportions showed in figure 1.5 a, lets assume w = [1 4]'
% and v = [4 1]'

w = [1 4]';
v = [4 1]';

hold on
%plot w
quiver(0,0, w(1), w(2), 0);

%plot v
quiver(0,0,v(1), v(2), 0);

%plot the dashed line (w-v) from v
line([v(1) w(1)], [v(2), w(2)], 'LineStyle', '--');

%plot point u 
% now we can have point u = 0.5v + 0.5w
u = 0.5*v + 0.5*w;
plot(u(1), u(2), "s");

u = 3/4*v + 1/4*w;
plot(u(1), u(2), "s");

u = 1/4*v + 1/4*w;
plot(u(1), u(2), "s");

u = v + w;
quiver(0,0, u(1), u(2));

legend("w", "v", "w-v", "u = 0.5*v + 0.5*w", "3/4*v + 1/4*w", "1/4*v + 1/4*w", "v+w"); 

hold off