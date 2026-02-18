import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

# Parameter sistem
K = 1
tau = 1

# Waktu simulasi
t = np.linspace(0, 10, 1000)

# Open-loop: G(s) = K / (tau*s + 1)
num_open = [K]
den_open = [tau, 1]
system_open = signal.TransferFunction(num_open, den_open)

# Closed-loop: T(s) = G(s) / (1 + G(s))
# = K / (tau*s + 1 + K)
num_closed = [K]
den_closed = [tau, 1 + K]
system_closed = signal.TransferFunction(num_closed, den_closed)

# Step response
t1, y_open = signal.step(system_open, T=t)
t2, y_closed = signal.step(system_closed, T=t)

# Plot
plt.figure()
plt.plot(t1, y_open, label="Open-Loop")
plt.plot(t2, y_closed, label="Closed-Loop (Unity Feedback)")
plt.title("Open-Loop vs Closed-Loop Step Response")
plt.xlabel("Time (seconds)")
plt.ylabel("Output")
plt.legend()
plt.grid(True)
plt.show()
