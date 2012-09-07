#ifndef JROOMWIDGET_H
#define JROOMWIDGET_H

#include <Global/Global>

#include <QWidget>

namespace Ui {
    class JRoomWidget;
}
class JRoomModelClientRoomProcessor;

class JRoomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JRoomWidget(QWidget *parent = 0);
    ~JRoomWidget();
signals:
    void enterRoom(JID roomId);
private:
    Ui::JRoomWidget *ui;
    JRoomModelClientRoomProcessor* m_processor;
private slots:
    void on_btn_enterroom_clicked();
    void on_btn_addroom_clicked();
    void On_processor_receiveHelloResult(JCode result);
    void On_processor_receiveAddRoomResult(JID roomId);
    void On_processor_receiveEnterRoom(JID userId,JID roomId,JCode result);
};

#endif // JROOMWIDGET_H
