#include "arkanoid.h"
#include <QPainter>
#include <QApplication>

Arkanoid::Arkanoid(QWidget *parent) : QWidget(parent)
{
    x = 0;
    gameOver = FALSE;
    gameWon = FALSE;
    paused = FALSE;
    gameStarted = FALSE;
    paddle = new Paddle();
    startGame();
    setWindowTitle("qtArkanoid");
    setMouseTracking(true);
}

Arkanoid::~Arkanoid()
{
    delete paddle;
}

void Arkanoid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (gameOver)
    {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.width("Game Over");

        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textWidth/2, 0, "Game Over");
    }

    else if(gameWon)
    {
        QFont font("Courier", 15, QFont::DemiBold);
        QFontMetrics fm(font);
        int textWidth = fm.width("Victory");

        painter.setFont(font);
        int h = height();
        int w = width();

        painter.translate(QPoint(w/2, h/2));
        painter.drawText(-textWidth/2, 0, "Victory");
    }

    else
    {
        painter.drawImage(paddle->getRect(), paddle->getImage());
    }
}

void Arkanoid::timerEvent(QTimerEvent *event)
{
    repaint();
}

void Arkanoid::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        {
            int x = paddle->getRect().x();
            for (int i=1; i<=5; i++)
                paddle->moveLeft(x--);
            break;
        }
    case Qt::Key_Right:
        {
            int x = paddle->getRect().x();
            for (int i=1; i<=5; i++)
                paddle->moveRight(x++);
        }
        break;
    case Qt::Key_P:
        {
            pauseGame();
        }
        break;
    case Qt::Key_Space:
        {
            startGame();
        }
        break;
    case Qt::Key_Escape:
        {
            qApp->exit();
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Arkanoid::mousePressEvent(QMouseEvent *event)
{
    /*
    if (event->button() == Qt::LeftButton)
    {
        gameOver = true;
    }
    */
}

void Arkanoid::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    paddle->movePaddle(pos.x());
}

void Arkanoid::startGame()
{
    if (!gameStarted)
    {
        paddle->resetState();

        gameOver = FALSE;
        gameWon = FALSE;
        gameStarted = TRUE;
        timerId = startTimer(10);
    }
}

void Arkanoid::pauseGame()
{
    if (paused)
    {
        timerId = startTimer(10);
        paused = FALSE;
    }
    else
    {
        paused = TRUE;
        killTimer(timerId);
    }
}

void Arkanoid::stopGame()
{
    killTimer(timerId);
    gameOver = TRUE;
    gameStarted = FALSE;
}

void Arkanoid::victory()
{
    killTimer(timerId);
    gameWon = TRUE;
    gameStarted = FALSE;
}