#include <QMouseEvent>
#include <QStatusBar>

#include "View.h"
#include "MainWidget.h"

ArtifactItem::ArtifactItem(qreal x, qreal y)
{
    m_x = x;
    m_y = y;
}

QRectF ArtifactItem::boundingRect() const
{
    return QRectF(m_x, m_y, 1, 1);
}

void ArtifactItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawRect(m_x, m_y, 1, 1);
}

View::View(MainWidget *p, QWidget *parent)
    : QGraphicsView(parent), m_parent(p)
{
    scene = new QGraphicsScene;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(0, 0, 500, 500);

    setCacheMode(QGraphicsView::CacheBackground);
    setRenderHint(QPainter::Antialiasing);
    setScene(scene);

    drawGrid();
}

void View::drawGrid()
{
    QPen blackPen;
    blackPen.setColor(Qt::black);
    QPen grayPen;
    grayPen.setColor(Qt::gray);

    for (int i = 0; i < 600; ++i)
    {
        QLineF line;
        line.setLine(i * 10, 0, i * 10, 500);
        scene->addLine(line, grayPen);
        line.setLine(0, i *10, 500, i* 10);
        scene->addLine(line, grayPen);
    }
    for (int i = 0; i < 6; ++i)
    {
        QLineF line;
        line.setLine(i * 100, 0, i * 100, 500);
        scene->addLine(line, blackPen);
        line.setLine(0, i * 100, 500, i * 100);
        scene->addLine(line, blackPen);
    }
}

void View::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect.intersect(sceneRect()), QBrush(Qt::lightGray));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect());
}

void View::mousePressEvent(QMouseEvent *event)
{
    QPointF areaMouseClickCoord;
    areaMouseClickCoord = event->pos();
    int x = areaMouseClickCoord.x();
    int y = areaMouseClickCoord.y();

    qreal real_x = x / 100.0;
    qreal real_y = (500 - y) / 100.0;

    m_parent->showArtifactPosition(real_x, real_y);

    ArtifactItem *artifact = new ArtifactItem(x, y);

    artifactList.append(artifact);
    scene->addItem(artifact);
    scene->update();

    m_parent->statusBar()->showMessage(tr("Всего находок: %1 шт.").arg(artifactList.count()));
}

void View::clearArtifactList()
{
    for (int i = 0; i < artifactList.count(); ++i)
    {
        scene->removeItem(artifactList.at(i));
    }
    artifactList.clear();
}
