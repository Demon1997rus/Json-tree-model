#include "jsonnode.h"

JsonNode::JsonNode(const QString &key, const QVariant &value, JsonNode *parent) :
    m_parent(parent), m_key(key), m_value(value)
{
    if (m_parent) {
        m_parent->appendChild(this);
    }
}

JsonNode::~JsonNode()
{
    qDeleteAll(m_children);
}

void JsonNode::appendChild(JsonNode *child)
{
    m_children << child;
}

JsonNode *JsonNode::child(int row) const
{
    return m_children.value(row, Q_NULLPTR);
}

JsonNode *JsonNode::parent() const Q_DECL_NOTHROW
{
    return m_parent;
}

int JsonNode::rowCount() const Q_DECL_NOTHROW
{
    return m_children.size();
}

const QString &JsonNode::key() const
{
    return m_key;
}

const QVariant &JsonNode::value() const
{
    return m_value;
}

int JsonNode::row() const
{
    if (m_parent) {
        return m_parent->m_children.indexOf(const_cast<JsonNode *>(this));
    }
    return 0;
}
