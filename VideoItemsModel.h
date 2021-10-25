#ifndef VIDEOITEMSMODEL_H
#define VIDEOITEMSMODEL_H

#include <QAbstractListModel>

struct VideoItem
{
    QString path;
    QString name;
    QString icon;
};

class VideoItemsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VideoItemsModel(QObject *parent = nullptr);

    enum {
        IconRole = Qt::UserRole,
        NameRole,
        PathRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void updateListItems(QString name);

private:
    int test;
    QList<VideoItem> m_listItems;

};

#endif // VIDEOITEMSMODEL_H
