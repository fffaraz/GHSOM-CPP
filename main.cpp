#include <QCoreApplication>

#include "common.h"
#include "map.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<Vector> sample;
    for (int i = 0; i < 11; ++i)
    {
        for (int j = 0; j < 11; ++j)
        {
            Vector v;
            v.append(i/10.0f);
            v.append(j/10.0f);
            sample.append(v);
        }
    }
    Map map(2);
    map.print();
    map.train(sample);
    map.print();
    cout << endl << endl;
    Vector v;
    v.append(0.1);
    v.append(0.9);
    auto cluster = map.findRecursive(v);
    for(int i = 0; i < cluster.size(); ++i)
    {
        cout << "[" << cluster[i].first << ", " << cluster[i].second << "], ";
    }
    cout << endl;
    cout.flush();

    a.processEvents();
    return 0; //a.exec();
}
