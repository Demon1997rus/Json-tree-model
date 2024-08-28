#include "jsontreemodel.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "jsonnode.h"

JsonTreeModel::JsonTreeModel(const QString &configPath, QObject *parent) :
    QAbstractItemModel(parent), m_root(new JsonNode("key", "value"))
{
    QFile file(configPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal("%s Config opening failed %s", Q_FUNC_INFO, file.errorString().toUtf8().data());
    }
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError) {
        qFatal("%s Json opening failed %s", Q_FUNC_INFO,
               jsonError.errorString().toUtf8().data());
    }

    if (document.isObject()) {
        setDataFromJsonObject(m_root, document.object());
    } else if (document.isArray()) {
        setDataFromJsonArray(m_root, document.array());
    }
}

JsonTreeModel::~JsonTreeModel()
{
    delete m_root;
}

QModelIndex JsonTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
    return createIndex(row, column, findNode(parent)->child(row));
}

QModelIndex JsonTreeModel::parent(const QModelIndex &child) const
{
    JsonNode *parent = findNode(child)->parent();
    if (parent == m_root) {
        return QModelIndex();
    }
    return createIndex(parent->row(), 0, parent);
}

int JsonTreeModel::rowCount(const QModelIndex &parent) const
{
    return findNode(parent)->rowCount();
}

int JsonTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 2;
}

QVariant JsonTreeModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {

        switch (index.column()) {
            case 0: return findNode(index)->key();
            case 1: return findNode(index)->value();
        }
    }
    return QVariant();
}

QVariant JsonTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return m_root->key();
            case 1: return m_root->value();
        }
    }
    return QVariant();
}

JsonNode *JsonTreeModel::findNode(const QModelIndex &index) const
{
    if (index.isValid()) {
        JsonNode *node = static_cast<JsonNode *>(index.internalPointer());
        if (node) {
            return node;
        }
    }
    return m_root;
}

void JsonTreeModel::setDataFromJsonObject(JsonNode *parent, const QJsonObject &object) const
{
    for (QJsonObject::const_iterator it = object.begin(); it != object.end(); ++it) {
        const QString key = it.key();
        const QJsonValue value = it.value();
        if (value.isObject()) {
            setDataFromJsonObject(new JsonNode(key, QVariant(), parent), value.toObject());
        } else if (value.isArray()) {
            setDataFromJsonArray(new JsonNode(key, QVariant(), parent), value.toArray());
        } else {
            new JsonNode(key, value.toVariant(), parent);
        }
    }
}

void JsonTreeModel::setDataFromJsonArray(JsonNode *parent, const QJsonArray &array) const
{
    for (int i = 0; i < array.size(); ++i) {
        const QString key = parent->key() + QString("[%1]").arg(i);
        const QJsonValue value = array.at(i);
        if (value.isObject()) {
            setDataFromJsonObject(new JsonNode(key, QVariant(), parent), value.toObject());
        } else if (value.isArray()) {
            setDataFromJsonArray(new JsonNode(key, QVariant(), parent), value.toArray());
        } else {
            new JsonNode(key, value.toVariant(), parent);
        }
    }
}
