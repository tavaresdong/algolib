#include "kosaraju_test.h"

namespace algo
{
    void test_ftime()
    {
        DirectedGraph<char> graph;
        for (auto c = 'a'; c <= 'h'; c++)
            graph.addNode(c);
        graph.addEdge('a', 'b', 1);
        graph.addEdge('e', 'a', 1);
        graph.addEdge('b', 'e', 1);
        graph.addEdge('b', 'c', 1);
        graph.addEdge('c', 'd', 1);
        graph.addEdge('d', 'c', 1);
        graph.addEdge('e', 'f', 1);
        graph.addEdge('b', 'f', 1);
        graph.addEdge('f', 'g', 1);
        graph.addEdge('g', 'f', 1);
        graph.addEdge('c', 'g', 1);
        graph.addEdge('g', 'h', 1);
        graph.addEdge('d', 'h', 1);
        graph.addEdge('h', 'h', 1);
        std::map<int, char> ftime;
        __compute_finish_time(graph, ftime);
        for (auto ft : ftime)
            std::cout << ft.first << " " << ft.second << std::endl;
    }

    void test_kosaraju()
    {
        DirectedGraph<char> graph;
        for (auto c = 'a'; c <= 'h'; c++)
            graph.addNode(c);
        graph.addEdge('a', 'b', 1);
        graph.addEdge('e', 'a', 1);
        graph.addEdge('b', 'e', 1);
        graph.addEdge('b', 'c', 1);
        graph.addEdge('c', 'd', 1);
        graph.addEdge('d', 'c', 1);
        graph.addEdge('e', 'f', 1);
        graph.addEdge('b', 'f', 1);
        graph.addEdge('f', 'g', 1);
        graph.addEdge('g', 'f', 1);
        graph.addEdge('c', 'g', 1);
        graph.addEdge('g', 'h', 1);
        graph.addEdge('d', 'h', 1);
        graph.addEdge('h', 'h', 1);
        std::map<char, int> sccs = kosaraju_scc(graph);
        for (auto pr : sccs)
        {
            std::cout << pr.first << " " << pr.second << std::endl;
        }
    }
}
