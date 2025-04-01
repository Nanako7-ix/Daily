x = [28.4, 27.3, 26.9, 27.3, 28.6, 28, 27.9, 28, 28.7, 27.7, 27.2, 26.1, 26.7, 25.5, 26.5];
y = [28.4, 28, 27, 27.8, 29.2, 29.7, 28.8, 30, 28.5, 28.7, 27, 25.6, 27, 26.8, 26.8];

[r, p] = corr(x', y', 'Type', 'Pearson');
fprintf('r = %.4f, p = %.4f\n', r, p);

l = polyfit(x, y, 1);
scatter(x, y, 'bo');
hold on;
x_fit = linspace(min(x), max(x), 100);
y_fit = polyval(l, x_fit);
plot(x_fit, y_fit, 'r-', 'LineWidth', 2);
xlabel('温度1');
ylabel('温度2');
title('温度1 vs 温度2');
legend('数据点', '线性拟合');
grid on;
hold off;
