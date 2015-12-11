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
            v.name = QString::number(v[0], 'f', 2) + ", " + QString::number(v[1], 'f', 2);
            v.has_name = true;
            sample.append(v);
        }
    }
    Map *map = new Map(2);
    map->print();
    map->train(sample);
    map->print();
    cout << endl << endl;
    Vector v;
    v.append(0.1);
    v.append(0.9);
    auto cluster = map->findRecursive(v);
    for(int i = 0; i < cluster.size(); ++i)
    {
        cout << "[" << cluster[i].first << ", " << cluster[i].second << "], ";
    }
    new GUI(map);
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

Vector fillVector(QString flags, QString name)
{
    Vector v;
    v.name = name;
    v.has_name = true;
    for(int i = 0; i < flags.size(); ++i) if(flags[i].toLatin1() == '1') v.append(1); else if (flags[i].toLatin1() == '0') v.append(0);
    return v;
}

void test3()
{
    QList<Vector> data_set;
    /*
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 0 0 1 0", "Dove"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 0 0 0 0", "Chicken"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 0 0 0 1", "Duck"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 0 0 1 1", "Goose"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 1 0 1 0", "Owl"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 1 1 0 1 0", "Hawk"));
    data_set.append(fillVector("0 1 0 1 0 0 0 0 1 1 0 1 0", "Eagle"));
    data_set.append(fillVector("0 1 0 0 1 1 0 0 0 1 0 0 0", "Fox"));
    data_set.append(fillVector("0 1 0 0 1 1 0 0 0 0 1 0 0", "Dog"));
    data_set.append(fillVector("0 1 0 0 1 1 0 1 0 1 1 0 0", "Wolf"));
    data_set.append(fillVector("1 0 0 0 1 1 0 0 0 1 0 0 0", "Cat"));
    data_set.append(fillVector("0 0 1 0 1 1 0 0 0 1 1 0 0", "Tiger"));
    data_set.append(fillVector("0 0 1 0 1 1 0 1 0 1 1 0 0", "Lion"));
    data_set.append(fillVector("0 0 1 0 1 1 1 1 0 0 1 0 0", "Horse"));
    data_set.append(fillVector("0 0 1 0 1 1 1 1 0 0 1 0 0", "Zebra"));
    data_set.append(fillVector("0 0 1 0 1 1 1 0 0 0 0 0 0", "Cow"));
    */
    // Small Medium Big 2-Legs 4-Legs Hair Scales Hooves Gills Mane Feathers Fins Hunt Run Fly Swim
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 0 0 1 0", " Dove"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 0 0 0 0", " Chicken"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 0 0 0 1", " Duck"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 0 0 1 1", " Goose"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 1 0 1 0", " Owl"));
    data_set.append(fillVector("1 0 0 1 0 0 0 0 0 0 1 0 1 0 1 0", " Hawk"));
    data_set.append(fillVector("0 1 0 1 0 0 0 0 0 0 1 0 1 0 1 0", " Eagle"));
    data_set.append(fillVector("0 1 0 0 1 1 0 0 0 0 0 0 1 0 0 0", " Fox"));
    data_set.append(fillVector("0 1 0 0 1 1 0 0 0 0 0 0 0 1 0 0", " Dog"));
    data_set.append(fillVector("0 1 0 0 1 1 0 0 0 1 0 0 1 1 0 0", " Wolf"));
    data_set.append(fillVector("1 0 0 0 1 1 0 0 0 0 0 0 1 0 0 0", " Cat"));
    data_set.append(fillVector("0 0 1 0 1 1 0 0 0 0 0 0 1 1 0 0", " Tiger"));
    data_set.append(fillVector("0 0 1 0 1 1 0 0 0 1 0 0 1 1 0 0", " Lion"));
    data_set.append(fillVector("0 0 1 0 1 1 0 1 0 1 0 0 0 1 0 0", " Horse"));
    data_set.append(fillVector("0 0 1 0 1 1 0 1 0 1 0 0 0 1 0 0", " Zebra"));
    data_set.append(fillVector("0 0 1 0 1 1 0 1 0 0 0 0 0 0 0 0", " Cow"));
    data_set.append(fillVector("1 0 0 0 1 0 1 0 0 0 0 0 1 0 0 0", " Lizard"));
    data_set.append(fillVector("0 1 0 0 0 0 1 0 0 0 0 0 1 0 0 1", " Snake"));
    data_set.append(fillVector("0 0 0 0 1 0 1 0 0 0 0 0 1 0 0 1", " Crocodile"));
    data_set.append(fillVector("1 0 0 0 1 0 1 0 0 0 0 0 0 0 0 1", " Turtle"));
    data_set.append(fillVector("1 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0", " Tortoise"));
    data_set.append(fillVector("1 0 0 0 0 0 1 0 1 0 0 1 0 0 0 1", " Bass"));
    data_set.append(fillVector("0 1 0 0 0 0 1 0 1 0 0 1 1 0 0 1", " Trout"));
    data_set.append(fillVector("0 0 1 0 0 0 0 0 1 0 0 1 1 0 0 1", " Shark"));
    data_set.append(fillVector("0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 1", " Dolphin"));
    Map *map = new Map(16);
    map->train(data_set);
    map->print();
    new GUI(map);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test3();

    cout.flush();
    return a.exec();
}
