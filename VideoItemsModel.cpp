#include "VideoItemsModel.h"
#include <QDir>
#include <QDebug>
#include <QFile>
#include "Utils.h"

VideoItemsModel::VideoItemsModel(QObject *parent)
    : QAbstractListModel(parent),
      m_listItems(QList<VideoItem>())
{
}

int VideoItemsModel::rowCount(const QModelIndex &parent) const
{
    return m_listItems.count();
}

QVariant VideoItemsModel::data(const QModelIndex &index, int role) const
{
    VideoItem videoItem = m_listItems.at(index.row());

    switch (role)
    {
    case IconRole:
        return QVariant(videoItem.icon);
    case NameRole:
        return QVariant(videoItem.name);
    case PathRole:
        return QVariant(videoItem.path);

    default:
        break;
    }

    return QVariant();
}


QHash<int, QByteArray> VideoItemsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IconRole] = "icon";
    names[NameRole] = "name";
    names[PathRole] = "path";
    return names;
}

void VideoItemsModel::updateListItems(QString name)
{
    beginResetModel();
    m_listItems.clear();

    QDir dir(name);
    QStringList lista = dir.entryList(QStringList() << "*.avi" << "*.AVI",QDir::Files);
    foreach(QString path, lista)
    {
        QString putanja = dir.absoluteFilePath(path);
        QFile file(putanja);

        VideoItem item;
        item.name = path;
        item.path = putanja;
        item.icon = Utils::getInstance()->createThumbnails(putanja);

        m_listItems.append(item);
    }
    endResetModel();
}


Qt::ItemFlags VideoItemsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}
