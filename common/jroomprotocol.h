#ifndef JROOMPROTOCOL_H
#define JROOMPROTOCOL_H

const EProcessorType RoomProcessor = EPI_UserType_1;
const EProcessorType GameDataProcessor = EPI_UserType_2;

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
