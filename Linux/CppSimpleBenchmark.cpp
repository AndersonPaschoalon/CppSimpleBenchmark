#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cstring>

const int ARRAY_SIZE = 1024 * 1024 * 1024; // 1 GB

void benchmark_disk_io() 
{
    std::ofstream file("test.txt");
    if (!file) {
        std::cerr << "Failed to open file for writing\n";
        return;
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        file << 'a';
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    file.close();
    std::remove("test.txt");
    
    std::cout << "Disk write speed: "
              << (ARRAY_SIZE / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
              << " bytes/ms\n";
    
    char* buffer = new char[ARRAY_SIZE];
    std::ofstream file2("test.txt");
    if (!file2) {
        std::cerr << "Failed to open file for writing\n";
        delete[] buffer;
        return;
    }
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        file2 << buffer[i];
    }
    end = std::chrono::high_resolution_clock::now();
    
    file2.close();
    std::remove("test.txt");
    delete[] buffer;
    
    std::cout << "Disk read speed: "
              << (ARRAY_SIZE / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
              << " bytes/ms\n";
}

void benchmark_ram_operations() 
{
    char* array = new char[ARRAY_SIZE];
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = 'a';
    }
    auto end = std::chrono::high_resolution_clock::now();
    
    std::cout << "RAM write speed: "
              << (ARRAY_SIZE / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
              << " bytes/ms\n";
    
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        char c = array[i];
        c += 1;
        array[i] = c;
    }
    end = std::chrono::high_resolution_clock::now();
    
    std::cout << "RAM read and write speed: "
              << (ARRAY_SIZE / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())
              << " bytes/ms\n";
    
    delete[] array;
}

int main() 
{
    benchmark_disk_io();
    benchmark_ram_operations();
    
    return 0;
}