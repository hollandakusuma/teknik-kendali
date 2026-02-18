# ==========================================
# INSTALL LIBRARY (jalankan sekali saja)
# ==========================================
!pip install control

# ==========================================
# IMPORT LIBRARY
# ==========================================
import numpy as np
import matplotlib.pyplot as plt
import control as ctrl

# ==========================================
# SISTEM 1 – JELAS BERMASALAH
# Overshoot besar & settling lama
# ==========================================

K1 = 1
zeta1 = 0.2      # redaman kecil → overshoot besar
wn1 = 2          # natural frequency rendah → lambat

num1 = [K1 * wn1**2]
den1 = [1, 2*zeta1*wn1, wn1**2]
system1 = ctrl.TransferFunction(num1, den1)

t1, y1 = ctrl.step_response(system1)

plt.figure()
plt.plot(t1, y1)
plt.axhline(1,color="red")
plt.title("Step Response - Sistem Bermasalah")
plt.xlabel("Time (s)")
plt.ylabel("Output")
plt.grid()
plt.show()


# ==========================================
# SISTEM 2 – BORDERLINE
# Overshoot kecil & lebih cepat stabil
# ==========================================

K2 = 1
zeta2 = 0.6      # redaman lebih baik
wn2 = 4          # lebih cepat

num2 = [K2 * wn2**2]
den2 = [1, 2*zeta2*wn2, wn2**2]
system2 = ctrl.TransferFunction(num2, den2)

t2, y2 = ctrl.step_response(system2)

plt.figure()
plt.plot(t2, y2)
plt.axhline(1,color="red")
plt.title("Step Response - Sistem Borderline")
plt.xlabel("Time (s)")
plt.ylabel("Output")
plt.grid()
plt.show()
