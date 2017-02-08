
#ifndef _GAME_APP_H_
#define _GAME_APP_H_

#include "md2.h"
#include "renderbasic.h"
#include "polygon.h"

#include "surface.h"
#include "fonttiles.h"
#include "sample.h"
#include "trace.h"

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QKeyEvent>
#include <QApplication>
#include <QTimer>

class GameApp : public QMainWindow
{
    Q_OBJECT

public:

    QImage buffer;
    QLabel label;
    QTimer timer;


    GameApp(QWidget *parent);
    ~GameApp();

    bool GameInit();
    void GameEnd();
    void GameLoop();

    int m_keys;
    vector_t m_pos; 
    framebuffer_t m_buffer;

    FontTiles m_text;
    surface_t m_fonts;

    object_t m_cube;
    CMD2Model m_model;

    public slots:
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void timeout();

};

#endif