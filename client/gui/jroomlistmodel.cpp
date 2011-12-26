#include "jroomlistmodel.h"

#include "network/jroommodelclientroomprocessor.h"

JRoomListModel::JRoomListModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    m_processor = JRoomModelClientRoomProcessor::getInstance();
    connect(m_processor,
            SIGNAL(receiveRoomInfo(JRoom)),
            SLOT(on_processor_receiveRoomInfo(JRoom)));
    connect(m_processor,
            SIGNAL(receiveRoomList(QList<JRoom>)),
            SLOT(on_processor_receiveRoomList(QList<JRoom>)));
}

int JRoomListModel::rowCount(const QModelIndex &)const
{
	return m_roomlist.count();
}

int JRoomListModel::columnCount(const QModelIndex &)const
{
	// id title num max
	return 4;
}

QVariant JRoomListModel::data(const QModelIndex &index, int role)const
{
	const JRoom& room = m_roomlist.at(index.row());
	switch(role){
	case Qt::DisplayRole:
		switch(index.column()){
		case 0:
			return room.getRoomId();
			break;
		case 1:
			return room.getTitle();
			break;
		case 2:
			return room.getNum();
			break;
		case 3:
			return room.getMax();
			break;
        default:
			break;
		}

		break;
    default:
		break;
	}
	return QVariant();
}

QVariant JRoomListModel::headerData(int section, Qt::Orientation orientation,
                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return "room ID";
            break;
        case 1:
            return "room title";
            break;
        case 2:
            return "plays count";
            break;
        case 3:
            return "max count";
            break;
        default:
            return QString("Column %1").arg(section);
        }
    }else{
        return QVariant();
    }
}

//void JRoomListModel::on_processor_receiveRoomAdded(const JRoom& room)
//{
//    int len = m_roomlist.length();
//    beginInsertRows(QModelIndex(),len,len);
//    m_roomlist.push_back(room);
//    endInsertRows();
//}

void JRoomListModel::on_processor_receiveRoomInfo(const JRoom& room)
{
    int len = m_roomlist.length();
    for(int i=0;i<len;++i){
        if(m_roomlist.at(i).getRoomId() == room.getRoomId()){
            m_roomlist[i] = room;
            emit dataChanged(index(i,0),index(i,4));
            return;
        }
    }
    beginInsertRows(QModelIndex(),len,len);
    m_roomlist.push_back(room);
    endInsertRows();
}

void JRoomListModel::on_processor_receiveRoomList(const QList<JRoom>& roomlist)
{
    bool insert = (roomlist.length()>m_roomlist.length());
    if(insert){
        beginInsertRows(QModelIndex(),m_roomlist.length(),roomlist.length()-1);
    }
    m_roomlist = roomlist;
    if(insert){
        endInsertRows();
    }
    emit dataChanged(index(0,0),index(m_roomlist.count(),4));
}

//void JRoomListModel::on_processor_receiveRoomUpdated(const JRoom& room)
//{
//    for(int i=0;i<m_roomlist.length();++i){
//        if(m_roomlist.at(i).getRoomId() == room.getRoomId()){
//            m_roomlist[i] = room;
//            emit dataChanged(index(i,0),index(i,4));
//        }
//    }
//}
