#include <iostream>
#include <chrono>
#include <thread>

void printProgressBar(int progress, int total) {
    const int barWidth = 50;
    float percentage = (float)progress / total;
    int pos = barWidth * percentage;

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(percentage * 100.0) << " %\r";
    std::cout.flush();
}

int main() {
    int total = 100;
    for (int i = 0; i <= total; ++i) {
        printProgressBar(i, total);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟处理时间
    }
    std::cout << std::endl; // 输出完进度条后换行
    return 0;
}