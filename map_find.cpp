#include "map.h"

Point Map::findBestMatch(const Vector &v) const
{
    Point minP;
    float minD = FLT_MAX;
    for(int i = 0; i < network.size(); ++i)
    {
        for(int j = 0; j < network[i].size(); ++j)
        {
            float d = network[i][j]->distance(v);
            if(d < minD)
            {
                minD = d;
                minP.first = i;
                minP.second = j;
            }
        }
    }
    return minP;
}

QList<Point> Map::findRecursive(const Vector &v) const
{
    QList<Point> res;
    const Map *map = this;
    for(;;)
    {
        Point p = map->findBestMatch(v);
        res.append(p);
        if(network[p.first][p.second]->has_map)
            map = network[p.first][p.second]->map;
        else
            break;
    }
    return res;
}

Point Map::findMaxErrorUnit() const
{
    Point maxP;
    float maxE = -1;
    for(int i = 0; i < network.size(); ++i)
    {
        for(int j = 0; j < network[i].size(); ++j)
        {
            float e = network[i][j]->quant;
            if(e > maxE)
            {
                maxE = e;
                maxP.first = i;
                maxP.second = j;
            }
        }
    }
    return maxP;
}

Point Map::findMaxDistLink(Point e, int &dir) const
{
    int eR = e.first;
    int eC = e.second;
    int dR[4], dC[4];
    float dE[4] = {-1, -1, -1, -1};
    dR[0] = eR - 1; dC[0] = eC + 0;
    dR[1] = eR + 0; dC[1] = eC + 1;
    dR[2] = eR + 1; dC[2] = eC + 0;
    dR[3] = eR + 0; dC[3] = eC - 1;
    if(dR[0] >= 0 && dR[0] < network.size() && dC[0] >= 0 && dC[0] < network[dR[0]].size()) dE[0] = network[eR][eC]->distance(network[dR[0]][dC[0]]);
    if(dR[1] >= 0 && dR[1] < network.size() && dC[1] >= 0 && dC[1] < network[dR[1]].size()) dE[1] = network[eR][eC]->distance(network[dR[1]][dC[1]]);
    if(dR[2] >= 0 && dR[2] < network.size() && dC[2] >= 0 && dC[2] < network[dR[2]].size()) dE[2] = network[eR][eC]->distance(network[dR[2]][dC[2]]);
    if(dR[3] >= 0 && dR[3] < network.size() && dC[3] >= 0 && dC[3] < network[dR[3]].size()) dE[3] = network[eR][eC]->distance(network[dR[3]][dC[3]]);
    int sD = -1;
    float sE = -2;
    if(sE < dE[0]) { sE = dE[0]; sD = 0; }
    if(sE < dE[1]) { sE = dE[1]; sD = 1; }
    if(sE < dE[2]) { sE = dE[2]; sD = 2; }
    if(sE < dE[3]) { sE = dE[3]; sD = 3; }
    Point d;
    d.first = dR[sD];
    d.second = dC[sD];
    dir = sD;
    return d;
}

int Map::markAllHierarchyUnits()
{
    int num = 0;
    for(int i = 0; i < network.size(); ++i)
    {
        for(int j = 0; j < network[i].size(); ++j)
        {
            Neuron *ne = network[i][j];
            if(ne->quant > tau_2 && ne->has_map == false && ne->quant_list.size() >= 4)
            {
                num++;
                network[i][j]->has_map = true;
                network[i][j]->map = new Map(vectorSize);
            }
        }
    }
    return num;
}
