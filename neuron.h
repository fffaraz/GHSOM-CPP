#ifndef NEURON_H
#define NEURON_H

#include "common.h"
#include "vector.h"

class Map;

class Neuron
{
public:
    Vector vector;
    float  quant = 0;
    QList<int> quant_list;
    bool   has_map = false;
    Map   *map = 0;
    Neuron(int vectorSize);
    ~Neuron();
    void print(bool printv = true) const;
    void resetQuant();
    void addQuant(const Vector &v, int i);
    float distance(Neuron* other) const;
    float distance(const Vector &other) const;
};

#endif // NEURON_H
