#include "rrt.h"
const int WORLD_WIDTH = 7e6;
const int WORLD_HEIGHT = 6e6;
const int WORLD_Z = 5e6;
const int END_DIST_THRESHOLD = 500;
RRT::RRT(Point start, Point end, Obstacles obstacles)
{
    this->obstacles = obstacles;
    startPos = Vect(start.x, start.y, start.z);
    endPos = Vect(end.x, end.y, end.z);
    root = new Node;
    root->parent = NULL;
    root->position = startPos;
    lastNode = root;
    nodes.push_back(root);
    step_size = 50;
    max_iter = 1000;
}

/**
 * @brief Initialize root node of RRT.
 */
void RRT::initialize()
{
    root = new Node;
    root->parent = NULL;
    root->position = startPos;
    lastNode = root;
    nodes.push_back(root);
}

/**
 * @brief getRand
 * @return uniformly distributed number from [-1, 1)
 */
static double getRand() {
    return 2 * (drand48() - 0.5);
}

/**
 * @brief Generate a random node in the field.
 * @return
 */
Node* RRT::getRandomNode()
{
    // compile pls
    Node* ret;
    Vect point(getRand() * WORLD_WIDTH, getRand() * WORLD_HEIGHT, getRand() * WORLD_Z);
    ret = new Node;
    ret->position = point;
    return ret;
}

Node* RRT::perturb(double x, double y, double z, double dist) {
    Node* ret = new Node;
    Vect point(getRand()*dist + x, getRand()*dist + y, z);
    ret->position = point;
    return ret;
}

/**
 * @brief Helper method to find distance between two positions.
 * @param p
 * @param q
 * @return
 */
double RRT::distance(Vect &p, Vect &q)
{
    Vect v = p - q;
    return sqrt(powf(v.getX(), 2) + powf(v.getY(), 2) + powf(v.getZ(), 2));
}

/**
 * @brief Get nearest node from a given configuration/position.
 * @param point
 * @return
 */
Node* RRT::nearest(Vect point)
{
    double minDist = 1e9;
    Node *closest = NULL;
    for(size_t i = 0; i < nodes.size(); ++i) {
        double dist = distance(point, nodes[i]->position);
        if (dist < minDist) {
            minDist = dist;
            closest = nodes[i];
        }
    }
    if(closest) {
        qInfo() << "selected nearest: " << Point::fromECEF(closest->position.getX(), closest->position.getY(), closest->position.getZ()).toGeodetic()
                << "with dist" << minDist << "out of:" << nodes.size();
    }
    return closest;
}

/**
 * @brief Find a configuration at a distance step_size from nearest node to random node.
 * @param q
 * @param qNearest
 * @return
 */
Vect RRT::newConfig(Node *q, Node *qNearest)
{
    Vect to = q->position;
    Vect from = qNearest->position;
    Vect intermediate = to - from;
    intermediate = intermediate / intermediate.normalized();
    Vect ret = from + (intermediate * step_size);
    return ret;
}

/**
 * @brief Add a node to the tree.
 * @param qNearest
 * @param qNew
 */
void RRT::add(Node *qNearest, Node *qNew)
{
    qNew->parent = qNearest;
    qNearest->children.push_back(qNew);
    nodes.push_back(qNew);
    lastNode = qNew;
}

/**
 * @brief Check if the last node is close to the end position.
 * @return
 */
bool RRT::reached()
{
    if (distance(lastNode->position, endPos) < END_DIST_THRESHOLD)
        return true;
    return false;
}

void RRT::setStepSize(int step)
{
    step_size = step;
}

void RRT::setMaxIterations(int iter)
{
    max_iter = iter;
}

/**
 * @brief Delete all nodes using DFS technique.
 * @param root
 */
void RRT::deleteNodes(Node *root)
{
    for(int i = 0; i < (int)root->children.size(); i++) {
        deleteNodes(root->children[i]);
    }
    delete root;
}
