#ifndef GAMESOUND_H
#define GAMESOUND_H

#include <QSound>

class GameSound : public QSound
{
    Q_OBJECT
public:
    GameSound(const QString& parent);
    void SetUsedMusicFile(QString absolutePath);
signals:

public slots:

};

#endif // GAMESOUND_H
