import sys
import os

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import (QWidget, QPushButton,QMainWindow,
                             QHBoxLayout, QVBoxLayout, QApplication, QLabel, QTextEdit, QGridLayout, QLineEdit, QAction,
                             QFileDialog)


class Example(QWidget):

    def __init__(self):
        super().__init__()
        self.initUI()


    def initUI(self):
        self.Qmain=QMainWindow()
        #设置窗口大小
        self.resize(1000, 600)
        # 设置窗口的标题
        self.setWindowTitle('词法分析程序')
        # 设置窗口的图标，引用当前目录下的web.png图片
        self.setWindowIcon(QIcon('data/h12.png'))
        #设置状态栏
        self.statusBar = self.Qmain.statusBar()
        #标签
        self.sourceCode = QLabel('PL/0源代码')
        self.result = QLabel('词法分析结果')
        #按钮
        self.analy_button = QPushButton('分析')
        self.exit_button = QPushButton('退出')
        #文本编辑
        self.sourceCodeEdit = QTextEdit()
        self.resultEdit = QTextEdit()

        self.analy_button.clicked.connect(self.ana_buttonClicked)
        self.exit_button.clicked.connect(self.close)

        grid = QGridLayout()
        grid.setSpacing(10)

        openFile = QAction(QIcon('open.png'), 'Open', self)
        openFile.setShortcut('Ctrl+O')
        openFile.setStatusTip('Open new File')
        openFile.triggered.connect(self.showDialog)

        menubar = self.Qmain.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(openFile)

        grid.addWidget(menubar,0,0,1,2)
        grid.addWidget(self.sourceCode, 1, 2)
        grid.addWidget(self.sourceCodeEdit, 2, 0, 20, 5)

        grid.addWidget(self.result, 1,7)
        grid.addWidget(self.resultEdit, 2, 5, 20, 5)

        grid.addWidget(self.analy_button, 22, 4)
        grid.addWidget(self.exit_button, 22, 5)

        self.setLayout(grid)

        self.show()



    def BoxLayout_(self):
        okButton = QPushButton("OK")
        cancelButton = QPushButton("exit")

        hbox = QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(okButton)
        hbox.addWidget(cancelButton)

        vbox = QVBoxLayout()
        vbox.addStretch(1)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

        self.show()



    def showDialog(self):
        fname = QFileDialog.getOpenFileName(self, 'Open file', '/home')
        if fname[0]:
            f = open(fname[0], 'r')
            data = f.read()
            self.sourceCodeEdit.setText(data)
            f.close()


    def ana_buttonClicked(self):
        #保存源码
        data=self.sourceCodeEdit.toPlainText()
        fj = open('input.txt', 'w')
        fj.write(data)
        fj.close()


        #调用词法分析程序
        main = "analyze.exe"
        os.popen(main)
        os.system('taskkill /f /im analyze.exe')


        #输出分析结果
        fk = open('output.txt', 'r')
        data = fk.read()
        self.resultEdit.setText(data)
        fk.close()

        if os.path.exists('input.txt'):
            os.remove('input.txt')
        if os.path.exists('output.txt'):
            os.remove('output.txt')



if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())