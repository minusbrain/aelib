/**
 * @author     Andreas Evers
 *
 * @copyright  Copyright © 2020 Andreas Evers
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once
#include <algorithm>
#include <cstdint>
#include <limits>
#include <map>
#include <optional>
#include <queue>
#include <set>
#include <vector>
#ifdef DEBUG_FLAG
#include <iostream>
#endif

namespace base {
template <class T_Node>
class Path {
   public:
    Path(const std::vector<T_Node> &path, uint32_t cost) : _success(true), _path(path), _cost(cost) {}
    Path(std::vector<T_Node> &&path, uint32_t cost) : _success(true), _path(std::move(path)), _cost(cost) {}

    Path(bool success = false) : _success(success), _path(), _cost(0) {}
    Path(const Path &other) = default;
    Path(Path &&other) = default;

    Path &operator=(const Path &other) = default;
    Path &operator=(Path &&other) = default;
    ~Path() = default;

    bool isValid() const { return _success; }

    uint32_t getCost() const { return _cost; }

    typename std::vector<T_Node>::const_iterator cbegin(void) const { return _path.cbegin(); }

    typename std::vector<T_Node>::const_iterator cend(void) const { return _path.cend(); }

   private:
    bool _success;
    std::vector<T_Node> _path;
    uint32_t _cost;
};

template <class T_Node>
class IPathfindWorld {
   public:
    /**
     * @brief Get all direct neighbors and the actual cost to travel to them
     *
     * Higher cost means worth. It must be ensured that a total path length must
     * not exceed numeric_limits<uint32_t>::max .
     * Cost is use case dependent and can mean anything like time, distance, monetary
     * cost, ...
     *
     * @param node The node to get the neighbors and their travel cost for
     *
     * @return std::vector<std::pair<T_Node, uint32_t>> A vector of neighbor / cost pairs
     */
    virtual std::vector<std::pair<T_Node, uint32_t>> getDirectNeighborsAndCosts(const T_Node &node) const = 0;

    /**
     * @brief Get the Estimated Cost to travel from one node to the other
     *
     * @param startNode start node to estimate the cost from
     * @param destNode destination node to estimate the cost to
     *
     * @return uint32_t The estimated code to travel from start to destination. Heuristic.
     *                  must NOT over-estimate the cost or the algorithm will not find the
     *                  shortest route.
     */
    virtual uint32_t getEstimatedCost(const T_Node &startNode, const T_Node &destNode) const = 0;

    virtual ~IPathfindWorld() {}
};

template <class T_Node>
class Pathfinder {
   public:
    static Path<T_Node> findPath(const IPathfindWorld<T_Node> &world, const T_Node &dest, const T_Node &start) {
        std::map<T_Node, Metadata> metaLUT;
        std::set<T_Node> closedSet;
        std::vector<T_Node> openList;

        openList.push_back(start);
        metaLUT[start] = Metadata{0, world.getEstimatedCost(start, dest), std::nullopt};

        while (openList.size() > 0) {
            std::sort(openList.begin(), openList.end(), [&metaLUT](const T_Node &lhs, const T_Node &rhs) -> bool {
                return metaLUT[lhs].f > metaLUT[rhs].f;
            });
            auto current = openList.back();
#ifdef DEBUG_FLAG
            std::cout << "Current Node: (" << current.first << " | " << current.second << ")" << std::endl;
#endif

            if (current == dest) {
                return generatePath(metaLUT, current);
            }

            openList.pop_back();
            closedSet.insert(current);

            auto neighbors = world.getDirectNeighborsAndCosts(current);

            for (auto neighbor : neighbors) {
                if (closedSet.find(neighbor.first) != closedSet.end()) {
                    continue;
                }

                if (std::find(openList.begin(), openList.end(), neighbor.first) == openList.end()) {
                    openList.push_back(neighbor.first);
                }

                if (metaLUT.find(neighbor.first) == metaLUT.end()) {
                    metaLUT[neighbor.first] = Metadata{std::numeric_limits<uint32_t>::max(),
                                                       std::numeric_limits<uint32_t>::max(), std::nullopt};
                }

                uint32_t tentative_g = metaLUT[current].g + neighbor.second;
                if (tentative_g >= metaLUT[neighbor.first].g) {
                    continue;
                }

                metaLUT[neighbor.first].cameFrom = current;
                metaLUT[neighbor.first].g = tentative_g;
                metaLUT[neighbor.first].f = tentative_g + world.getEstimatedCost(neighbor.first, dest);
            }
        }

        return Path<T_Node>(false);
    }

   private:
    struct Metadata {
        Metadata() : g(0), f(0), cameFrom() {}
        Metadata(uint32_t pg, uint32_t pf, std::optional<T_Node> pcameFrom) : g(pg), f(pf), cameFrom(pcameFrom) {}
        uint32_t g;
        uint32_t f;
        std::optional<T_Node> cameFrom;
    };

    static Path<T_Node> generatePath(std::map<T_Node, Metadata> &metaLUT, T_Node current) {
        uint32_t cost = metaLUT[current].g;
        std::vector<T_Node> pathVector;
        pathVector.push_back(current);
        while (metaLUT[current].cameFrom != std::nullopt) {
            current = *(metaLUT[current].cameFrom);
            pathVector.push_back(current);
        }
        return Path<T_Node>{pathVector, cost};
    }
};
}  // namespace base
