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
    quant_names.clear();
}

void Neuron::addQuant(const Vector &v, int i)
{
    quant += vector.distanceTo(v);
    quant_list.append(i);
    if(v.has_name) quant_names.append(v.name);
}

void Neuron::print(bool printv) const
{
    cout << "(";
    if(printv)
    {
        for(int i = 0; i < vector.size(); ++i)
        {
            cout << fixed << setprecision(2) << vector[i];
            if(i != vector.size() - 1) cout << ",";
        }
        cout << ";";
        cout << fixed << setprecision(1) << quant << ",";
    }
    cout << quant_list.size();
    if(has_map) cout << "+";
    else cout << "_";
    cout << ")";
}
