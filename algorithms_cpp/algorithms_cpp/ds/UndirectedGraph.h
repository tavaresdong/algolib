#pragma once
#pragma once
#ifndef _UNDIRECTEDGRAPH_H_
#define _UNDIRECTEDGRAPH_H_
#include <map>
#include <set>
#include <utility>
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

namespace algo
{
    template <typename T>
    class UndirectedGraph {
        typedef typename std::map<T, std::set<T>>::iterator iterator;
    public:
        UndirectedGraph();
        bool addNode(T node);
        bool removeNode(T node);
        bool addEdge(T e1, T e2);
        bool removeEdge(T e1, T e2);
        const std::set<T>& edgesFrom(T node) const;
        iterator begin() { return adjlists.begin(); }
        iterator end() { return adjlists.end(); }
    private:
        std::map<T, std::set<T>> adjlists;
    };

    template <typename T>
    const std::set<T>& UndirectedGraph<T>::edgesFrom(T node) const
    {
        if (adjlists.find(node) == adjlists.end())
            throw std::invalid_argument("node is not in the graph");  // return an empty map
        return adjlists.at(node);
    }

    template <typename T>
    UndirectedGraph<T>::UndirectedGraph() { }

    template <typename T>
    bool UndirectedGraph<T>::addNode(T node)
    {
        // The node already exists
        if (adjlists.find(node) != adjlists.end())
            return false;
        auto result = adjlists.insert(std::make_pair
            (node, std::set<T>()));
        return result.second;
    }

    template <typename T>
    bool UndirectedGraph<T>::addEdge(T e1, T e2)
    {
        if (adjlists.find(e1) == adjlists.end())
            return false;
        if (adjlists.find(e2) == adjlists.end())
            return false;
        adjlists.at(e1).insert(e2);
        adjlists.at(e2).insert(e1);
        return true;
    }

    template <typename T>
    bool UndirectedGraph<T>::removeEdge(T e1, T e2)
    {
        if (adjlists.find(e1) == adjlists.end())
            return false;
        if (adjlists.find(e2) == adjlists.end())
            return false;
        size_t erased1 = adjlists.at(e1).erase(e2);
        size_t erased2 = adjlists.at(e2).erase(e1);
        return erased1 == 1 && erased2 == 1;
    }

    template <typename T>
    bool UndirectedGraph<T>::removeNode(T node)
    {
        if (adjlists.find(node) == adjlists.end())
            return false;
        adjlists.erase(node);
        for (auto& val : adjlists)
        {
            val.second.erase(node);
        }
        return true;
    }

    void test_undirected_graph()
    {
        UndirectedGraph<std::string> graph;
        assert(graph.removeNode("good") == false);
        assert(graph.addNode("good") == true);
        assert(graph.removeEdge("good", "excellent") == false);
        assert(graph.addEdge("good", "excellent") == false);
        assert(graph.addNode("excellent") == true);
        assert(graph.addEdge("good", "excellent") == true);
        auto& edges = graph.edgesFrom("excellent");
        assert(!edges.empty());
        assert(edges.find("good") != edges.end());
    }
}

#endif