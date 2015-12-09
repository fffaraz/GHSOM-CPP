#include "gui.h"

GUI::GUI(Map *map, QObject *parent) : QObject(parent), map(map)
{
    QFont font;
    font.setBold(true);
    QTableWidget *tw = new QTableWidget();
    connect(tw, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(cellDoubleClicked(int,int)));
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tw->setSelectionMode(QAbstractItemView::SingleSelection);
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
    tw->adjustSize();
    tw->show();
}

void GUI::cellDoubleClicked(int r, int c)
{
    if(!map->network[r][c]->has_map) return;
    new GUI(map->network[r][c]->map, this);
}
