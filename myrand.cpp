#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()

void init_rand(){
    srand(static_cast<unsigned int>(time(0))); // 使用当前时间作为种子
}

int zero_or_one(int percent_for_one){
    int i = rand() % 100;
    return i < percent_for_one;
} 

