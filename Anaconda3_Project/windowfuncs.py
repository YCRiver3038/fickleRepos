import numpy as np
import math
from scipy import signal
"""
windowIndex: index/(windowLength-1)
0:SMA, 1:Gaussian, 2:Hanning, 3:Sin, 4:Vorbis
5:Blackman, 6:Nutall, 7:Blackman-Harris, 8:Kaiser(beta14), 9:Dolph-Chebyshev(100dB)
"""

_FILTERTYPE = {'SMA':0, 'Gaussian':1, 'Hanning':2, 'Sin':3, 'Vorbis':4, 'Blackman':5, 'Nuttall':6, 'BH':7, 'Kaiser':8, 'DCheb':9 }

#mode0:constant time, mode1:constant period, mode2:Sweep
def createWavetable(amp, length, *, mode=1, freq=1.0, maxTime=1.0, period=1.0, fstart=0.0, fstop=1.0):
	cTable = np.zeros(length)
	indice1 = np.arange(0, length, 1)
	
	if(mode == 0):
		timeArray = (indice1/(length-1))*maxTime
	if(mode == 1):
		timeArray = (indice1/((length-1)/period)/freq)
	if(mode==2):
		timeArray = (indice1/(length-1))*maxTime
		freqArray = np.linspace(fstart, fstop, length)
		
	for ctr in indice1:
		if(mode != 2):
			cTable[ctr] = amp*math.sin(timeArray[ctr]*2*math.pi*freq)
		else:
			cTable[ctr] = amp*math.sin(timeArray[ctr]*2*math.pi*freqArray[ctr])
		
	if(mode != 2):
		return np.vstack((timeArray, cTable))#時間軸:[0,:], 正弦波テーブル:[1,:]
	else:
		return np.vstack((timeArray, cTable, freqArray))#時間軸:[0,:], 正弦波テーブル:[1,:]

def GaussianWindow(wsize):
	"""
	参考サイト：http://www.eng.kagawa-u.ac.jp/~tishii/Lab/Etc/gauss.html
	"""
	warray = np.zeros(wsize)
	iterator1 = np.arange(0,wsize,1)
	sigma = np.std(iterator1)
	for i in iterator1:
		warray[i] = (1/(math.sqrt(2*math.pi)*sigma))*math.exp(-1*(math.pow(i-((wsize-1)/2),2)/(2*math.pow(sigma,2))))
	return warray

def HanningWindow(wsize):
	"""
	http://www.fbs.osaka-u.ac.jp/labs/ishijima/FFT-06.html
	"""
	warray = np.zeros(wsize)
	iterator1 = np.arange(0,wsize,1)
	for i in iterator1:
		warray[i] = 0.5-(0.5*math.cos(2*math.pi*(i/(wsize-1))))
	return warray

def SinWindow(wsize):
	"""
	参考：http://www.spcom.ecei.tohoku.ac.jp/~aito/kisosemi/slides2.pdf
	"""
	warray = np.zeros(wsize)
	iterator1 = np.arange(0,wsize,1)
	for i in iterator1:
		warray[i] = math.sin((math.pi*(i/(wsize-1))))
	return warray

def VorbisWindow(wsize):
	"""
	参考：http://www.spcom.ecei.tohoku.ac.jp/~aito/kisosemi/slides2.pdf
	"""
	warray = np.zeros(wsize)
	iterator1 = np.arange(0,wsize,1)
	for i in iterator1:
		warray[i] = math.sin( (math.pi / 2.0) * math.pow(math.sin(math.pi*(i/(wsize-1))), 2))
	return warray

def BlackmanWindow(wsize):
	warray = np.zeros(wsize)
	warray = signal.get_window('blackman', wsize)
	return warray

def NuttallWindow(wsize):
	warray = np.zeros(wsize)
	warray = signal.get_window('nuttall', wsize)
	return warray

def BHWindow(wsize):#Blackman-Harris
	warray = np.zeros(wsize)
	warray = signal.get_window('blackmanharris', wsize)
	return warray

def KaiserWindow(wsize, *, beta=14):#Kaiser(beta=14)
	warray = np.zeros(wsize)
	warray = signal.get_window(('kaiser',beta), wsize)
	return warray

def DChebWindow(wsize):#Dolph-Chebyshev(100dB)
	warray = np.zeros(wsize)
	warray = signal.get_window(('chebwin',100.0), wsize)
	return warray

def CreateWindow(wsize, wtype, *, ckbeta=14):
	window_array = np.zeros(wsize)
	if(wtype==0):
		window_array[:] = 1
	elif (wtype == 1):
		window_array = GaussianWindow(wsize)
	elif (wtype == 2):
		window_array = HanningWindow(wsize)
	elif (wtype == 3):
		window_array = SinWindow(wsize)
	elif (wtype == 4):
		window_array = VorbisWindow(wsize) 
	elif (wtype == 5):
		window_array = BlackmanWindow(wsize) 
	elif (wtype == 6):
		window_array = NuttallWindow(wsize) 
	elif (wtype == 7):
		window_array = BHWindow(wsize) 
	elif (wtype == 8):
		window_array = KaiserWindow(wsize, beta=ckbeta) 
	elif (wtype == 9):
		window_array = DChebWindow(wsize) 
	return window_array
