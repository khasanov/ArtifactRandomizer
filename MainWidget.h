#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDebug>
#include <QMainWindow>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

class MainWidget;

const int MAX_X = 99999;
const int MAX_Y = 99999;

class ArtifactItem : public QGraphicsItem
{
public:
    ArtifactItem(qreal x, qreal y);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal m_x;
    qreal m_y;
};


class View : public QGraphicsView
{
    Q_OBJECT
public:
    View(MainWidget *p, QWidget *parent = 0);
    QGraphicsScene *scene;
    void clearArtifactList();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QMouseEvent *event);

private:
    void drawGrid();
    MainWidget *m_parent;
    QList <ArtifactItem *> artifactList;
};


class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void showPointData(qreal x, qreal y);

private:
    // GUI
    QSpinBox *xSpinBox;
    QSpinBox *ySpinBox;
    QPushButton *clearButton;

    View *view;

    QTextEdit *textEdit;

    // !GUI
private slots:
    void clearPoint();
    void showAbout();
};

#endif // MAINWIDGET_H
