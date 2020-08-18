# -*- coding:utf-8 -*-
#Reference:https://qiita.com/MuAuan/items/675854ab602595c79612

import pyaudio
import numpy as np
from scipy import signal
import math
import threading

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

RATE=96000
p=pyaudio.PyAudio()

CHUNK=int(input("Buffer size?："))
GainSet_L = np.ones(CHUNK)
GainSet_R = np.ones(CHUNK)
fftres = RATE/CHUNK
xfreq = np.fft.fftfreq(CHUNK, d=(1/RATE))
window = CreateWindow(CHUNK, 0)
pregain_arr = np.zeros(CHUNK)
gain1 = 1/((window[:int(CHUNK/2)]+window[int(CHUNK/2):]))
pregain_arr[:int(CHUNK/2)] = gain1
pregain_arr[int(CHUNK/2):] = gain1
id20k = np.where(abs(xfreq)>20000)

print('FFT Resolution:%6.4f[Hz]'%(fftres))
print('FFT Length:%d'%(CHUNK))
print()

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

MVol = 1
n_channel=2
stream=p.open(  format = pyaudio.paFloat32,
		channels = n_channel,
		rate = RATE,
		frames_per_buffer = CHUNK,
		input = True,
		output = True,
		input_device_index=idev,
		output_device_index=odev )

terminate_req = False
def AudioThr():
	buffer_size = CHUNK*n_channel
	write_buffer = np.zeros(buffer_size)

	input_data_cur = np.zeros(buffer_size)

	input_array_prev = np.zeros(buffer_size)
	input_array_cur = np.zeros(buffer_size)

	ifftarray_L = (np.zeros(CHUNK)).astype(complex)
	ifftarray_R = (np.zeros(CHUNK)).astype(complex)

	input_array_mid_L = np.zeros(CHUNK)
	input_array_mid_R = np.zeros(CHUNK)
	
	while stream.is_active():
		try:
			input_data_cur = stream.read(CHUNK)
		except OSError:
			print("retry:")
			input_data_cur = stream.read(CHUNK)



		input_array_prev = input_array_cur
		input_array_cur = np.frombuffer(input_data_cur, dtype=np.float32)

		length = len(input_array_prev)
		input_array_prev_L = input_array_prev[0:length:2]*window
		input_array_prev_R = input_array_prev[1:length:2]*window

		length2 = len(input_array_cur)
		input_array_cur_L = input_array_cur[0:length2:2]*window
		input_array_cur_R = input_array_cur[1:length2:2]*window

		input_array_mid_L[:int((CHUNK/2))] = input_array_prev_L[int(CHUNK/2):]
		input_array_mid_L[int(CHUNK/2):] = input_array_cur_L[:int((CHUNK/2))]
		input_array_mid_L = input_array_mid_L*window
		
		input_array_mid_R[:int((CHUNK/2))] = input_array_prev_R[int(CHUNK/2):]
		input_array_mid_R[int(CHUNK/2):] = input_array_cur_R[:int((CHUNK/2))]
		input_array_mid_R = input_array_mid_R*window

		#Lch manipulation
		fftarray_prev_L = np.fft.fft(input_array_prev_L)
		fftarray_prev_L = fftarray_prev_L*GainSet_L#gain manipulation
		ifftarray_prev_L = (np.fft.ifft(fftarray_prev_L))

		fftarray_mid_L = np.fft.fft(input_array_mid_L)
		fftarray_mid_L = fftarray_mid_L*GainSet_L#gain manipulation
		ifftarray_mid_L = (np.fft.ifft(fftarray_mid_L))

		fftarray_cur_L = np.fft.fft(input_array_cur_L)
		fftarray_cur_L = fftarray_cur_L*GainSet_L#gain manipulation
		ifftarray_cur_L = (np.fft.ifft(fftarray_cur_L))

		#Rch manipulation
		fftarray_prev_R = np.fft.fft(input_array_prev_R)
		fftarray_prev_R = fftarray_prev_R*GainSet_R#gain_manipulation
		ifftarray_prev_R = (np.fft.ifft(fftarray_prev_R))

		fftarray_mid_R = np.fft.fft(input_array_mid_R)
		fftarray_mid_R = fftarray_mid_R*GainSet_R#gain_manipulation
		ifftarray_mid_R = (np.fft.ifft(fftarray_mid_R))

		fftarray_cur_R = np.fft.fft(input_array_cur_R)
		fftarray_cur_R = fftarray_cur_R*GainSet_R#gain_manipulation
		ifftarray_cur_R = (np.fft.ifft(fftarray_cur_R))

		ifftarray_L[:int(CHUNK/2)] = (ifftarray_prev_L[int(len(ifftarray_prev_L)/2):]+ifftarray_mid_L[:int((len(ifftarray_mid_L)/2))])
		ifftarray_L[int(CHUNK/2):] = (ifftarray_mid_L[int(len(ifftarray_mid_L)/2):]+ifftarray_cur_L[:int((len(ifftarray_cur_L)/2))])
		ifftarray_R[:int(CHUNK/2)] = (ifftarray_prev_R[int(len(ifftarray_prev_R)/2):]+ifftarray_mid_R[:int((len(ifftarray_mid_R)/2))])
		ifftarray_R[int(CHUNK/2):] = (ifftarray_mid_R[int(len(ifftarray_mid_R)/2):]+ifftarray_cur_R[:int((len(ifftarray_cur_R)/2))])

		ifftarray_L = ifftarray_L*pregain_arr
		ifftarray_R = ifftarray_R*pregain_arr

		write_buffer[0:buffer_size:2] = ifftarray_L.real
		write_buffer[1:buffer_size:2] = ifftarray_R.real

		write_buffer=write_buffer*MVol
		output = stream.write(write_buffer.astype(np.float32), num_frames=CHUNK)

