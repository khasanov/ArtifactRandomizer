#include "MainWidget.h"

#include <QPushButton>
#include <QSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QLocale>
#include <QTableWidget>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>

#include "AboutDialog.h"
#include "View.h"

MainWidget::MainWidget(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createGui();
    createConnections();
}

MainWidget::~MainWidget()
{
}

void MainWidget::createActions()
{
    exitAct = new QAction(tr("Выйти"), this);
    exitAct->setShortcut(QKeySequence(tr("CTRL+Q")));

    clearAct = new QAction(tr("Очистить"), this);
    clearAct->setShortcut(QKeySequence(tr("CTRL+Z")));

    aboutAct = new QAction(tr("О программе"), this);
    aboutAct->setShortcut(QKeySequence(tr("F1")));

    selectAllAct = new QAction(tr("Выделить все"), this);
    selectAllAct->setShortcut(QKeySequence(tr("CTRL+A")));

    selectXColumnAct = new QAction(tr("Выделить колонку X"), this);
    selectXColumnAct->setShortcut(QKeySequence(tr("CTRL+X")));

    selectYColumnAct = new QAction(tr("Выделить колонку Y"), this);
    selectYColumnAct->setShortcut(QKeySequence(tr("CTRL+Y")));

    copySelectedAct = new QAction(tr("Копировать выделенное"), this);
    copySelectedAct->setShortcut(QKeySequence(tr("CTRL+C")));
}

void MainWidget::createGui()
{
    //
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

    //
    tableWidget = new QTableWidget;
    tableWidget->setGridStyle(Qt::NoPen);
    tableWidget->setColumnCount(2);
    QStringList headers;
    headers << tr("X") << tr("Y");
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    view = new View(this);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(view);
    scrollArea->setAlignment(Qt::AlignCenter);

    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(scrollArea);
    middleLayout->addWidget(tableWidget);

    //
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);

    setWindowTitle(tr("Планиграф"));

    QWidget *cw = new QWidget;
    cw->setLayout(mainLayout);
    setCentralWidget(cw);

    statusBar()->showMessage(tr(" "));

    // Menus
    QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(clearAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    QMenu *editMenu = menuBar()->addMenu(tr("Правка"));
    editMenu->addAction(selectXColumnAct);
    editMenu->addAction(selectYColumnAct);
    editMenu->addAction(selectAllAct);
    editMenu->addSeparator();
    editMenu->addAction(copySelectedAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(aboutAct);
}

void MainWidget::createConnections()
{
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearPoint()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearPoint()));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(showAbout()));

    connect(selectXColumnAct, SIGNAL(triggered()), this, SLOT(selectXColumn()));
    connect(selectYColumnAct, SIGNAL(triggered()), this, SLOT(selectYColumn()));
    connect(selectAllAct, SIGNAL(triggered()), this, SLOT(selectAll()));

    connect(copySelectedAct, SIGNAL(triggered()), this, SLOT(copySelected()));

    connect(tableWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
}

void MainWidget::clearPoint()
{
    for (int i = tableWidget->rowCount() - 1; i >= 0; --i)
    {
        tableWidget->removeRow(i);
    }

    view->clearArtifactList();
    statusBar()->clearMessage();
}

void MainWidget::showAbout()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWidget::selectXColumn()
{
    tableWidget->selectColumn(0);
}

void MainWidget::selectYColumn()
{
    tableWidget->selectColumn(1);
}

void MainWidget::selectAll()
{
    tableWidget->selectAll();
}

void MainWidget::copySelected()
{
    QModelIndex index;
    QByteArray str;

    const QItemSelection selection = tableWidget->selectionModel()->selection();
    int minrow = selection.at(0).top();
    int mincolumn = selection.at(0).left();
    int maxrow = selection.at(0).bottom();
    int maxcolumn = selection.at(0).right();

    for (int i = minrow; i <= maxrow; ++i)
    {
        if (i > minrow)
            str += "\n";
            for (int j = mincolumn; j <= maxcolumn; ++j)
            {
                if (j > mincolumn)
                    str += "\t";
                    index = tableWidget->model()->index(i, j, QModelIndex());
                    QString t = tableWidget->model()->data(index).toString();
                    str += t;
            }
    }

    QMimeData * mimeData = new QMimeData();
    mimeData->setData("text/plain", str);
    QApplication::clipboard()->setMimeData(mimeData);
}

void MainWidget::showArtifactPosition(qreal x, qreal y)
{
    QLocale rus(QLocale::Russian);

    int row = tableWidget->rowCount();
    QTableWidgetItem *xItem = new QTableWidgetItem(rus.toString((xSpinBox->value() + x), char('f'), 2));
    QTableWidgetItem *yItem = new QTableWidgetItem(rus.toString((ySpinBox->value() + y), char('f'), 2));
    xItem->setFlags(xItem->flags() ^ Qt::ItemIsEditable);
    yItem->setFlags(yItem->flags() ^ Qt::ItemIsEditable);
    tableWidget->insertRow(row);
    tableWidget->setItem(row, 0, xItem);
    tableWidget->setItem(row, 1, yItem);
}

void MainWidget::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = tableWidget->mapToGlobal(pos);
    QMenu menu;

    menu.addAction(selectXColumnAct);
    menu.addAction(selectYColumnAct);
    menu.addAction(selectAllAct);
    menu.addSeparator();
    menu.addAction(copySelectedAct);

    menu.exec(globalPos);
}
