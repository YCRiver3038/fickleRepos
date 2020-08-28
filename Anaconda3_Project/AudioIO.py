# -*- coding:utf-8 -*-
#Reference:https://qiita.com/MuAuan/items/675854ab602595c79612

import pyaudio
import numpy as np
from scipy import signal
import math
import threading

import windowfuncs as wfc

#プロット関係のライブラリ
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import numpy as np
import sys
#音声関係のライブラリ
import struct

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

window = wfc.CreateWindow(CHUNK, wfc._FILTERTYPE['Hanning'])

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
