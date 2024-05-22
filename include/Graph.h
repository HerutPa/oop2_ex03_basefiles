#pragma once

#include <queue>
#include<iostream>
#include <SFML/Graphics.hpp>
#include "Resources.h"


class Graph
{
public:
	Graph(const int);
    const std::vector<bool> BFS(const int, const sf::Color)const;
    const int BFS_Medium(const sf::Color, const sf::Color)const;
    const int BFS_Hard(const sf::Color, const sf::Color)const;
    void addNeighbor(const int, Shape*);
    void clear();

private:
	int m_size;
    std::vector<std::vector<Shape*>> m_neighbors;
};

//inline Graph<Shape>::Graph(const int size)
//	:m_size(size)
//{
//    m_neighbors.resize(m_size);
//}
//
//inline const std::vector<bool> Graph<Shape>::BFS(const int start_node, const sf::Color color )const
//{
//    std::vector<bool> visited(m_size, false);
//    std::queue<int> q;
//
//    visited[start_node] = true;
//    q.push(start_node);
//
//    while (!q.empty())
//    {
//        int node = q.front();
//        q.pop();
//
//        std::vector<Shape*> neighbors = m_neighbors[node];
//      
//        for (int i = 0; i < neighbors.size(); i++) 
//        {
//            int neighbor_node = neighbors[i]->getIndex();
//            if ((!visited[neighbor_node])&& (neighbors[i]->getColor() == color))
//            {
//                visited[neighbor_node] = true;
//                q.push(neighbor_node);
//            }
//        }
//    }
//    return visited;
//}
//
//
//
//inline const int Graph<Shape>::BFS_Medium(const sf::Color my_color, const sf::Color desired_color)const
//{
//    int start_node = COMPUTER_INDEX;
//    int counter = 0;
//    std::vector<bool> visited(m_size, false);
//    std::queue<int> q;
//
//    visited[start_node] = true;
//    q.push(start_node);
//
//    while (!q.empty())
//    {
//        int node = q.front();
//        q.pop();
//
//        std::vector<Shape*> neighbors = m_neighbors[node];
//
//        for (int i = 0; i < neighbors.size(); i++)
//        {
//            int neighbor_node = neighbors[i]->getIndex();
//            if ((!visited[neighbor_node]) && (neighbors[i]->getColor() == my_color))
//            {
//                visited[neighbor_node] = true;
//                q.push(neighbor_node);
//            }
//            else if ((!visited[neighbor_node]) && (neighbors[i]->getColor() == desired_color))
//            {
//                visited[neighbor_node] = true;
//                counter++;
//            }
//        }
//    }
//    return counter;
//}
//
//inline const int Graph<Shape>::BFS_Hard(const sf::Color my_color, const sf::Color desired_color)const
//{
//    int start_node = COMPUTER_INDEX;
//    int counter = 0;
//    std::vector<bool> visited(m_size, false);
//    std::queue<int> q;
//    std::queue<int> q2;
//
//    visited[start_node] = true;
//    q.push(start_node);
//    q2.push(start_node);
//
//    while (!q.empty())
//    {
//        int node = q.front();
//        q.pop();
//
//        std::vector<Shape*> neighbors = m_neighbors[node];
//
//        for (int i = 0; i < neighbors.size(); i++)
//        {
//            int neighbor_node = neighbors[i]->getIndex();
//            if ((!visited[neighbor_node]) && (neighbors[i]->getColor() == my_color))
//            {
//                visited[neighbor_node] = true;
//                q.push(neighbor_node);
//                q2.push(neighbor_node);
//                counter++;
//            }
//        }
//    }
//
//    while (!q2.empty())
//    {
//        int node = q2.front();
//        q2.pop();
//
//        std::vector<Shape*> neighbors = m_neighbors[node];
//
//        for (int i = 0; i < neighbors.size(); i++)
//        {
//            int neighbor_node = neighbors[i]->getIndex();
//            if ((!visited[neighbor_node]) && (neighbors[i]->getColor() == desired_color))
//            {
//                visited[neighbor_node] = true;
//                q2.push(neighbor_node);
//                counter++;
//            }
//        }
//    }
//    return counter;
//}
//
//inline void Graph<Shape>::addNeighbor(const int index, Shape* shape)
//{
//    m_neighbors[index].push_back(shape);
//}
//
//inline void Graph<Shape>::clear()
//{
//    for (int index = 0; index < m_neighbors.size(); index++)
//    {
//        m_neighbors[index].clear();
//    }
//    m_neighbors.clear();
//    m_neighbors.resize(m_size);
//}
//