debug_enabled = True

if __name__ == '__main__':
	thr1 = threading.Thread(target=AudioThr)
	thr1.setDaemon(True)
	thr1.start()
	if debug_enabled:
		print("---DEBUG---")
		print("fftfreq:")
		print(np.shape(np.fft.fftfreq(CHUNK, d=(1/RATE))))
		print(np.fft.fftfreq(CHUNK, d=(1/RATE)))
		print("---DEBUG---")

	while(True):
		try:
			str = input()   
			if(str=="mvol"):
				MVol = float(input("gain?(ratio)："))
			if(str=="mute"):
				MVol = 0
			if(str=="exit"):
				break
			if(str=="CWIN"):
				print("window:")
				print("0:Square")
				print("1:Gaussian")
				print("2:Hanning")
				print("3:Sin")
				print("4:Vorbis")
				print("5:Blackman")
				print("6:Nuttall")
				print("7:Blackman-Harris")
				print("8:Kaiser")
				print("9:Dolph-Chebyshev(100dB)")
				wnum = int(input("window?"))
				if(wnum==8):
					beta_1 = float(input("beta?"))
					window = CreateWindow(CHUNK, wnum, ckbeta=beta_1)
				else:
					window = CreateWindow(CHUNK, wnum)

				gain1 = 1/((window[:int(CHUNK/2)]+window[int(CHUNK/2):]))
				pregain_arr[:int(CHUNK/2)] = gain1
				pregain_arr[int(CHUNK/2):] = gain1
				if debug_enabled:
					print("---DEBUG---")
					print("gain:")
					print(pregain_arr)
					print("---DEBUG---")

			if(str=="20kcut"):
				GainSet_L[id20k] = 0
				GainSet_R[id20k] = 0
				if debug_enabled:
					print("---DEBUG---")
					print("gainset:")
					print(GainSet_L)
					print("---DEBUG---")
			
			if(str=="wcut"):
				cfreq=float(input("Frequency?[Hz]："))
				idNFreq = np.where(abs(xfreq)>cfreq)
				GainSet_L= np.ones(CHUNK)
				GainSet_R = np.ones(CHUNK)
				GainSet_L[idNFreq] = 0
				GainSet_R[idNFreq] = 0
				if debug_enabled:
					print("---DEBUG---")
					print("gainset:")
					print(GainSet_L)
					print("---DEBUG---")

			if(str=="grecover"):
				GainSet_L= np.ones(CHUNK)
				GainSet_R = np.ones(CHUNK)
				if debug_enabled:
					print("---DEBUG---")
					print("gainset:")
					print(GainSet_L)
					print("---DEBUG---")

		except KeyboardInterrupt:
			break
