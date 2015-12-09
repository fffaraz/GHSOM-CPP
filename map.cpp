#include "map.h"

Map::Map(int vector_size, int init_r, int init_c) :
    vectorSize(vector_size)
{
    mean.reserve(vectorSize);
    for(int i = 0; i < vectorSize; ++i) mean.append(0);
    for(int i = 0; i < init_r; ++i)
    {
        QList<Neuron*> row;
        for(int j = 0; j < init_c; ++j)
        {
            Neuron *n = new Neuron(vectorSize);
            //for(int k = 0; k < vector_size; ++k) n->vector[k] = (i+j)/(init_r+init_c-2.0f);
            //n->vector[0] = i / (init_r - 1.0f);
            //n->vector[1] = j / (init_c - 1.0f);
            row.append(n);
        }
        network.append(row);
    }
}

Map::~Map()
{
    for(int i = 0; i < network.size(); ++i)
        for(int j = 0; j < network[i].size(); ++j)
            delete network[i][j];
}

void Map::calcMean(const QList<Vector> &input)
{
    int mean_size = mean.size();
    int input_size = input.size();
    for(int i = 0; i < mean_size; ++i) mean[i] = 0;
    for(int i = 0; i < input_size; ++i)
        for(int j = 0; j < mean_size; ++j)
            mean[j] += input[i][j];
    for(int i = 0; i < mean_size; ++i) mean[i] /= input_size;
    mqe0 = 0;
    for(int i = 0; i < input_size; ++i) mqe0 += input[i].distanceTo(mean);
    mqe0 /= input_size;
}

void Map::calcQuant(const QList<Vector> &input)
{
    for(int i = 0; i < network.size(); ++i)
        for(int j = 0; j < network[i].size(); ++j)
            network[i][j]->resetQuant();
    for(int i = 0; i < input.size(); ++i)
    {
        Point bmu = findBestMatch(input[i]);
        network[bmu.first][bmu.second]->addQuant(input[i], i);
    }
    mqe = 0;
    for(int i = 0; i < network.size(); ++i)
    {
        for(int j = 0; j < network[i].size(); ++j)
        {
            int qs = network[i][j]->quant_list.size();
            if(qs > 0) network[i][j]->quant /= qs;
            mqe += network[i][j]->quant;
        }
    }
    mqe /= network.size() * network[0].size();
}

void Map::train(const QList<Vector> &input, int max_iterations)
{
    input_size = input.size();
    calcMean(input);
    for(;;)
    {
        if(iteration >= max_iterations) break;
        for(int i = 0; i < lambda; ++i)
        {
            iteration++;
            //if(iteration % 2 == 0) cout << "iteration: " << i << endl;
            float my_alpha = alpha();
            for(int j = 0; j < input_size; ++j) learn(input[j], my_alpha);
        }
        calcQuant(input);
        for(int i = 0; i < network.size(); ++i)
        {
            for(int j = 0; j < network[i].size(); ++j)
            {
                Neuron *ne = network[i][j];
                if(ne->has_map)
                {
                    QList<Vector> subInput;
                    for(int k = 0; k < ne->quant_list.size(); ++k)
                        subInput.append(input[ne->quant_list[k]]);
                    if(subInput.size() > 0) ne->map->train(subInput, max_iterations);
                }
            }
        }
        if(mqe > tau_1 * mqe0)
            grow();
        else
        {
            int n = markAllHierarchyUnits();
            if(n < 1) break;
        }
    }
}

void Map::learn(const Vector &v, float curr_alpha)
{
    Point bmu = findBestMatch(v);
    for (int i = 0; i < network.size(); ++i)
    {
        for (int j = 0; j < network[i].size(); ++j)
        {
            Neuron *neuron = network[i][j];
            float my_theta = theta(bmu, i, j);
            for (int k = 0; k < v.size(); ++k)
            {
                float vk = neuron->vector[k];
                neuron->vector[k] = vk + curr_alpha * my_theta * (v[k] - vk);
            }
        }
    }
}

void Map::grow()
{
    Point e = findMaxErrorUnit();
    int dir = -1;
    Point d = findMaxDistLink(e, dir);
    QList<Neuron*> newlist;
    switch(dir)
    {
    case 0:
        newlist = addRow(d.first);
        network.insert(e.first, newlist);
        break;
    case 2:
        newlist = addRow(e.first);
        network.insert(d.first, newlist);
        break;
    case 1:
        newlist = addColumn(e.second);
        for(int i = 0; i < network.size(); ++i) network[i].insert(d.second, newlist[i]);
        break;
    case 3:
        newlist = addColumn(d.second);
        for(int i = 0; i < network.size(); ++i) network[i].insert(e.second, newlist[i]);
        break;
    default:
        cout << "dir =/= 0,1,2,3 !!!\n\n";
        break;
    }
}

QList<Neuron*> Map::addRow(int r) const
{
    QList<Neuron*> result;
    int size = network[r].size();
    for(int i = 0; i < size; ++i)
    {
        Neuron* n = new Neuron(vectorSize);
        for(int j = 0; j < vectorSize; ++j) n->vector[j] = (network[r][i]->vector[j] + network[r+1][i]->vector[j]) / 2.0f;
        result.append(n);
    }
    return result;
}

QList<Neuron*> Map::addColumn(int c) const
{
    QList<Neuron*> result;
    for(int i = 0; i < network.size(); ++i)
    {
        Neuron* n = new Neuron(vectorSize);
        for(int j = 0; j < vectorSize; ++j) n->vector[j] = (network[i][c]->vector[j] + network[i][c+1]->vector[j]) / 2.0f;
        result.append(n);
    }
    return result;
}

float Map::alpha() const
{
    return 0.1f;
    //return qMax(0.1f, 1.0f - (iteration * 0.001f));
}

float Map::theta(Point u, int x, int y) const
{
    if(u.first == x && u.second == y) return 1;
    int dx = u.first - x;
    int dy = u.second - y;
    int dx2 = dx * dx;
    int dy2 = dy * dy;
    if((u.first  == x && dy2 == 1)||(u.second == y && dx2 == 1)) return 0.5;
    //if(dx2 == 1 && dy2 == 1) return 1.0f/1.414f;
    //if(dx2<2 && dy2<2) return 1.0f / sqrt(dx2 + dy2);
    return 0;
}
