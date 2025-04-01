x = [7.90, 7.9, 7.8, 7.8, 7.8, 7.8, 7.8, 7.8, 7.7, 7.8, 7.6, 7.7, 7.7, 7.6, 7.5, 7.50];
y = [8, 7.8, 7.9, 7.8, 7.8, 7.9, 7.8, 7.9, 7.7, 7.7, 7.7, 7.8, 7.9, 7.7, 7.6, 7.7];

[r, p] = corr(x', y', 'Type', 'Pearson');
fprintf('r = %.4f, p = %.4f\n', r, p);

l = polyfit(x, y, 1);
scatter(x, y, 'bo');
hold on;
x_fit = linspace(min(x), max(x), 100);
y_fit = polyval(l, x_fit);
plot(x_fit, y_fit, 'r-', 'LineWidth', 2);
xlabel('pH1');
ylabel('pH2');
title('pH1 vs pH2');
legend('数据点', '线性拟合');
grid on;
hold off;
