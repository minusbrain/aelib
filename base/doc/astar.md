# Generic A* Pathfinding algorithm

This header implements a fairly basic but generic A* pathfinding algorithm. All the user needs
to provide is a World class that derives from `IPathfindWorld<T_Node>` . `T_Node` can be any data
type that represents a node in the users world. And IPathfindWorld expects only two methods to be
implemented:
```cpp
    virtual std::vector<std::pair<T_Node, uint32_t>> getDirectNeighborsAndCosts(const T_Node&) = 0;
    virtual uint32_t getEstimatedCost(const T_Node&, const T_Node&) = 0;
```
Then a simple call to
```cpp
auto path = base::Pathfinder<T_Node>::findPath(world, destinationNode, startNode);
```
will return the shortest path.

You can look at the unit-test examples to get an idea.
