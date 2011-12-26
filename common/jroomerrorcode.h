#ifndef JROOMERRORCODE_H
#define JROOMERRORCODE_H

#include <Global/CodeError>

const JCode ERoomModelCode = 0x1000;

const JCode EUserIdError = ERoomModelCode;
const JCode EUserIdDuplicated = EUserIdError | 0x0001;
const JCode EUserIdNotExist = EUserIdError | 0x0002;

const JCode ERoomIdError = ERoomModelCode | 0x0100;
const JCode ERoomIdDuplicated = ERoomIdError | 0x0001;
const JCode ERoomIdNotExist = ERoomIdError | 0x0002;

const JCode ERoomError = ERoomModelCode | 0x0200;
const JCode ERoomIsFull = ERoomError | 0x0001;

const JCode EEnterRoomError = ERoomError | 0x0020;
const JCode EEnterRoomAlreadyInRoom = ERoomError | 0x0001;

const JCode EApplicationManagerError = ERoomModelCode | 0x0FF0;
const JCode EApplicationManager_AppFactoryIsNull = EApplicationManagerError | 0x0001;

#endif // JROOMERRORCODE_H
