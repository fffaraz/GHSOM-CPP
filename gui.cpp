#include "gui.h"

GUI::GUI(Map *map, bool list, int x, int y, QObject *parent) : QObject(parent), map(map)
{
    QTableWidget *tw = new QTableWidget();
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tw->setSelectionMode(QAbstractItemView::SingleSelection);
    if(!list)
    {
        QFont font;
        font.setBold(true);
        connect(tw, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(cellDoubleClicked(int,int)));
        tw->verticalHeader()->setDefaultSectionSize(50);
        tw->horizontalHeader()->setDefaultSectionSize(50);
        tw->setRowCount(map->network.size());
        tw->setColumnCount(map->network[0].size());
        for(int i = 0; i < map->network.size(); ++i)
        {
            for(int j = 0; j < map->network[i].size(); ++j)
            {
                tw->setItem(i, j, new QTableWidgetItem(QString::number(map->network[i][j]->quant_list.size())));
                if(map->network[i][j]->has_map) tw->item(i, j)->setFont(font);
            }
        }
    }
    else
    {
        tw->setColumnCount(1);
        tw->setRowCount(map->network[x][y]->quant_names.size());
        for (int i = 0; i < map->network[x][y]->quant_names.size(); ++i)
        {
            tw->setItem(i, 0, new QTableWidgetItem(map->network[x][y]->quant_names[i]));
        }
    }
    tw->adjustSize();
    tw->show();
}

void GUI::cellDoubleClicked(int r, int c)
{
    if(map->network[r][c]->has_map)
        new GUI(map->network[r][c]->map, false, 0, 0, this);
    else if(map->network[r][c]->quant_names.size() > 0)
        new GUI(map, true, r, c, this);
}
