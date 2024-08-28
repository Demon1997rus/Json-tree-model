#ifndef JSONNODE_H
#define JSONNODE_H

#include <QList>
#include <QString>
#include <QVariant>

class JsonNode {
public:
    JsonNode(const QString &key, const QVariant &value = QVariant(),
             JsonNode *parent = Q_NULLPTR);
    ~JsonNode();

public:
    void appendChild(JsonNode *child);
    JsonNode *child(int row) const;
    JsonNode *parent() const Q_DECL_NOTHROW;
    int rowCount() const Q_DECL_NOTHROW;
    const QString &key() const;
    const QVariant &value() const;
    int row() const;

private:
    JsonNode *m_parent;
    QList<JsonNode *> m_children;
    QString m_key;
    QVariant m_value;
};

#endif // JSONNODE_H
