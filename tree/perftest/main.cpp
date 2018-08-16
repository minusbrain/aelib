#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <tree/tree.h>
#include <vector>

int main(int argc, char** argv) {
    const int NUM_OF_NODES = 1000000;
    std::chrono::high_resolution_clock::time_point stlStart;
    std::chrono::high_resolution_clock::time_point stlEnd;
    std::chrono::high_resolution_clock::time_point myStart;
    std::chrono::high_resolution_clock::time_point myEnd;
    std::vector<int> randomVector;
    std::default_random_engine randEngine;
    std::uniform_int_distribution<int> randDist(-1000000, 1000000);
    std::multiset<int> stlTree;
    ae::Tree<int> myTree;
    std::multiset<int>::iterator stlIt;
    ae::Tree<int>::iterator myIt;

    // std::ofstream file("test.dot");

    std::cout << "Start generating random numbers..." << std::endl;

    // Fill vector with NUM_OF_NODES million integers between - 1 million and +
    // 1 million
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        randomVector.push_back(randDist(randEngine));
    }

    std::cout << "Start filling random numbers into STL multiset..."
              << std::endl;

    stlStart = std::chrono::high_resolution_clock::now();
    for (auto it = randomVector.begin(); it != randomVector.end(); ++it)
        stlTree.insert(*it);
    stlEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Start filling random numbers into my tree..." << std::endl;

    myStart = std::chrono::high_resolution_clock::now();
    for (auto it = randomVector.begin(); it != randomVector.end(); ++it)
        myTree.insert(*it);
    myEnd = std::chrono::high_resolution_clock::now();

    // myTree.streamStructureToDotFormat(file, "", ++(myTree.begin()));

    std::cout << "Finished inserting " << NUM_OF_NODES << " integers!"
              << std::endl;
    std::cout << "STL Multiset Time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stlEnd -
                                                                       stlStart)
                   .count()
              << " ms" << std::endl;
    std::cout << "AE Tree Time      : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(myEnd -
                                                                       myStart)
                   .count()
              << " ms" << std::endl;

    std::cout << "Start finding integers in STL multiset..." << std::endl;

    stlStart = std::chrono::high_resolution_clock::now();
    for (int i = -499999; i < 500000; ++i)
        stlIt = stlTree.find(i);
    stlEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Start finding integers in my tree..." << std::endl;

    myStart = std::chrono::high_resolution_clock::now();
    for (int i = -499999; i < 500000; ++i)
        myIt = myTree.find(i);
    myEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Finished searching a million times in " << NUM_OF_NODES
              << " integers!" << std::endl;
    std::cout << "STL Multiset Time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stlEnd -
                                                                       stlStart)
                   .count()
              << " ms" << std::endl;
    std::cout << "AE Tree Time      : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(myEnd -
                                                                       myStart)
                   .count()
              << " ms" << std::endl;

    return 0;
}
