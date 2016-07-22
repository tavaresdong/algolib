#pragma once
#ifndef _KOSARAJU_H_
#define _KOSARAJU_H_
#include <map>
#include <set>
#include "DirectedGraph.h"


// Implementation of Kosaraju's Strongly connected component
// Algorithm
// Output is a map from Node to its belonging scc number(starting from 0)
// Nodes within the same scc have same scc number

namespace algo
{
    template <typename T>
    void __dfs_visit(std::set<T>& visited, T node, const DirectedGraph<T>& graph, 
                     std::map<int, T>& ftime, int& time)
    {
        visited.insert(node);
        for (auto nb : graph.edgesFrom(node))
        {
            if (visited.find(nb.first) == visited.end())
            {
                __dfs_visit(visited, nb.first, graph, ftime, time);
            }
        }
        time += 1;
        ftime.insert(std::pair<int, T>(time, node));
    }

    template <typename T>
    void __compute_finish_time(const DirectedGraph<T>& graph, std::map<int, T>& ftime)
    {
        // Do dfs on nodes and mark finish time for all nodes
        int time = 0;
        std::set<T> visited;
        for (auto iter = graph.cbegin(); iter != graph.cend(); ++iter)
        {
            T node = iter->first;
            if (visited.find(node) == visited.end())
            {
                __dfs_visit(visited, node, graph, ftime, time);
            }
        }
    }

    template <typename T>
    void __mark_scc(int scc, T node, std::map<T, int>& sccs,
                    DirectedGraph<T>& trans, std::set<T>& visited)
    {
        visited.insert(node);
        sccs.insert(std::pair<T, int>(node, scc));
        for (auto nb : trans.edgesFrom(node))
        {
            if (visited.find(nb.first) == visited.end())
            {
                __mark_scc(scc, nb.first, sccs, trans, visited);
            }
        }
    }


    template <typename T>
    void __compute_scc(DirectedGraph<T>& trans, std::map<int, T>& ftime,
        std::map<T, int>& sccs)
    {
        int scc = 0;
        std::set<T> visited;
        
        // DFS on reversed graph with decreasing ftime
        for (auto iter = ftime.rbegin(); iter != ftime.rend(); ++iter)
        {
            if (visited.find(iter->second) == visited.end())
            {
                scc += 1; 
                
                // A new SCC, mark all scc members this scc number
                __mark_scc(scc, iter->second, sccs, trans, visited);
            }
        }
    }


    template <typename T>
    std::map<T, int> kosaraju_scc(const DirectedGraph<T>& graph)
    {
        // Compute finish time for graph
        std::map<T, int> sccs;
        std::map<int, T> finish_time;
        __compute_finish_time(graph, finish_time);

        // Compute transpose graph
        DirectedGraph<T> trans_graph = graph.transpose();

        // DFS on the transposed graph with finish_time decreasing
        __compute_scc(trans_graph, finish_time, sccs);
        return sccs;
    }
}

#endif