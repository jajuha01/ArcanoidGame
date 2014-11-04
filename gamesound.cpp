#include "gamesound.h"
#include <QMultimedia>
#include <QDir>

GameSound::GameSound(const QString& parent) :
    QSound(parent)
{

}

void GameSound::SetUsedMusicFile(QString absolutePath)
{
    setObjectName(absolutePath);
    setLoops(-1);
    play();
}


