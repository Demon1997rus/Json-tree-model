#ifndef JSONTREEVIEW_H
#define JSONTREEVIEW_H

#include <QGridLayout>
#include <QTreeView>
#include <QWidget>

#include "jsontreemodel.h"

class JsonTreeView : public QWidget {
    Q_OBJECT
public:
    explicit JsonTreeView(const QString &configPath, QWidget *parent = Q_NULLPTR);

private:
    void init(const QString &configPath);
    void settings();
    void setupLayout();
    void connects();

private:
    QGridLayout *mainLayout = Q_NULLPTR;
    QTreeView *treeView = Q_NULLPTR;
    JsonTreeModel *model = Q_NULLPTR;
};

#endif // JSONTREEVIEW_H
