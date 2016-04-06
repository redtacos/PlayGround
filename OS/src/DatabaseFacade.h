#ifndef DATABASEFACADE_H
#define DATABASEFACADE_H

#include <vector>

#include <QString>

struct Score
{
    QString userName;
    int score;
};

class DatabaseFacade
{
public:
    DatabaseFacade();

    void connectUser( const QString& username_ );
    void addUserStat( int userId, const QString& gameName_, int score_ );
    std::vector< Score > getHightScores( const QString& gameName_ );
private:
    void openConnexion();
};

#endif // DATABASEFACADE_H
