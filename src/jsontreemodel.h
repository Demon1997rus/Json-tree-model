#ifndef JSONTREEMODEL_H
#define JSONTREEMODEL_H

#include <QAbstractItemModel>

class JsonNode;
class JsonTreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit JsonTreeModel(const QString &configPath, QObject *parent = Q_NULLPTR);
    virtual ~JsonTreeModel();

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role) const override;

private:
    JsonNode *findNode(const QModelIndex &index) const;

    // function builder tree json
private:
    void setDataFromJsonObject(JsonNode *parent, const QJsonObject &object) const;
    void setDataFromJsonArray(JsonNode *parent, const QJsonArray &array) const;

private:
    JsonNode *m_root = Q_NULLPTR;
};

#endif // JSONTREEMODEL_H
