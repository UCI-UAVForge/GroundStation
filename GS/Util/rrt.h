#ifndef RRT_H
#define RRT_H

#include <stdlib.h>
#include <vector>
#include <math.h>
#include "vect.h"
#include "point.hpp"
#include "obstacles.h"


struct Node {
    std::vector<Node *> children;
    Node *parent;
    Vect position;
};

class RRT
{
public:
    RRT(Point start, Point end, Obstacles o);
    void initialize();
    Node* getRandomNode();
    Node* nearest(Vect point);
    int distance(Vect &p, Vect &q);
    Vect newConfig(Node *q, Node *qNearest);
    void add(Node *qNearest, Node *qNew);
    bool reached();
    void setStepSize(int step);
    void setMaxIterations(int iter);
    void deleteNodes(Node *root);
    Obstacles obstacles;
    std::vector<Node *> nodes;
    std::vector<Node *> path;
    Node *root, *lastNode;
    Vect startPos, endPos;
    int max_iter;
    int step_size;
};

#endif // RRT_H
