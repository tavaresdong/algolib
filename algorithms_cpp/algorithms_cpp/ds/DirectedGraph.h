#pragma once
#ifndef _DIRECTEDGRAPH_H_
#define _DIRECTEDGRAPH_H_
#include <map>
#include <stack>
#include <utility>
#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>

namespace algo
{
    template <typename T>
    class DirectedGraph {
        typedef typename std::map<T, std::map<T, double>>::iterator iterator;
    public:
        DirectedGraph();
        bool addNode(T node);
        bool removeNode(T node);
        bool addEdge(T src, T dest, double weight);
        bool removeEdge(T src, T dest);
        bool isDAG();
        const std::map<T, double>& edgesFrom(T node) const;
        iterator begin() { return adjlists.begin(); }
        iterator end() { return adjlists.end(); }
    private:
        std::map<T, std::map<T, double>> adjlists;
    };

    template <typename T>
    const std::map<T, double>& DirectedGraph<T>::edgesFrom(T node) const
    {
        if (adjlists.find(node) == adjlists.end())
            throw std::invalid_argument("node is not in graph");
        return adjlists.at(node);
    }

    template <typename T>
    DirectedGraph<T>::DirectedGraph() { }

    template <typename T>
    bool DirectedGraph<T>::isDAG()
    {
        // Using dfs to check if the graph contains a back edge
        // 0 stands for white, 1 for gray and 2 for black
        std::map<T, int> colors;
        std::stack<T> st;
        bool dag = true;
        for (auto it : adjlists)
        {
            T key = it.first;
            if (colors.find(key) == colors.end())
            {
                colors[key] = 1;
                st.push(key);
                while (!st.empty())
                {
                    T cur = st.top();
                    bool finished = true;
                    for (auto nb : edgesFrom(cur))
                    {
                        if (colors[nb.first] == 0)
                        {
                            // Meet an unvisited neighbor
                            colors[nb.first] = 1;
                            st.push(nb.first);
                            finished = false;
                        }
                        else if (colors[nb.first] == 1)
                        {
                            // Back edge
                            dag = false;
                            break;
                        }
                    }
                    if (dag == false)
                        break;
                    else if (finished)
                    {
                        // This node now is out of unvisited neighbors
                        st.pop();
                        colors[cur] = 2;
                    }
                }
                if (dag == false)
                    break;
            }
        }
        return dag;
    }

    template <typename T>
    bool DirectedGraph<T>::addNode(T node)
    {
        // The node already exists
        if (adjlists.find(node) != adjlists.end())
            return false;
        auto result = adjlists.insert(std::make_pair
            (node, std::map<T, double>()));
        return result.second;
    }

    template <typename T>
    bool DirectedGraph<T>::addEdge(T src, T dest, double weight)
    {
        if (adjlists.find(src) == adjlists.end())
            return false;
        if (adjlists.find(dest) == adjlists.end())
            return false;
        auto& edges = adjlists.at(src);
        if (edges.find(dest) != edges.end())
            return false;
        auto result = edges.insert(std::make_pair(dest, weight));
        return result.second;
    }

    template <typename T>
    bool DirectedGraph<T>::removeEdge(T src, T dest)
    {
        if (adjlists.find(src) == adjlists.end())
            return false;
        auto& edges = adjlists.at(src);
        if (edges.find(dest) == edges.end())
            return false;
        auto removed = edges.erase(dest);
        return removed != 0;
    }

    template <typename T>
    bool DirectedGraph<T>::removeNode(T node)
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

    void test_directed_graph()
    {
        DirectedGraph<std::string> graph;
        assert(graph.removeNode("good") == false);
        assert(graph.addNode("good") == true);
        assert(graph.removeEdge("good", "excellent") == false);
        assert(graph.addEdge("good", "excellent", 1.0) == false);
        assert(graph.addNode("excellent") == true);
        assert(graph.addEdge("good", "excellent", 2.1) == true);
        graph.addNode("terrific");
        graph.addEdge("good", "terrific", 2.5);
        auto& edges = graph.edgesFrom("good");
        assert(edges.size() == 2);
        assert(edges.find("excellent") != edges.end());
        assert(edges.find("terrific") != edges.end());
        for (auto key : graph)
            std::cout << key.first << std::endl;
    }

    void test_dag()
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
        assert(graph.isDAG());
        graph.addEdge("D", "A", 1);
        assert(!graph.isDAG());
        graph.removeEdge("D", "A");
        graph.addNode("E");
        graph.addEdge("E", "C", 1);
        assert(graph.isDAG());
    }
}

#endif