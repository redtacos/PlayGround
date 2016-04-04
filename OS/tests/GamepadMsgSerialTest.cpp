#include "GamepadMsgSerialTest.h"

#include <QApplication>
#include <QTimer>

#include "Fixtures/FakeGamepad.h"
#include "GamePadCom.h"

void GamepadMsgSerialTest::testSendMessage()
{
    QString serialPortName = "ttyS1";
    GamePadCom com( serialPortName );
    FakeGamepad fakeGamepad( serialPortName );

    QObject::connect( &com, SIGNAL( newMessageArrive( GamePadMsgType ) ), &fakeGamepad, SLOT( sendedMessageLoopback( GamePadMsgType ) ) );

    fakeGamepad.connect();
    fakeGamepad.send( GamePadMsgType( std::numeric_limits< uint64_t >::max() ) );

    QTimer::singleShot( 1000, qApp, SLOT( quit() ) );
    qApp->exec();

    QVERIFY( fakeGamepad.getLoopbackMsg().cmd == std::numeric_limits< uint64_t >::max() );
}