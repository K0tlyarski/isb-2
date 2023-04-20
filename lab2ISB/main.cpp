//
//  main.cpp
//  lab2ISB
//
//  Created by Вадим Котлярский on 03.04.2023.
//

#include <iostream>
#include <random>
#include <vector>
#include <fstream>

void show_vector( std::vector<int>&a)
{
    for (std::vector<int>::iterator it = a.begin() ; it!=a.end() ; ++it)
        std::cout<<*it;
}
std::vector<int>GetSubsequence (){
    std::vector<int> res;
    //Источник
    std::random_device rd;
      //Генератор
    std::default_random_engine generator(rd());
      // Распределение
    std::uniform_int_distribution<int> distribution(0,1);
    for (int i = 0; i < 128; ++i) {
        res.push_back(distribution(generator));
    }
    show_vector(res);
    std::ofstream file;
    file.open("/Users/vadimkotlarskij/Desktop/c++/sem4/testRandom/testRandom/binarysequence.txt");
    if (file.is_open()) {
        for (auto i : res) {
            file << i;
        }
        }
        file.close();
    return res;
}

int main(int argc, const char * argv[]) {
    
    return 0;
}
