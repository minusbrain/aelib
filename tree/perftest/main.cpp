/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the “Software”), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <tree/tree.h>

#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <vector>

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    const int NUM_OF_NODES = 10000000;
    std::chrono::high_resolution_clock::time_point stlStart;
    std::chrono::high_resolution_clock::time_point stlEnd;
    std::chrono::high_resolution_clock::time_point myStart;
    std::chrono::high_resolution_clock::time_point myEnd;
    std::vector<int> randomVector;
    std::default_random_engine randEngine;
    std::uniform_int_distribution<int> randDist(-1000000, 1000000);
    std::multiset<int> stlTree;
    base::Tree<int> myTree;
    std::multiset<int>::iterator stlIt;
    base::Tree<int>::iterator myIt;

    // std::ofstream file("test.dot");

    std::cout << "Start generating random numbers..." << std::endl;

    // Fill vector with NUM_OF_NODES million integers between - 1 million and +
    // 1 million
    for (int i = 0; i < NUM_OF_NODES; ++i) {
        randomVector.push_back(randDist(randEngine));
    }

    std::cout << "Start filling random numbers into STL multiset..." << std::endl;

    stlStart = std::chrono::high_resolution_clock::now();
    for (auto it = randomVector.begin(); it != randomVector.end(); ++it) stlTree.insert(*it);
    stlEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Start filling random numbers into my tree..." << std::endl;

    myStart = std::chrono::high_resolution_clock::now();
    for (auto it = randomVector.begin(); it != randomVector.end(); ++it) myTree.insert(*it);
    myEnd = std::chrono::high_resolution_clock::now();

    // myTree.streamStructureToDotFormat(file, "", ++(myTree.begin()));

    std::cout << "Finished inserting " << NUM_OF_NODES << " integers!" << std::endl;
    std::cout << "STL Multiset Time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stlEnd - stlStart).count() << " ms" << std::endl;
    std::cout << "AE Tree Time      : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(myEnd - myStart).count() << " ms" << std::endl;

    std::cout << "Start finding integers in STL multiset..." << std::endl;

    stlStart = std::chrono::high_resolution_clock::now();
    for (int i = -499999; i < 500000; ++i) stlIt = stlTree.find(i);
    stlEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Start finding integers in my tree..." << std::endl;

    myStart = std::chrono::high_resolution_clock::now();
    for (int i = -499999; i < 500000; ++i) myIt = myTree.find(i);
    myEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Finished searching a million times in " << NUM_OF_NODES << " integers!" << std::endl;
    std::cout << "STL Multiset Time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stlEnd - stlStart).count() << " ms" << std::endl;
    std::cout << "AE Tree Time      : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(myEnd - myStart).count() << " ms" << std::endl;

    return 0;
}
