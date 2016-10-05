#pragma once

#include <QAbstractListModel>
#include <QJsonArray>
#include "Attribute.hpp"

namespace nodeeditor
{

class AttributeCollection : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum AttributeRoles
    {
        NameRole = Qt::UserRole + 1,
        KeyRole,
        TooltipRole,
        TypeRole,
        MinRole,
        MaxRole,
        StepRole,
        OptionsRole,
        ValueRole,
        ModelDataRole
    };
    Q_ENUMS(AttributeRoles)

public:
    AttributeCollection(QObject* parent = 0);
    AttributeCollection(const AttributeCollection& obj) = delete;
    AttributeCollection& operator=(AttributeCollection const&) = delete;

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

public:
    Q_SLOT bool add(Attribute*);
    Q_SLOT bool remove(Attribute*);
    Q_SLOT void clear();
    Q_SLOT int rowIndex(Attribute*) const;
    Q_SLOT int rowIndex(const QString&) const;
    Q_SLOT QVariantMap toVMap(int) const;
    Q_SLOT QJsonArray serializeToJSON() const;
    Q_SLOT void deserializeFromJSON(const QJsonArray&);
    Q_SIGNAL void countChanged(int);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Attribute*> _attributes;
};

} // namespace