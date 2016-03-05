#include "GameSelection.h"

#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDirIterator>
#include <QDebug>

#include "FileLoader.h"

constexpr char gameBaseDir[] = "./games";
constexpr char gamePictureFileName[] = "picture.jpg";
constexpr char gameDescriptionFileName[] = "description.txt";
constexpr char gameAppFileName[] = "game";
constexpr char selectedGameTagName[] = "elementWithFocus";

GameProcess::GameProcess()
{
    QObject::connect( &currentGame, SIGNAL( finished(int, QProcess::ExitStatus) ), this, SLOT( gameFinished(int, QProcess::ExitStatus) ) );
    QObject::connect( &currentGame, SIGNAL( readyReadStandardError() ), this, SLOT( readyReadStandardError() ) );
    QObject::connect( &currentGame, SIGNAL( readyReadStandardOutput() ), this, SLOT( readyReadStandardOutput() ) );
    QObject::connect( &currentGame, SIGNAL( started() ), this, SLOT( started() ) );
}

void GameProcess::gameFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // Show OS panel.
}

void GameProcess::readyReadStandardError()
{
    // Logging error.
}

void GameProcess::readyReadStandardOutput()
{
    // Command from the game arrive, answer on game stdin
}

void GameProcess::started()
{
    // Hide OS panel
}

void GameProcess::startGame( const QString& gameAppPath )
{
    currentGame.start( gameAppPath );
}

GameSelection::GameSelection() :
    selectedGameIndex( 0 )
{
    detectAvaibleGame();

    QHBoxLayout* pGameList = new QHBoxLayout();

    foreach( QString gameName, avaibleGames )
    {
        QLabel* pGameTitleLabel = new QLabel( gameName );
        pGameTitleLabel->setFont( QFont( "Arial", 48, QFont::Bold ) );

        QLabel* pGamePixmap = new QLabel();
        pGamePixmap->setPixmap( QPixmap( QString("%1/%2/%3").arg( gameBaseDir ).arg( gameName ).arg( gamePictureFileName ) ).scaled( 400, 600 ) );
        pGamePixmap->setMaximumSize( QSize( 500, 800 ) );

        QLabel* pGameDescriptionLabel = new QLabel( readFiles( QStringList() << QString("%1/%2/%3").arg( gameBaseDir ).arg( gameName ).arg( gameDescriptionFileName ) ) );
        pGameDescriptionLabel->setFont( QFont( "Arial", 34 ) );

        QPushButton* pStartGameBtn = new QPushButton( QString( "Débuter %1" ).arg( gameName )  );
        pStartGameBtn->setObjectName( gameName );
        pStartGameBtn->setMaximumWidth( 400 );
        QObject::connect( pStartGameBtn, SIGNAL( clicked() ), this, SLOT( startGameRequest() ) );

        QVBoxLayout* gamePreview = new QVBoxLayout();
        gamePreview->addWidget( pGameTitleLabel );
        gamePreview->addWidget( pGamePixmap );
        gamePreview->addWidget( pGameDescriptionLabel );
        gamePreview->addStretch();
        gamePreview->addWidget( pStartGameBtn );

        QWidget* gamePanel = new QWidget();
        gamePanel->setLayout( gamePreview );
        pGameList->addWidget( gamePanel );
        this->gamePanels.append( gamePanel );
    }

    QPushButton* backToProfileSelection = new QPushButton( "Back" );

    QVBoxLayout* pMainLayout = new QVBoxLayout();
    pMainLayout->addLayout( pGameList );
    pMainLayout->addWidget( backToProfileSelection );

    this->setLayout( pMainLayout );
    this->setObjectName( "mainPane" );
    this->setStyleSheet( readFiles( QStringList() << "css/GameSelection.css" ) );
}

void GameSelection::detectAvaibleGame()
{
    QDirIterator it( gameBaseDir );

    while( it.hasNext() )
    {
        QString gameName = it.fileName();

        if( it.fileInfo().isDir() && gameName != "." )
        {
            qDebug() << " Game avaible: " << gameName;
            avaibleGames.append( gameName );
        }

        it.next();
    }
}

void GameSelection::startGameRequest()
{
    QObject* pObj = sender();

    if( pObj != nullptr && pObj->objectName().isEmpty() == false )
    {
        QString gameAppPath("%1/%2/%3");
        gameAppPath = gameAppPath.arg( gameBaseDir ).arg( pObj->objectName() ).arg( gameAppFileName );

        qDebug() << "Start game " << gameAppPath;
        emit startGame( gameAppPath );
    }
}

void GameSelection::process( GamePadMsgType message_ )
{
    if( this->gamePanels.size() > 0 )
    {

    }
}

