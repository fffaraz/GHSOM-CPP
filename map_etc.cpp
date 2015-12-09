#include "map.h"

void Map::print(bool printv, int tab) const
{
    string strtab = "";
    for (int i = 0; i < tab; ++i) strtab.append("    ");
    cout << strtab << "iteration  : " << iteration << endl;
    cout << strtab << "input_size : " << input_size << endl;
    if(printv)
    {
        cout << strtab << "mean : (";
        for(int i = 0; i < mean.size(); ++i) cout << mean[i] << ",";
        cout << ")\n";
    }
    cout << strtab << "mqr0 : " << mqe0 << endl;
    cout << strtab << "MQR  : " << mqe << endl;
    cout << strtab << "size : " << network.size() << " x " << network[0].size() << endl;
    for(int i = 0; i < network.size(); ++i)
    {
        cout << strtab;
        for(int j = 0; j < network[i].size(); ++j)
        {
            network[i][j]->print(printv);
            //cout << " ";
        }
        cout << endl;
    }
    for(int i = 0; i < network.size(); ++i)
    {
        for(int j = 0; j < network[i].size(); ++j)
        {
            if(network[i][j]->has_map)
            {
                cout << strtab << "+++ [" << i << ", " << j << "]\n";
                network[i][j]->map->print(printv, tab + 1);
            }
        }
    }
    cout << strtab << "---\n";
}
