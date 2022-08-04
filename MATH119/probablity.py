
import numpy as np
from scipy.stats import norm

a = np.random.exponential(1/2, 10000000)

print(np.mean(np.sin(a)))

a = np.random.normal(size=10000000)
print(np.mean(a**2))
