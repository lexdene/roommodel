#include "jroomwidget.h"
#include "ui_jroomwidget.h"
#include "jroomlistmodel.h"

#include "network/jroommodelclientroomprocessor.h"
#include "application/jclientapplicationbase.h"

#include "../common/jroomerrorcode.h"

#include <Helper/JGameClientArgumentAnalyser>
#include <Global/CodeError>

#include <QMessageBox>
#include <QInputDialog>

JRoomWidget::JRoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JRoomWidget)
{
    m_processor = JRoomModelClientRoomProcessor::getInstance();
    connect(m_processor,
            SIGNAL(receiveHelloResult(JCode)),
            SLOT(On_processor_receiveHelloResult(JCode)));
    connect(m_processor,
            SIGNAL(receiveAddRoomResult(JID)),
            SLOT(On_processor_receiveAddRoomResult(JID)));
    connect(m_processor,
            SIGNAL(receiveEnterRoomResult(JID,JCode)),
            SLOT(On_processor_receiveEnterRoomResult(JID,JCode)));
    ui->setupUi(this);
	JRoomListModel* model = new JRoomListModel(this);
	ui->tableView_roomlist->setModel(model);
    m_processor->sendHello(JGameClientArgumentAnalyser::getInstance()->getUserId());
    m_processor->requestRoomList();
}

JRoomWidget::~JRoomWidget()
{
    delete ui;
}

void JRoomWidget::on_btn_addroom_clicked()
{
    JRoom room;
    QString room_title;
    bool ok;
    room_title = QInputDialog::getText(
            this,
            tr("room title"),
            tr("please input the title of room"),
            QLineEdit::Normal,
            tr("no title"),
            &ok
            );
    if(ok){
        room.setTitle(room_title);
        JClientApplicationBase* app=JClientApplicationBase::getInstance();
        app->createRoomInfo(room);
        m_processor->requestAddRoom(room);
    }
}

void JRoomWidget::on_btn_enterroom_clicked()
{
    QModelIndexList selectindexlist= ui->tableView_roomlist->selectionModel()->selectedIndexes();
    if(selectindexlist.length()<=0){
        QMessageBox::critical(
                this,
                tr("please select room"),
                tr("please select room"));
        return;
    }
    QModelIndex currentindex = selectindexlist.at(0);
    int row = currentindex.row();
    QModelIndex index = ui->tableView_roomlist->model()->index(row,0);
    JID roomId = index.data(Qt::DisplayRole).toInt();
    m_processor->requestEnterRoom(roomId);
}

void JRoomWidget::On_processor_receiveHelloResult(JCode result)
{
    switch(result){
    case ESuccess:
        return;
        break;
    default:
        QMessageBox::warning(
                this,
                tr("hello error"),
                tr("hello error : unknown error %1").arg(result));
        return;
    }
}

void JRoomWidget::On_processor_receiveAddRoomResult(JID roomId)
{
    if(roomId >=0){
        m_processor->requestEnterRoom(roomId);
    }else{
        QMessageBox::critical(
                this,
                tr("enter room error"),
                tr("you are already in a room.can not enter another one."));
    }
}

void JRoomWidget::On_processor_receiveEnterRoomResult(JID roomId,JCode result)
{
    switch(result){
    case ESuccess:
        emit enterRoom(roomId);
        return;
        break;
    case EEnterRoomAlreadyInRoom:
        QMessageBox::warning(
                this,
                tr("enter room error"),
                tr("you are already in a room.can not enter another one."));
        break;
    default:
        QMessageBox::warning(
                this,
                tr("enter room error"),
                tr("enter room error : unknown error %1").arg(result));
        return;
    }
}
