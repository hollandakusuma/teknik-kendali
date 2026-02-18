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
# DEFINISI SISTEM (bisa diubah mahasiswa)
# ==========================================

K = 1
zeta = 0.6      # damping ratio
wn = 4          # natural frequency

num = [K * wn**2]
den = [1, 2*zeta*wn, wn**2]
system = ctrl.TransferFunction(num, den)

# ==========================================
# STEP RESPONSE
# ==========================================

t, y = ctrl.step_response(system)

# ==========================================
# HITUNG METRIK PERFORMA
# ==========================================

final_value = y[-1]
overshoot = (np.max(y) - final_value) / final_value * 100

# Settling time (2% band)
tolerance = 0.02 * final_value
settling_indices = np.where(np.abs(y - final_value) > tolerance)[0]

if len(settling_indices) > 0:
    settling_time = t[settling_indices[-1]]
else:
    settling_time = 0

steady_state_error = abs(1 - final_value)

# ==========================================
# VISUALISASI
# ==========================================

plt.figure()

plt.plot(t, y, label="Step Response")
plt.axhline(1, linestyle="--", label="Setpoint (1)")
plt.axhline(1.1, linestyle=":", label="Overshoot 10% Limit")
plt.axhline(0.9, linestyle=":")
plt.axvline(2, linestyle="--", label="Settling Time Limit (2s)")

plt.title("Visualisasi Spesifikasi Sistem")
plt.xlabel("Time (s)")
plt.ylabel("Output")
plt.legend()
plt.grid()
plt.show()

# ==========================================
# CETAK HASIL ANALISIS
# ==========================================

print("===== HASIL ANALISIS =====")
print(f"Overshoot        : {overshoot:.2f}%")
print(f"Settling Time    : {settling_time:.2f} detik")
print(f"Steady-State Err : {steady_state_error:.4f}")

print("\n===== CEK SPESIFIKASI =====")

print("Overshoot < 10%      :", overshoot < 10)
print("Settling Time < 2 s  :", settling_time < 2)
print("Error ≈ 0            :", steady_state_error < 0.02)
