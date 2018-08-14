#include <boost/optional.hpp>
#include <cstdint>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <vector>
#ifdef DEBUG_FLAG
#include <iostream>
#endif

#ifndef _AELIB_ASTAR_H_
#define _AELIB_ASTAR_H_

namespace ae {
template <class T_Node> class Path {
  public:
    Path(std::vector<T_Node> path, uint32_t cost)
      : _success(true), _path(path), _cost(cost) {}
    Path(bool success = false) : _success(success), _path(), _cost(0) {}

    bool isValid() { return _success; }

    uint32_t getCost() { return _cost; }

    typename std::vector<T_Node>::const_iterator cbegin(void) {
        return _path.cbegin();
    }

    typename std::vector<T_Node>::const_iterator cend(void) {
        return _path.cend();
    }

  private:
    bool _success;
    std::vector<T_Node> _path;
    uint32_t _cost;
};

template <class T_Node> class IPathfindWorld {
  public:
    virtual std::vector<std::pair<T_Node, uint32_t>>
      getDirectNeigboursAndCosts(T_Node) = 0;
    virtual uint32_t getEstimatedCost(T_Node, T_Node) = 0;

    virtual ~IPathfindWorld() {}
};

template <class T_Node> class Pathfinder {
  public:
    static Path<T_Node> findPath(IPathfindWorld<T_Node>* world, T_Node dest,
                                 T_Node start) {
        std::map<T_Node, Metadata> metaLUT;
        std::set<T_Node> closedSet;
        std::vector<T_Node> openList;

        openList.push_back(start);
        metaLUT[start] =
          Metadata{0, world->getEstimatedCost(start, dest), boost::none};

        while (openList.size() > 0) {
            std::sort(openList.begin(), openList.end(),
                      [&metaLUT](const T_Node& lhs, const T_Node& rhs) -> bool {
                          return metaLUT[lhs].f > metaLUT[rhs].f;
                      });
            auto current = openList.back();
#ifdef DEBUG_FLAG
            std::cout << "Current Node: (" << current.first << " | "
                      << current.second << ")" << std::endl;
#endif

            if (current == dest) {
                return generatePath(metaLUT, current);
            }

            openList.pop_back();
            closedSet.insert(current);

            auto neigbours = world->getDirectNeigboursAndCosts(current);

            for (auto neigbour : neigbours) {
                if (closedSet.find(neigbour.first) != closedSet.end()) {
                    continue;
                }

                if (std::find(openList.begin(), openList.end(),
                              neigbour.first) == openList.end()) {
                    openList.push_back(neigbour.first);
                }

                if (metaLUT.find(neigbour.first) == metaLUT.end()) {
                    metaLUT[neigbour.first] = Metadata{
                      std::numeric_limits<uint32_t>::max(),
                      std::numeric_limits<uint32_t>::max(), boost::none};
                }

                uint32_t tentative_g = metaLUT[current].g + neigbour.second;
                if (tentative_g >= metaLUT[neigbour.first].g) {
                    continue;
                }

                metaLUT[neigbour.first].cameFrom = current;
                metaLUT[neigbour.first].g = tentative_g;
                metaLUT[neigbour.first].f =
                  tentative_g + world->getEstimatedCost(neigbour.first, dest);
            }
        }

        return Path<T_Node>(false);
    }

  private:
    struct Metadata {
        Metadata() : g(0), f(0), cameFrom() {}
        Metadata(uint32_t pg, uint32_t pf, boost::optional<T_Node> pcameFrom)
          : g(pg), f(pf), cameFrom(pcameFrom) {}
        uint32_t g;
        uint32_t f;
        boost::optional<T_Node> cameFrom;
    };

    static Path<T_Node> generatePath(std::map<T_Node, Metadata>& metaLUT,
                                     T_Node current) {
        uint32_t cost = metaLUT[current].g;
        std::vector<T_Node> pathVector;
        pathVector.push_back(current);
        while (metaLUT[current].cameFrom != boost::none) {
            current = *(metaLUT[current].cameFrom);
            pathVector.push_back(current);
        }
        return Path<T_Node>{pathVector, cost};
    }
};
}

#endif /* _AELIB_ASTAR_H_ */
