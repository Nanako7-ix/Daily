x = [30, 28, 29, 25, 25, 26, 26, 28, 30, 26, 30, 29, 21, 22, 20];
y = [28, 26, 27, 26, 26, 26, 27, 28, 29, 26, 28, 30, 21, 21, 22];

[r, p] = corr(x', y', 'Type', 'Pearson');
fprintf('r = %.4f, p = %.4f\n', r, p);

l = polyfit(x, y, 1);
scatter(x, y, 'bo');
hold on;
x_fit = linspace(min(x), max(x), 100);
y_fit = polyval(l, x_fit);
plot(x_fit, y_fit, 'r-', 'LineWidth', 2);
xlabel('盐度1');
ylabel('盐度2');
title('盐度1 vs 盐度2');
legend('数据点', '线性拟合');
grid on;
hold off;
