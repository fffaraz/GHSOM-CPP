#include "neuron.h"
#include "map.h"

Neuron::Neuron(int vectorSize)
{
    vector.reserve(vectorSize);
    for(int i = 0; i < vectorSize; ++i)
        vector.append(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

Neuron::~Neuron()
{
    if(has_map) delete map;
}

float Neuron::distance(Neuron *other) const
{
    return distance(other->vector);
}

float Neuron::distance(const Vector &other) const
{
    return vector.distanceTo(other);
}

void Neuron::resetQuant()
{
    quant = 0;
    quant_list.clear();
}

void Neuron::addQuant(const Vector &v, int i)
{
    quant += vector.distanceTo(v);
    quant_list.append(i);
}

void Neuron::print() const
{
    cout << "(";
    for(int i = 0; i < vector.size(); ++i)
    {
        cout << fixed << setprecision(2) << vector[i];
        if(i != vector.size() - 1) cout << ",";
    }
    cout << ";" << quant << ",";
    cout << quant_list.size();
    if(has_map) cout << "+";
    else cout << "_";
    cout << ")";
}
