#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Расписываем скопления с комфортом
"""
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from ui_toy import Ui_ToyForm

class Artifact(QGraphicsItem):
    def __init__(self, graphWidget, coord):
        QGraphicsItem.__init__(self)
        self.graph = graphWidget
        self.x, self.y = coord[0], coord[1]

    def boundingRect(self):
        return QRectF(self.x, self.y, 1, 1)
        
    def paint(self, painter, option, widget):#implements the actual painting
        painter.setPen(QPen(Qt.black, 0))
        painter.drawRect(self.x, self.y, 1, 1)
    

class PaintAreaWidget(QGraphicsView):
    def __init__(self, parentWidget):
        QGraphicsView.__init__(self)
        
        self.parentWidget = parentWidget
        self.scene = QGraphicsScene(self)
        #self.scene.setItemIndexMethod(QGraphicsScene.NoIndex)
        self.setCacheMode(QGraphicsView.CacheBackground)
        self.setRenderHint(QPainter.Antialiasing)
        
        self.scene.setSceneRect(0, 0, 500, 500)#x,y,w,h
        self.setScene(self.scene)
       
        self.artifactsList = []
        #Grid
        pn = QPen()
        pn.setColor(Qt.darkGray)
        pn2 = QPen()
        pn2.setColor(Qt.gray)
        for i in range(600):
            l = QLineF()
            l.setLine(i * 10, 0, i * 10, 500)
            self.scene.addLine(l, pn2)
            l.setLine(0, i * 10, 500, i * 10)
            self.scene.addLine(l, pn2)
        for i in range(6):
            l = QLineF()
            l.setLine(i * 100, 0, i * 100, 500)
            self.scene.addLine(l, pn)
            l.setLine(0, i * 100, 500, i * 100)
            self.scene.addLine(l, pn)
    
    def drawBackground(self, painter, rect):
        sceneRect = self.sceneRect()
        painter.fillRect(rect.intersect(sceneRect), QBrush(Qt.lightGray))
        painter.setBrush(Qt.NoBrush)
        painter.drawRect(sceneRect)
        
    def mousePressEvent(self, event):
        areaMouseClickCoord = event.pos()
        x, y = areaMouseClickCoord.x(), areaMouseClickCoord.y() #point == cm
        self.parentWidget.showCoord([(x - 5)/100.0, (505 - y)/100.0]) #meter
        self.artifactsList.append(Artifact(self,[x,y]))
              
        lastAddedArtifact = self.artifactsList[len(self.artifactsList) - 1]
        self.scene.addItem(lastAddedArtifact)
        
        self.update()
    def removeArtifact(self):
        for item in range(len(self.artifactsList)):
            self.scene.removeItem(self.artifactsList[item])
        self.artifactsList = []
       
class Toy(QWidget, Ui_ToyForm):
    def __init__(self, parent = None):
        super(Toy, self).__init__(parent)
        self.setupUi(self)
        self.area = PaintAreaWidget(self)
        self.scrollArea.setWidget(self.area)
        self.coordText = QString()
        self.connect(self.clearButton, SIGNAL("clicked()"), self.clearPoint)
    def showCoord(self,coord):
        xmin, ymin = self.xSpinBox.value(), self.ySpinBox.value()
        x, y = coord[0] + xmin, coord[1] + ymin
        self.coordText += QString(str(x) + "\t" + str(y) + "\n")
        self.textBrowser.setText(self.coordText)
    def clearPoint(self):
        self.coordText = QString("")
        self.area.removeArtifact()
        
if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = Toy()
    w.setMinimumSize(640, 480)
    w.show()
    sys.exit(app.exec_())