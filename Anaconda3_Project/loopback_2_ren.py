# -*- coding:utf-8 -*-
#Reference:https://qiita.com/MuAuan/items/675854ab602595c79612

import pyaudio
import numpy as np
from scipy import signal
import math
import threading
import windowfuncs as wfc

global window

def calImpulse(clength, garray):
	impulse_array = np.zeros(clength)
	impulse_array[int(clength/2)] = 1
	fft_array = np.fft.fft(impulse_array)
	ifft_array = (np.fft.ifft(fft_array*garray))*window
	return ifft_array.real

RATE=48000
p=pyaudio.PyAudio()

CHUNK=int(input("Buffer size?："))
GainSet_L = np.ones(CHUNK)
GainSet_R = np.ones(CHUNK)
fftres = RATE/CHUNK
xfreq = np.fft.fftfreq(CHUNK, d=(1/RATE))
window = wfc.CreateWindow(CHUNK, 0)
pregain_arr = np.zeros(CHUNK)
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

impulse_array_L = calImpulse(CHUNK, GainSet_L)
impulse_array_R = calImpulse(CHUNK, GainSet_R)
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

def AudioThr():
	buffer_size = CHUNK*n_channel
	write_buffer = np.zeros(buffer_size)
	halfLength = int(CHUNK/2)+1
	itr1 = np.arange(0, CHUNK, 1)

	input_data_cur = np.zeros(buffer_size)
	input_array_cur = np.zeros(buffer_size)

	output_array_L = np.zeros(CHUNK)
	output_array_R = np.zeros(CHUNK)
	conbined_array_L = np.zeros(CHUNK*2)
	conbined_array_R = np.zeros(CHUNK*2)


	while stream.is_active():
		try:
			input_data_cur = stream.read(CHUNK)
		except OSError:
			try:
				print("retry:")
				input_data_cur = stream.read(CHUNK)
			except OSError:
				print("exiting")
				exit()

		input_array_cur = np.frombuffer(input_data_cur, dtype=np.float32)
		length2 = len(input_array_cur)

		"""
		conbined_array_L[:CHUNK] = conbined_array_L[CHUNK:]
		conbined_array_R[:CHUNK] = conbined_array_R[CHUNK:]
		conbined_array_L[CHUNK:] = input_array_cur[0:length2:2]
		conbined_array_R[CHUNK:] = input_array_cur[1:length2:2]

		for ctr in itr1:
			temparray_L = np.convolve(conbined_array_L[ctr:(ctr+halfLength)], impulse_array_L[:halfLength], mode="same")
			temparray_R = np.convolve(conbined_array_R[ctr:(ctr+halfLength)], impulse_array_R[:halfLength], mode="same")
			output_array_L[ctr] = temparray_L[halfLength-1]
			output_array_R[ctr] = temparray_R[halfLength-1]
		"""

		output_array_L = np.convolve(input_array_cur[0:length2:2], impulse_array_L, mode="same")
		output_array_R = np.convolve(input_array_cur[1:length2:2], impulse_array_R, mode="same")
		write_buffer[0:buffer_size:2] = output_array_L*MVol
		write_buffer[1:buffer_size:2] = output_array_R*MVol
		stream.write(write_buffer.astype(np.float32), num_frames=CHUNK)

debug_enabled = False
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
					window = wfc.CreateWindow(CHUNK, wnum, ckbeta=beta_1)
				else:
					window = wfc.CreateWindow(CHUNK, wnum)

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
				impulse_array_L = calImpulse(CHUNK, GainSet_L)
				impulse_array_R = calImpulse(CHUNK, GainSet_R)
				if debug_enabled:
					print("---DEBUG---")
					print("gainset:")
					print(GainSet_L)
					print("---DEBUG---")

			if(str=="grecover"):
				GainSet_L= np.ones(CHUNK)
				GainSet_R = np.ones(CHUNK)
				impulse_array_L = calImpulse(CHUNK, GainSet_L)
				impulse_array_R = calImpulse(CHUNK, GainSet_R)

				if debug_enabled:
					print("---DEBUG---")
					print("gainset:")
					print(GainSet_L)
					print("---DEBUG---")

		except KeyboardInterrupt:
			break
