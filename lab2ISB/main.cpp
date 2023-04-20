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

float FrequencyBitTest(std::vector<int>& sequence) {
    float sum = 0;
    for (int i = 0; i < sequence.size(); ++i) {
        if (sequence[i] == 1)
            ++sum;
        else
            --sum;
    }
    sum = sum / sqrt(sequence.size());
    float res = erfc(sum / sqrt(2));
    return res;
}

float TestForIdenticalConsecutiveBits(std::vector<int>& seq) {
    float psi = 0;
    unsigned long n = seq.size();
    for (auto i : seq)
        psi += i;
    psi /= n;
    if (!(abs(psi - 0.5) < (2 / sqrt(n))))
        return 0;
    int value = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (seq[i] != seq[i + 1])
            ++value;
    }
    float numerator = abs(value - n * psi * (1 - psi) * 2);
    float denominator = 2 * sqrt(2 * n) * psi * (1 - psi);
    float res = erfc(numerator / denominator);
    return res;
}

float TestForTheLongestSequenceOfOnesInBlock(std::vector<int>& seq) {
    unsigned long N = seq.size(), M = 8;
    int index = 0;
    std::vector<int> count_ones;
    while (index != 128) {
        std::vector<int> tmp;
        for (int i = index; i < index + 8; ++i) {
            tmp.push_back(seq[i]);
        }
        int len = 0, count = 0, max = 0;
        for (auto i : tmp) {
            if (i == 1) ++count;
            else {
                if (count > max) max = count;
                count = 0;
            }
        }
        len = max;
        count_ones.push_back(len);
        index += 8;
    }

    int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    for (auto i : count_ones) {
        if (i <= 1) ++v1;
        if (i == 2) ++v2;
        if (i == 3) ++v3;
        if (i >= 4) ++v4;
    }
    std::vector<int> v = { v1, v2, v3, v4 };
    std::vector<double> p = { 0.2148, 0.3672, 0.2305, 0.1875 };
    float x2 = 0;
    for (int i = 0; i < 4; ++i) {
        x2 += (pow((v[i] - 16 * p[i]), 2) / (16 * p[i]));
    }
    return x2;
}

int main(int argc, const char * argv[]) {
    std::vector<int> binseq;
    binseq = GetSubsequence();
    std::cout << std::endl;
    double first_test = FrequencyBitTest(binseq);
    std::cout << "First test: " << first_test << std::endl;
    double second_test = TestForIdenticalConsecutiveBits(binseq);
    std::cout << "Second test: " << second_test << std::endl;
    double x2 = TestForTheLongestSequenceOfOnesInBlock(binseq);
    std::cout << "Xu: " << x2 << std::endl;
    std::cout << "Third test (result from online calculator): " << 0.277069 << std::endl;
    return 0;
}
