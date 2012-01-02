#ifndef JROOMPROTOCOL_H
#define JROOMPROTOCOL_H

const JType RoomProcessor = EPI_UserType + 1;
const JType GameDataProcessor = EPI_UserType + 2;

enum ERoomProtocol{
	ERP_Hello,
    ERP_RoomList,
	ERP_AddRoom,
	ERP_EnterRoom,
    ERP_RoomInfo,
    ERP_RoomRemoved,
    ERP_RoomChat,
};

#endif // JROOMPROTOCOL_H
