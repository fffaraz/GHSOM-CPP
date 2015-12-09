#include <QApplication>
#include "common.h"
#include "map.h"
#include "gui.h"

void test1()
{
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
}

void test2()
{
    QFile file("plants.data");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << file.errorString();
        return;
    }
    QString content = file.readAll();
    QStringList lines = content.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QMultiHash<QString, QString> data;
    QList<QString> states;
    QList<QString> names;
    foreach(QString line, lines)
    {
        QStringList fields = line.split(",");
        QString name = fields[0].replace(" ", "_");
        if(!names.contains(name)) names.append(name);
        for(int i = 1; i < fields.size(); ++i)
        {
            QString state = fields[i];
            data.insertMulti(name, state);
            if(!states.contains(state)) states.append(state);
        }
    }

    QList<Vector> data_set;
    foreach(QString name, names)
    {
        Vector v;
        auto values = data.values(name);
        foreach(QString state, states)
        {
            if(values.contains(state))
                v.append(1);
            else
                v.append(0);
        }
        data_set.append(v);
    }
    cout << data_set.size() << endl;
    Map *map = new Map(states.size());
    map->train(data_set);
    map->print();
    new GUI(map);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test2();
    cout << endl;
    cout.flush();

    return a.exec();
}
