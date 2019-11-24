import sys
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator



fileName=sys.argv[1]

f=open(fileName,"r")
contents =f.readlines()
print(contents)
ptsPdm=[]
ptCount=[]
contador=1
for i in contents:
    ptsPdm.append(float(i))
    ptCount.append(int(contador))
    contador=contador+1

x = np.array(ptCount)
y = np.array(ptsPdm)


ax = plt.figure().gca()
ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.plot(x, y, '-',x, y, 'o')
plt.legend(['linear', 'pontos pdm'], loc='best')
plt.title('Variação da distância PDM para diferentes perspectivas')
plt.ylabel('Distância PDM')
plt.xlabel('Número de perspectiva')

plt.show()
