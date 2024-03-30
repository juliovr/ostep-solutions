import matplotlib.pyplot as plt
import numpy as np

import subprocess

xpoints = []
ypoints = []

for nthreads in range(1, 41):
    sample_size = 10_000_000
    
    print("sample_size = {}".format(sample_size))
    print("nthreads = {}".format(nthreads))

    output = subprocess.run(['bin/linked_list_hand_over_hand_locking', str(nthreads), str(sample_size)], 
                            stdout = subprocess.PIPE, 
                            stderr = subprocess.PIPE,
                            text = True)
    
    elapsed = float(output.stdout.strip("\n").strip("elapsed time = ").strip(" sec"))
    print(elapsed)

    xpoints = np.append(xpoints, nthreads)
    ypoints = np.append(ypoints, elapsed)


plt.title('Linked list hand-over-hand locking')
plt.xlabel('threads')
plt.ylabel('Time (sec)')

plt.plot(xpoints, ypoints, 'ro')
plt.savefig('bin/linked_list_hand_over_hand_locking.png')
