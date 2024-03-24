import matplotlib.pyplot as plt
import numpy as np

import subprocess



xpoints = []
ypoints = []

for i in range(0, 18):
    num_pages = (2**i)
    print("number of pages = {}".format(num_pages))
    output = subprocess.run(['bin/tlb', str(num_pages), '20'], 
                            stdout = subprocess.PIPE, 
                            stderr = subprocess.PIPE,
                            text=True)
    
    elapsed_ms = float(output.stdout.strip("\n").strip(" ms"))
    print(elapsed_ms)

    xpoints = np.append(xpoints, num_pages)
    ypoints = np.append(ypoints, elapsed_ms)


plt.title('TLB Size Measurement')
plt.xlabel('Number of pages')
plt.ylabel('Time per access (ms)')

plt.plot(xpoints, ypoints, 'ro')
plt.savefig('bin/foo.png')
