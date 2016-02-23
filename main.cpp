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
        if(confList.size() < 4) return result;
        bool has_name   = confList[0].toInt();
        int  features   = confList[1].toInt();
        bool has_minmax = confList[2].toInt();
        bool has_header = confList[3].toInt();
        bool startIdx = has_name ? 1 : 0;
        QVector<float> minVec, maxVec;
        if(has_minmax)
        {
            QString minLine = file.readLine().trimmed();
            QString maxLine = file.readLine().trimmed();
            QStringList mins = minLine.split(',', QString::SkipEmptyParts);
            QStringList maxs = maxLine.split(',', QString::SkipEmptyParts);
            if(mins.size() != features || maxs.size() != features) return result;
            for (int i = 0; i < features; ++i)
            {
                minVec.append(mins[i].toFloat());
                maxVec.append(maxs[i].toFloat());
            }
        }
        if(has_header) file.readLine();
        while(!file.atEnd())
        {
            QString line = file.readLine().trimmed();
            if(line.size() < 1) continue;
            QStringList items = line.split(',');
            if(items.size() != startIdx + features) continue;
            Vector v;
            if(has_name)
            {
                v.name = items[0];
                v.has_name = true;
            }
            for(int i = startIdx; i < items.size(); ++i)
            {
                if(has_minmax)
                {
                    float n = items[i].toFloat();
                    float min = minVec[i - startIdx];
                    float max = maxVec[i - startIdx];
                    if(min < max)
                    {
                        float r = (n-min)/(max-min);
                        v.append(r);
                    }
                    else
                    {
                        v.append(0);
                    }
                }
                else
                {
                    v.append(items[i].toFloat());
                }
            }
            if(v.size() != features) continue;
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
