#include "jsontreeview.h"

JsonTreeView::JsonTreeView(const QString &configPath, QWidget *parent) : QWidget(parent)
{
    init(configPath);
    settings();
    setupLayout();
    connects();
}

/*!
 * \brief JsonTreeView::init - инициализация формы
 */
void JsonTreeView::init(const QString &configPath)
{
    mainLayout = new QGridLayout(this);
    treeView = new QTreeView(this);
    model = new JsonTreeModel(configPath, this);
}

/*!
 * \brief JsonTreeView::settings - настройки формы
 */
void JsonTreeView::settings()
{
    // Установка модели
    treeView->setModel(model);

    // Настройки главной формы
    this->setWindowTitle("Tree json");
}

/*!
 * \brief JsonTreeView::setupLayout - установка слоя
 */
void JsonTreeView::setupLayout()
{
    mainLayout->addWidget(treeView);

    this->setLayout(mainLayout);
}

/*!
 * \brief JsonTreeView::connects - соединения
 */
void JsonTreeView::connects() {}
