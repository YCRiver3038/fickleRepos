# -*- coding:utf-8 -*-
#Reference:https://qiita.com/MuAuan/items/675854ab602595c79612

import pyaudio
import numpy as np
from scipy import signal
import math
import threading

#プロット関係のライブラリ
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import numpy as np
import sys
#音声関係のライブラリ
import struct

"""
windowIndex: index/(windowLength-1)
0:SMA, 1:Gaussian, 2:Hanning, 3:Sin, 4:Vorbis
5:Blackman, 6:Nutall, 7:Blackman-Harris, 8:Kaiser(beta14), 9:Dolph-Chebyshev(100dB)
"""

print('init:', end='')
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

RATE=48000
p=pyaudio.PyAudio()

stream1 = pyaudio.PyAudio()
dev_index = np.arange(stream1.get_device_count())
print("device ID, device name:")
for idx in dev_index:
	print("ID%4d：%s"%(idx, (stream1.get_device_info_by_index(idx))['name']), end='')
	print()

print("Select Device(ID?)")
try:
	idev = int(input("input："))
except ValueError:
	idev=0
try:
	odev = int(input("output："))
except ValueError:
	odev=4
print()

CHUNK=int(input("Buffer size?："))
stream=p.open(  format = pyaudio.paFloat32,
		channels = 1,
		rate = RATE,
		frames_per_buffer = CHUNK,
		input = True,
		output = True,
		input_device_index=idev,
		output_device_index=odev )

window = CreateWindow(CHUNK, _FILTERTYPE['Hanning'])

fftres = RATE/CHUNK
minpitch = 20.0
maxpitch = 20000
shiftmaxf = 16000

minpitch_coff_index = int(minpitch/fftres)
maxpitch_coff_index = int(maxpitch/fftres)
shiftmax_index = int(shiftmaxf/fftres)

pitch_shift = 2.0
form_shift = 1.35

pshift_zone = 3

iterator = np.arange(0, CHUNK, 1)
xfreq = np.fft.fftfreq(CHUNK, 1/RATE)
fftarray = np.zeros(int((CHUNK/2)+1))
fftarray_windowed = np.zeros(int((CHUNK/2)+1))
print('done')
print('FFT Resolution:%6.4f[Hz]'%(fftres))
print('FFT Length:%d'%(CHUNK))

def AudioThr():
	while stream.is_active():
		input_data = stream.read(CHUNK)
		input_array = np.frombuffer(input_data, dtype=np.float32)
		
		fftarray = np.fft.fft(input_array)
		fftarray_windowed = np.fft.fft(input_array*window)

		try:
			peak_index = (signal.argrelmax(fftarray_windowed[:int(len(fftarray_windowed)/2)], order=2))[0]
			pitch_index = np.where(fftarray_windowed == (fftarray_windowed[peak_index].max()))[0]

			harm_sec_index = (np.where(peak_index > pitch_index)[0])[0]
			harm_second = fftarray_windowed[peak_index[harm_sec_index]]

			pitch = xfreq[pitch_index]
			print('\rpitch:%.2f, second:%.2f       '%(pitch, (peak_index[harm_sec_index])*fftres), end='')
			
			pitch_power = np.array(fftarray[int(pitch_index-pshift_zone):int(pitch_index+pshift_zone)])
			form_power = np.array(fftarray[int(harm_sec_index+pshift_zone+1):shiftmax_index])
			fftarray[int(pitch_index-pshift_zone):] = 0

			pitch_shift_index = int(pitch_index*pitch_shift)
			harm_shift_start = int((harm_sec_index+pshift_zone)*form_shift)

			fftarray[(pitch_shift_index-pshift_zone):(pitch_shift_index+pshift_zone)] = np.copy(pitch_power)
			fftarray[harm_shift_start:(harm_shift_start+len(form_power))] = np.copy(form_power)
		except (ValueError, IndexError):
			try:
				peak_index = (signal.argrelmax(fftarray_windowed[:int(len(fftarray_windowed)/2)]))[0]
				pitch_index = np.where(fftarray_windowed == (fftarray_windowed[peak_index].max()))[0]

				harm_sec_index = (np.where(peak_index > pitch_index)[0])[0]
				harm_second = fftarray_windowed[peak_index[harm_sec_index]]

				pitch = xfreq[pitch_index]
				print('\rpitch:%.2f, second:%.2f       '%(pitch, (peak_index[harm_sec_index])*fftres), end='')
				
				pitch_power = np.array(fftarray[int(pitch_index-pshift_zone):int(pitch_index+pshift_zone)])
				form_power = np.array(fftarray[int(harm_sec_index+pshift_zone+1):shiftmax_index])
				fftarray[int(pitch_index-pshift_zone):] = 0

				pitch_shift_index = int(pitch_index*pitch_shift)
				harm_shift_start = int((harm_sec_index+pshift_zone)*form_shift)

				fftarray[(pitch_shift_index-pshift_zone):(pitch_shift_index+pshift_zone)] = np.copy(pitch_power)
				fftarray[harm_shift_start:(harm_shift_start+len(form_power))] = np.copy(form_power)
			except (ValueError, IndexError):
				pitch_index = minpitch_coff_index
				pitch = xfreq[pitch_index]
				print('\rpitch:%.2f       '%(pitch), end='')
				
				pitch_power = np.array(fftarray[int(pitch_index-pshift_zone):int(pitch_index+pshift_zone)])
				form_power = np.array(fftarray[int(pitch_index+pshift_zone+1):shiftmax_index])
				fftarray[int(pitch_index-pshift_zone):int(pitch_index+pshift_zone)] = 0

				fftarray[(int(pitch_index*pitch_shift)-pshift_zone):(int(pitch_index*pitch_shift)+pshift_zone)] = np.copy(pitch_power)
				fftarray[int(pitch_index+pshift_zone):(int(pitch_index+pshift_zone)+len(form_power))] = np.copy(form_power)


		for i in iterator[:len(form_power)]:
			fftarray[int(((pitch_index+pshift_zone)+i)*form_shift)] = form_power[i]
			if (((pitch_index+pshift_zone)*form_shift)>CHUNK):
				break
			
		ifftarray = (np.fft.ifft(fftarray)).real
		output = stream.write(ifftarray.astype(np.float32), num_frames=CHUNK)

if __name__ == '__main__':
	thr1 = threading.Thread(target=AudioThr)
	thr1.setDaemon(True)
	thr1.start()
	str = "NONSTOP"
	while(str == "NONSTOP"):
		try:
			str = input()    
		except KeyboardInterrupt:
			break
