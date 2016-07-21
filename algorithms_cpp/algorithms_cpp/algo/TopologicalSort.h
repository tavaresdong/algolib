#pragma once
#ifndef _TOPOLOGICALSORT_H_
#define _TOPOLOGICALSORT_H_

#include <list>
#include <map>
#include <utility>
#include <iostream>

#include "DirectedGraph.h"

namespace algo
{
    template <typename T>
    void __dfs(const DirectedGraph<T>& graph,
               T key,
               std::map<T, int>& colors,
               std::list<T>& order,
               bool& dag)
    {
        colors[key] = 1;
        for (auto nb : graph.edgesFrom(key))
        {
            if (colors[nb.first] == 0)
            {
                if (dag == false)
                    break;

                // Recursively search descendents
                __dfs(graph, nb.first, colors, order, dag);
            }
            else if (colors[nb.first] == 1)
            {
                // Found a back edge, not DAG!
                dag = false;
                break;
            }
        }
        if (dag == false)
            return;

        // The node finished, insert it in front of the topo-order
        colors[key] = 2;
        order.push_front(key);
    }

    template <typename T>
    std::pair<bool, std::list<T>> topological_sort(const DirectedGraph<T>& graph)
    {
        // Do topological sort on the graph
        // If the graph is not DAG, return false on the first element of returned pair
        // Else return <true, the ordered list of nodes in the graph>

        bool dag = true;
        std::list<T> order;
        std::map<T, int> colors;
        for (auto it = graph.cbegin(); it != graph.cend(); ++it)
        {
            // The node is not visited
            if (colors.find(it->first) == colors.end())
            {
                __dfs(graph, it->first, colors, order, dag);
                if (dag == false)
                    break;
            }
        }
        return std::make_pair<bool, std::list<T>>(std::move(dag), std::move(order));
    }


    void test_topological_sort()
    {
        DirectedGraph<std::string> graph;
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addNode("D");
        graph.addEdge("A", "B", 1);
        graph.addEdge("A", "C", 1);
        graph.addEdge("B", "D", 1);
        graph.addEdge("C", "D", 1);
        
        graph.addEdge("D", "A", 1);
        auto ret = topological_sort(graph);
        assert(!ret.first);
        graph.removeEdge("D", "A");
        graph.addNode("E");
        graph.addEdge("E", "C", 1);
        graph.addNode("F");
        graph.addEdge("F", "A", 1);
        auto ret2 = topological_sort(graph);
        assert(ret2.first);
        for (auto key : ret2.second)
            std::cout << key << std::endl;
    }
}

#endif