import numpy as np
import matplotlib.pyplot as plt

# Parameter sistem
a = 0.8           # karakteristik sistem
dt = 0.01         # step waktu
T = 5             # total waktu simulasi
time = np.arange(0, T, dt)

# Variasi gain
Kp = 2.0
Kd = 0.5

# Inisialisasi
error = np.zeros(len(time))
derror = np.zeros(len(time))
u = np.zeros(len(time))

error[0] = 5   # error awal (misal robot terlalu dekat dinding)

for i in range(1, len(time)):
    derror[i] = (error[i-1] - error[i-2]) / dt if i > 1 else 0
    u[i] = Kp * error[i-1] + Kd * derror[i]
    error[i] = error[i-1] - a * u[i] * dt

plt.figure()
plt.plot(time, error)
plt.xlabel("Time (s)")
plt.ylabel("Error")
plt.title("Respons Error terhadap Waktu")
plt.show()
