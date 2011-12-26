#ifndef JROOMLISTMODEL_H
#define JROOMLISTMODEL_H

#include "../common/jroom.h"

#include <QAbstractTableModel>

class JRoomModelClientRoomProcessor;

class JRoomListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit JRoomListModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent = QModelIndex())const;
	int columnCount(const QModelIndex &parent = QModelIndex())const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
	QList<JRoom> m_roomlist;
    JRoomModelClientRoomProcessor* m_processor;
private slots:
    void on_processor_receiveRoomInfo(const JRoom& room);
    void on_processor_receiveRoomList(const QList<JRoom>& roomlist);
};

#endif // JROOMLISTMODEL_H
