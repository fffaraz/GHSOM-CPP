#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "neuron.h"
#include "vector.h"

using Point = QPair<int, int>;

class Map
{
public:
    Map(int vector_size, int init_r = 2, int init_c = 2);
    ~Map();
    void print(bool printv = false, int tab = 0) const;
    void train(const QList<Vector> &input, int max_iterations = 5000);
    Point findBestMatch(const Vector &v) const;
    QList<Point> findRecursive(const Vector &v) const;
    QList<QList<Neuron*>> network;

private:
    Vector mean;
    int iteration = 0;
    int input_size = 0;
    int vectorSize;
    float mqe0 = 0;
    float mqe  = 0;
    void  learn(const Vector &v, float curr_alpha);
    void  calcMean (const QList<Vector> &input);
    void  calcQuant(const QList<Vector> &input);
    void  grow();
    Point findMaxErrorUnit() const;
    Point findMaxDistLink(Point e, int &dir) const;
    QList<Neuron*> addRow(int r) const;
    QList<Neuron*> addColumn(int c) const;
    int markAllHierarchyUnits();

protected:
    int   lambda = 50;
    float tau_1 = 0.50;
    float tau_2 = 0.50;
    float alpha() const;
    float theta(Point u, int x, int y) const;
};

#endif // MAP_H
