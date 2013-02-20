# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'toy.ui'
#
# Created: Wed Sep 29 23:04:52 2010
#      by: PyQt4 UI code generator 4.7.3
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

class Ui_ToyForm(object):
    def setupUi(self, ToyForm):
        ToyForm.setObjectName("ToyForm")
        ToyForm.resize(818, 593)
        self.widget = QtGui.QWidget(ToyForm)
        self.widget.setGeometry(QtCore.QRect(22, 3, 784, 576))
        self.widget.setObjectName("widget")
        self.verticalLayout = QtGui.QVBoxLayout(self.widget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout_2 = QtGui.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.gridLayout = QtGui.QGridLayout()
        self.gridLayout.setObjectName("gridLayout")
        self.label = QtGui.QLabel(self.widget)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.label_2 = QtGui.QLabel(self.widget)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 0, 1, 1, 1)
        self.xSpinBox = QtGui.QSpinBox(self.widget)
        self.xSpinBox.setMaximum(999)
        self.xSpinBox.setObjectName("xSpinBox")
        self.gridLayout.addWidget(self.xSpinBox, 1, 0, 1, 1)
        self.ySpinBox = QtGui.QSpinBox(self.widget)
        self.ySpinBox.setMaximum(999)
        self.ySpinBox.setObjectName("ySpinBox")
        self.gridLayout.addWidget(self.ySpinBox, 1, 1, 1, 1)
        self.horizontalLayout_2.addLayout(self.gridLayout)
        spacerItem = QtGui.QSpacerItem(40, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.horizontalLayout_2.addItem(spacerItem)
        self.clearButton = QtGui.QPushButton(self.widget)
        self.clearButton.setObjectName("clearButton")
        self.horizontalLayout_2.addWidget(self.clearButton)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.scrollArea = QtGui.QScrollArea(self.widget)
        self.scrollArea.setMinimumSize(QtCore.QSize(520, 520))
        self.scrollArea.setWidgetResizable(True)
        self.scrollArea.setObjectName("scrollArea")
        self.scrollAreaWidgetContents = QtGui.QWidget(self.scrollArea)
        self.scrollAreaWidgetContents.setGeometry(QtCore.QRect(0, 0, 514, 514))
        self.scrollAreaWidgetContents.setObjectName("scrollAreaWidgetContents")
        self.scrollArea.setWidget(self.scrollAreaWidgetContents)
        self.horizontalLayout.addWidget(self.scrollArea)
        self.textBrowser = QtGui.QTextBrowser(self.widget)
        self.textBrowser.setObjectName("textBrowser")
        self.horizontalLayout.addWidget(self.textBrowser)
        self.verticalLayout.addLayout(self.horizontalLayout)

        self.retranslateUi(ToyForm)
        QtCore.QObject.connect(self.clearButton, QtCore.SIGNAL("clicked()"), self.textBrowser.clear)
        QtCore.QMetaObject.connectSlotsByName(ToyForm)

    def retranslateUi(self, ToyForm):
        ToyForm.setWindowTitle(QtGui.QApplication.translate("ToyForm", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("ToyForm", "Xmin", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("ToyForm", "Ymin", None, QtGui.QApplication.UnicodeUTF8))
        self.clearButton.setText(QtGui.QApplication.translate("ToyForm", "clear", None, QtGui.QApplication.UnicodeUTF8))

