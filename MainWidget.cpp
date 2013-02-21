#include "MainWidget.h"

#include <QPushButton>
#include <QGraphicsScene>
#include <QMouseEvent>

#include <QSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextBrowser>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLocale>

#include "AboutDialog.h"

ArtifactItem::ArtifactItem(qreal x, qreal y)
{
    m_x = x;
    m_y = y;
}

QRectF ArtifactItem::boundingRect() const
{
    return QRectF(m_x, m_y, 1, 1);
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

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    /* GUI */
    xSpinBox = new QSpinBox;
    xSpinBox->setMinimumWidth(100);
    xSpinBox->setMaximum(MAX_X);

    ySpinBox = new QSpinBox;
    ySpinBox->setMinimumWidth(100);
    ySpinBox->setMaximum(MAX_Y);

    QFormLayout *coordForm = new QFormLayout;
    coordForm->addRow(tr("X, min"), xSpinBox);
    coordForm->addRow(tr("Y, min"), ySpinBox);

    clearButton = new QPushButton(tr("Очистить"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(coordForm);
    topLayout->addStretch();
    topLayout->addWidget(clearButton);


    QScrollArea *scrollArea = new QScrollArea;
    textEdit = new QTextEdit;

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(scrollArea);
    middleLayout->addWidget(textEdit);


    view = new View(this);
    scrollArea->setWidget(view);
    scrollArea->setAlignment(Qt::AlignCenter);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);

    setWindowTitle(tr("Планиграф"));

    QWidget *cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    statusBar()->showMessage(tr(" "));



    QAction *exitAct = new QAction(tr("Выйти"), this);
    exitAct->setShortcut(QKeySequence(tr("CTRL+Q")));

    QAction *clearAct = new QAction(tr("Очистить"), this);
    clearAct->setShortcut(QKeySequence(tr("CTRL+C")));

    QAction *aboutAct = new QAction(tr("О программе"), this);

    QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(aboutAct);

    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearPoint()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearPoint()));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(showAbout()));

}

MainWidget::~MainWidget()
{
}

void MainWidget::clearPoint()
{
    textEdit->clear();
    view->clearArtifactList();
    statusBar()->clearMessage();
}

void MainWidget::showAbout()
{
    AboutDialog dlg;
    dlg.exec();
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

    m_parent->showPointData(real_x, real_y);

    ArtifactItem *artifact = new ArtifactItem(x, y);

    artifactList.append(artifact);
    scene->addItem(artifact);
    scene->update();

    m_parent->statusBar()->showMessage(tr("Всего находок: %1 шт.").arg(artifactList.count()));
}

void MainWidget::showPointData(qreal x, qreal y)
{
    QString data;
    QLocale rus(QLocale::Russian);

    data.append(rus.toString((xSpinBox->value() + x), char('f'), 2));
    data.append("\t");
    data.append(rus.toString((ySpinBox->value() + y), char('f'), 2));
    textEdit->append(data);
}

void ArtifactItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(m_x, m_y, 1, 1);
}

void View::clearArtifactList()
{
    for (int i = 0; i < artifactList.count(); ++i)
    {
        scene->removeItem(artifactList.at(i));
    }
    artifactList.clear();
}
