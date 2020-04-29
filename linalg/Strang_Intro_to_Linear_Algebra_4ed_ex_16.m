% Plotting for Introduction to Linear Algebra, 4th edition
% author : Wesley Mesquita (wesleymesquita@gmail.com) 

%Exercise 16 :
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

z = -v + 2*w;
quiver(0,0,z(1), z(2), 0);


for c=linspace(0,1,100)
    d = 1-c;
    z = c*v + w*d;
    quiver(0,0,z(1), z(2), 0);
end

legend("w", "v", "w-v", "-v + 2*w"); 

hold off