#ifndef CWORLDINFOSIDEBAR_H
#define CWORLDINFOSIDEBAR_H

#include <QWidget>
#include <QSortFilterProxyModel>
#include "CWorldTreeModel.h"

class CWorldEditor;

namespace Ui {
class CWorldInfoSidebar;
}

class CWorldInfoSidebar : public QWidget
{
    Q_OBJECT

    Ui::CWorldInfoSidebar *mpUI;
    CWorldTreeModel mModel;
    CWorldTreeProxyModel mProxyModel;

public:
    explicit CWorldInfoSidebar(CWorldEditor *pEditor);
    ~CWorldInfoSidebar();

public slots:
    void OnActiveProjectChanged(CGameProject *pProj);
    void OnAreaFilterStringChanged(const QString& rkFilter);
    void OnWorldTreeClicked(QModelIndex Index);
    void OnWorldTreeDoubleClicked(QModelIndex Index);
    void ClearWorldInfo();
    void ClearAreaInfo();
};

#endif // CWORLDINFOSIDEBAR_H
