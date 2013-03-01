#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsItem>
#include <QGraphicsView>

class MainWidget;

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

#endif // VIEW_H
