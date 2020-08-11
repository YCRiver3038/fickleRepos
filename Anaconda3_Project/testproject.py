# -*- coding:utf-8 -*-

#プロット関係のライブラリ
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import numpy as np
import sys

#音声関係のライブラリ
import pyaudio
import struct


class PlotWindow:
    def __init__(self):
        #プロット初期設定
        self.win=pg.GraphicsWindow()
        self.win.setWindowTitle(u"")
        self.plt=self.win.addPlot() #プロットのビジュアル関係
        self.plt.setYRange(-1,1)    #y軸の上限、下限の設定
        self.curve=self.plt.plot()  #プロットデータを入れる場所

        #マイクインプット設定
        self.CHUNK=1024             #1度に読み取る音声のデータ幅
        self.RATE=44100             #サンプリング周波数
        self.audio=pyaudio.PyAudio()
        self.stream=self.audio.open(format=pyaudio.paFloat32,
                                    channels=1,
                                    rate=self.RATE,
                                    input=True,
                                    frames_per_buffer=self.CHUNK)

        #アップデート時間設定
        self.timer=QtCore.QTimer()
        self.timer.timeout.connect(self.update)
        self.timer.start(17)    #17msごとにupdateを呼び出し

        #音声データの格納場所(プロットデータ)
        self.data=np.zeros(self.CHUNK)

    def update(self):
        self.data=self.AudioInput()
        self.curve.setData(self.data)   #プロットデータを格納

    def AudioInput(self):
        ret=self.stream.read(self.CHUNK)    #音声の読み取り(バイナリ)
        #バイナリ → 数値(float32)に変換
        ret=np.frombuffer(ret, dtype="float32")
        return ret

if __name__=="__main__":
    plotwin=PlotWindow()
    if (sys.flags.interactive!=1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()