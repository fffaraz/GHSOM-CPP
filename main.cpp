#include <QApplication>
#include "common.h"
#include "map.h"
#include "gui.h"

QList<Vector> readCSV(QString path)
{
    QList<Vector> result;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString configLine = file.readLine().trimmed();
        QStringList confList = configLine.split(',');
        if(confList.size() < 2) return result;
        bool has_name = confList[0].toInt();
        int features  = confList[1].toInt();
        bool startIdx = has_name ? 1 : 0;
        while(!file.atEnd())
        {
            QString line = file.readLine().trimmed();
            if(line.size() < 1) continue;
            QStringList items = line.split(',');
            if(items.size() < startIdx + 1) continue;
            Vector v;
            if(has_name)
            {
                v.name = items[0];
                v.has_name = true;
            }
            for(int i = startIdx; i < items.size(); ++i) v.append(items[i].toFloat());
            if(v.size() != features) break;
            result.append(v);
        }
    }
    else
    {
        cout << file.errorString().toStdString() << endl;
    }
    return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //test3();
    auto data_set = readCSV("animals.csv");
    if(data_set.size() > 0)
    {
        Map *map = new Map(data_set[0].size());
        map->train(data_set);
        map->print();
        new GUI(map);
    }
    cout << "\nDONE.\n";
    cout.flush();
    return a.exec();
}
