import numpy as np
import pyaudio 

stream = pyaudio.PyAudio()
dev_index = np.arange(stream.get_device_count())
print("device ID, device name:")
for idx in dev_index:
    print("ID%4d：%s"%(idx, (stream.get_device_info_by_index(idx))['name']), end='')
    print()

