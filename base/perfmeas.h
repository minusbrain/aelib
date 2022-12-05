/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2022 Andreas Evers
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
#pragma once
#include <chrono>
#include <iostream>
#include <string>

#include "helpers.h"

namespace base {

class BenchmarkStatistics : public NONCOPYANDMOVEABLE {
   public:
    BenchmarkStatistics() = default;
    ~BenchmarkStatistics() = default;

    void registerBenchmarkResult(const std::string& name, std::chrono::microseconds duration) {
        auto it = _numberOfbenchmarks.find(name);
        if (it != _numberOfbenchmarks.end()) {
            ++(it->second);
            _totalTime.find(name)->second += duration;
        } else {
            _numberOfbenchmarks.insert({name, 1});
            _totalTime.insert({name, duration});
        }
    }

    void printStatistics() {
        std::cout << "\nBenchmarking statistics:\n";
        for (const auto& [name, number] : _numberOfbenchmarks) {
            std::cout << "Name: " << name << '\n';
            std::cout << "Runs: " << number << ", Total time: " << _totalTime[name]
                      << " Average time: " << _totalTime[name] / number << '\n';
        }
    }

   private:
    std::map<std::string, int> _numberOfbenchmarks;
    std::map<std::string, std::chrono::microseconds> _totalTime;
};

class ScopedBenchmark : public NONCOPYANDMOVEABLE {
   public:
    ScopedBenchmark(BenchmarkStatistics& statistics, const std::string& name)
        : _statistics(statistics), _name(name), _start() {
        _start = std::chrono::high_resolution_clock::now();
    }
    ~ScopedBenchmark() {
        std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - _start);
        _statistics.registerBenchmarkResult(_name, duration);
    }

   private:
    BenchmarkStatistics& _statistics;
    std::string _name;
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

}  // namespace base