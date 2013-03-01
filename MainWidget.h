#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QDebug>
#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
class QPushButton;
class QSpinBox;
class QAction;
class QTableWidget;
QT_END_NAMESPACE

class View;

const int MAX_X = 99999;
const int MAX_Y = 99999;

class MainWidget : public QMainWindow
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void showArtifactPosition(qreal x, qreal y);

private:
    // Gui
    QSpinBox *xSpinBox;
    QSpinBox *ySpinBox;
    QPushButton *clearButton;

    View *view;
    QTableWidget *tableWidget;

    // Actions
    QAction *exitAct;
    QAction *clearAct;
    QAction *aboutAct;
    QAction *selectAllAct;
    QAction *selectXColumnAct;
    QAction *selectYColumnAct;
    QAction *copySelectedAct;

    // Methods
    void createActions();
    void createGui();
    void createConnections();

private slots:
    void clearPoint();
    void showAbout();

    void selectXColumn();
    void selectYColumn();
    void selectAll();
    void copySelected();

    void showContextMenu(const QPoint &pos);
};

#endif // MAINWIDGET_H
