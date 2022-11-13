
%% Display position
x_shift=0;
y_shift=0;
 
%% Benchmark
x_b=[0 0.0625 0.0703 0.0781 0.0938 0.1563 0.2266 0.2344 0.5000 0.8047 0.8594 0.9063 0.9453 0.9531 0.9609 0.9688 1.0];
y_b=[0 0.0547 0.0625 0.0703 0.1016 0.1719 0.2813 0.4531 0.5000 0.6172 0.7344 0.8516 0.9531 0.9609 0.9688 0.9766 1.0];
Re_100_v=[0 0.09233 0.10091 0.10890 0.12317 0.16077 0.17507 0.17527 0.05454 -0.24533 -0.22445 -0.16914 -0.10313 -0.08864 -0.07391 -0.05906 0];
Re_100_u=[0 -0.03717 -0.04192 -0.04775 -0.06434 -0.10150 -0.15662 -0.21090 -0.20581 -0.13641 0.00332 0.23151 0.68717 0.73722 0.78871 0.84123 1];
Re_400_v=[0 0.1836 0.19713 0.20920 0.22965 0.28124 0.30203 0.30174 0.05186 -0.38598 -0.44993 -0.23827 -0.22847 -0.19254 -0.15663 -0.12146 0];
Re_400_u=[0 -0.08186 -0.09266 -0.10338 -0.14612 -0.24299 -0.32726 -0.17119 -0.11477 0.02135 0.16256 0.29093 00.55892 0.91756 0.68439 0.75837 1];
Re_1000_v=[0.00000 0.27485 0.29012 0.30353 0.32627 0.37095 0.33075 0.32235 0.02526 -0.31966 -0.42665 -0.51500 -0.39188 -0.33714 -0.27669 -0.21388 0.00000];
Re_1000_u=[0.00000 -0.18109 -0.20196 -0.22220 -0.29730 -0.38289 -0.27805 -0.10648 -0.06080 0.05702 0.18719 0.33304 0.46604 0.51117 0.57492 0.65928 1.00000];
Re_5000_v=[0.00000 0.42447 0.43329 0.43648 0.42951 0.35368 0.28066 0.27280 0.00945 -0.30018 -0.36214 -0.41442 -0.52876 -0.55408 -0.55069 -0.49774  0.00000];
Re_5000_u=[0.00000 -0.41165 -0.42901 -0.43643 -0.40435 -0.33050 -0.22855 -0.07404 -0.03039 0.08183 0.20087 0.33556 0.46036 0.45992 0.46120 0.48223 1.00000];
%grid point
for i=1:81
    pt(i)=(i-1)/80;
end
%% Load data
load u.dat
load v.dat
load p.dat
% load pred_p.dat

% Post-process
u=u.';
v=v.';
p=p.';
% pred_p=pred_p.';
velocity=(u.^2+v.^2).^0.5;

% Plot
% Benchmark-u
figure(1)
hold on

plot(Re_100_u, y_b, 'k^')
plot(u(:, 41), pt, 'k')
axis square
hold off
set(gcf,'position',[x_shift+0 y_shift+300 500 500])
xlabel('u')
ylabel('y')
legend ('Ghia et al.(1982)', 'Result', 'Location','southeast')
legend('boxoff')
ylim([0 1])
hold off
% Benchmark-v
figure(2)
hold on

plot(x_b, Re_100_v, 'k^')
plot(pt, v(41, :), 'k')
xlabel('x')
ylabel('v')
axis square
legend ('Ghia et al.(1982)', 'Result', 'Location','northeast')
legend('boxoff')
xlim([0 1])
hold off
set(gcf,'position',[x_shift+0 y_shift+0 500 500])
%%
% u
figure(3)
contourf(u);
xlabel('i')
ylabel('j')
colorbar
axis square
set(gcf,'position',[x_shift+800 y_shift+500 500 500])

% v
figure(4)
contourf(v);
xlabel('i')
ylabel('j')
colorbar
axis square
set(gcf,'position',[x_shift+1300 y_shift+500 500 500])

% velocity
figure(5)
contourf(velocity);
xlabel('i')
ylabel('j')
colorbar
axis square
set(gca,'YDir','normal') 
set(gcf,'position',[x_shift+1050 y_shift+500 500 500])

% p
figure(6)
imagesc(p);
xlabel('i')
ylabel('j')
colorbar
axis square
set(gca,'YDir','normal') 
set(gcf,'position',[x_shift+800 y_shift+0 500 500])

% p_pred
% figure(7)
% imagesc(pred_p);
% xlabel('i')
% ylabel('j')
% colorbar
% axis square
% set(gca,'YDir','normal') 
% set(gcf,'position',[x_shift+1300 y_shift+0 500 500])