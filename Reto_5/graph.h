#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <set>

template <class T>
class GraphVertex
{
private:
    T val;
    std::set<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {
        val = _val;
    };

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::set<int> get_adj() {return adj;};
    void add_to_adj(int idx) {adj.insert(idx);};
};

template <class T>
class Graph
{
private:
    
    bool is_directed;

public:
    std::vector<GraphVertex<T> > nodes;
    ~Graph() {};
    Graph() {is_directed=true;};

    void add_node(T val)
    {
        GraphVertex<T> node(val);
        nodes.push_back(node);
    };

    void add_edge(int src, int dst)
    {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

    void BFS(int start_vertex)
    {
        // Create vector for visited flag
        std::vector<bool> visited(nodes.size(), false);
        
        // Create a queue for BFS 
        std::queue<int> queue;
    
        // Mark the current node as visited and enqueue it 
        visited[start_vertex] = true; 
        queue.push(start_vertex);
            
        while(!queue.empty()) 
        { 
            // Dequeue a vertex from queue and print it 
            int s = queue.front(); 
            // Do something with the vertex
            std::cout << nodes[s].get_val() << " "; 
            queue.pop(); 
    
            // Get all adjacent vertices of the dequeued 
            // vertex s. If a adjacent has not been visited,  
            // then mark it visited and enqueue it 
            for (auto& it: nodes[s].get_adj()) 
            { 
                if (!visited[it]) 
                { 
                    visited[it] = true; 
                    queue.push(it); 
                } 
            }
        } 
        std::cout << std::endl;
    };

    void DFS(int start_vertex)
    {
        // Create vector for visited flag
        std::vector<bool> visited(nodes.size(), false);
        
        // Create a stack for DFS 
        std::stack<int> stack;

        stack.push(start_vertex);
    
            
        while(!stack.empty()) 
        { 
            // Dequeue a vertex from queue and print it 
            int s = stack.top();
            stack.pop();

            if (!visited[s])
            {            
                visited[s] = true;
                // Do something with the vertex
                std::cout << nodes[s].get_val() << " "; 
            }

            // Get all adjacent vertices of the dequeued 
            // vertex s. If a adjacent has not been visited,  
            // then mark it visited and enqueue it 
            for (auto& it: nodes[s].get_adj()) 
            { 
                if (!visited[it]) 
                { 
                    stack.push(it); 
                } 
            }
        } 
        std::cout << std::endl;
    };
};

#endif