import cv2
import numpy as np
from matplotlib import pyplot as plt
import sys
import pyautogui
import matplotlib.patches as patches
from PIL import Image
import numpy as np
import math
from scipy.interpolate import interp1d
import scipy as sp
from scipy import interpolate
from scipy.interpolate import CubicSpline

nomeImagem=sys.argv[1]
nomeTextoPontoFronteira=sys.argv[2]
#rangeOfRead = sys.argv[3]
f=open(nomeTextoPontoFronteira, "r")
contents =f.readlines()
dpi = plt.rcParams['figure.dpi']
im_data = plt.imread(nomeImagem,0)
height, width, depth = im_data.shape
contador=0
# What size does the figure need to be in inches to fit the image?
figsize = width / float(dpi), height / float(dpi)
vetorPontosArquivos=[]#vetor para o tamanho dos pontos
distanciasPdm=[]
vetorDistancia=[]

# Create a figure of the right size with one axes that takes up the full figure
fig = plt.figure(figsize=figsize)
ax = fig.add_axes([0, 0, 1, 1])
vetorPontos=[]
ponto=[]
pontosDoCanny=[]
pontosDoCannyReal=[]
ax.axis('off')
edges = cv2.Canny(im_data,50,100)
ax.imshow(edges, cmap='gray')

#for ix in range(0,int(rangeOfRead),1):
    #f=open(nomeTextoPontoFronteira+str(ix), "r")
    #contents = f.readlines()
    #pts=[]#pontos dos arquivos
    #print("Arquivo: ",ix)
pts=[]
for ct in contents:
    txt = ct.split(",")
    #pts.append(float(txt[0]))
    #pts.append(float(txt[1]))
    vetorPontosArquivos.append(float(txt[0]))
    vetorPontosArquivos.append(float(txt[1]))

#print("ola destro, ",vetorPontosArquivos)

def display_pdm_distance():
    #print('começo aqui: ',vetorPontosArquivos)
    #calculando PDM de F1 para F2 (dos pontos de fronteira para os pontos do canny)

    #for i in range(0,len(vetorPontosArquivos),1):#esses são os pontos de fronteira
        soma1=0
        soma2=0
        for j in range(1,len(vetorPontosArquivos),2):
            dmin1=1000000
            x1=vetorPontosArquivos[j-1]
            y1=vetorPontosArquivos[j]
            for k in range(3,len(pontosDoCannyReal),2):#canny deve retornar pelo menos 2 pontos para comparar, senão o programa crasha "er er"
                    x3=pontosDoCannyReal[k-1]
                    y3=pontosDoCannyReal[k]
                    x2=pontosDoCannyReal[k-3]
                    y2=pontosDoCannyReal[k-2]
                    d1=(x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
                    d1=math.sqrt(d1)
                    d2=(x1-x3)*(x1-x3) + (y1-y3)*(y1-y3)
                    d2=math.sqrt(d2)
                    ly1=((y3-y2)*(y1-y2)+(x3-x2)*(x1-x2))
                    ly2=((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))

                    if ly2 == 0:
                        ly2=2
                    if ly2 != 0:
                         ly=ly1/ly2

                    if (ly < 0 or ly >1) and dmin1 >min(d1,d2) :
                        dmin1=min(d1,d2)
                        #soma1=soma1+dmin1
                    else:
                       dp1=math.fabs(((y3-y2)*(x2-x1)+(x3-x2)*(y1-y2)))
                       dp2=math.sqrt(((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)))
                       if(dp2==0):
                         dmin1=min(min(d1,d2),dmin1)
                       else:
                         dp=dp1/dp2
                         dmin1=min(dmin1,dp)
            soma1=soma1+dmin1
            vetorDistancia.append(dmin1)

        for j in range(1,len(pontosDoCannyReal),2):
            dmin2=1000000
            x1=pontosDoCannyReal[j-1]
            y1=pontosDoCannyReal[j]
            for k in range(3,len(vetorPontosArquivos),2):#canny deve retornar pelo menos 2 pontos para comparar, senão o programa crasha "er er"
                    x3=vetorPontosArquivos[k-1]
                    y3=vetorPontosArquivos[k]
                    x2=vetorPontosArquivos[k-3]
                    y2=vetorPontosArquivos[k-2]
                    d1=(x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
                    d1=math.sqrt(d1)
                    d2=(x1-x3)*(x1-x3) + (y1-y3)*(y1-y3)
                    d2=math.sqrt(d2)
                    ly1=((y3-y2)*(y1-y2)+(x3-x2)*(x1-x2))
                    ly2=((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))
                    if ly2 == 0:
                        ly2=2
                    if ly2 != 0:
                         ly=ly1/ly2

                    if (ly < 0 or ly >1) and dmin2 >min(d1,d2) :
                        dmin2=min(d1,d2)

                    else:
                        dp1=math.fabs(((y3-y2)*(x2-x1)+(x3-x2)*(y1-y2)))
                        dp2=math.sqrt(((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)))
                        if(dp2==0):
                           dmin2=min(min(d1,d2),dmin2)
                        else:
                          dp=dp1/dp2
                          dmin2=min(dmin2,dp)
        soma2=soma2+dmin2

        calcpdm=(soma1+soma2)/(len(vetorPontosArquivos)+len(pontosDoCannyReal))
        distanciasPdm.append(calcpdm)


        #calcular media, variancia e desvio padrão da amostra das menores distancias dos pontos de fronteira até o padrão ouro
        somaMedia=0
        desvpad=0
        varian=0
        for k in range(0,len(vetorDistancia),1):
            somaMedia=somaMedia+vetorDistancia[k]

        somaMedia=somaMedia/len(vetorDistancia)

        for k in range(0,len(vetorDistancia),1):
            varian=varian+((vetorDistancia[k]-somaMedia)*(vetorDistancia[k]-somaMedia))

        desvpad=math.sqrt(varian/len(vetorDistancia))

        print('distancias pdm: ',calcpdm)
        print('desvio padrao: ',somaMedia,'+/-',desvpad)
        pdmToArchive= open("pdmGraphic","a+")
        pdmToArchive.write(str(calcpdm)+"\n")
        pdmToArchive.close()


def onclick(event):

    global contador
    if contador <= 1:
        plt.scatter(int(event.xdata), int(event.ydata), s=15)
        fig.canvas.draw()
        contador=contador+1
        ponto.append(int(event.xdata))
        ponto.append(int(event.ydata))
        #print(ponto)
        vetorPontos.append(ponto)

    if contador==2:

        contador=contador+1
        #print(vetorPontos)
        rect = patches.Rectangle((vetorPontos[0][0],vetorPontos[0][1]),vetorPontos[1][2]-vetorPontos[0][0],vetorPontos[1][3]-vetorPontos[0][1],linewidth=1,edgecolor='r',facecolor='none')
        ax.add_patch(rect)

        if vetorPontos[0][0] < vetorPontos[0][2] and vetorPontos[0][1] < vetorPontos[0][3]:

            for i in range(vetorPontos[0][0],vetorPontos[0][2],1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],1):
                     if(edges[j,i] >= 250):

                         #plt.scatter(i,j, s=2,color="black")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)


        elif vetorPontos[0][0] > vetorPontos[0][2] and vetorPontos[0][1] > vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],-1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],-1):
                     if(edges[j,i] >= 250):

                         #plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)

        elif vetorPontos[0][0] > vetorPontos[0][2] and vetorPontos[0][1] < vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],-1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],1):
                     if(edges[j,i] >= 250):

                         #plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)

        elif vetorPontos[0][0] < vetorPontos[0][2] and vetorPontos[0][1] > vetorPontos[0][3]:
            for i in range(vetorPontos[0][0],vetorPontos[0][2],1):
                for j in range(vetorPontos[0][1],vetorPontos[0][3],-1):
                     if(edges[j,i] >= 250):

                         #plt.scatter(i,j, s=2,color="red")
                         pontosDoCanny.append(i-320)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)
                         pontosDoCanny.append(240-j)#se o tamanho da tela for ajustado, não esqueça de ajustar esse parâmetro também :)


        x=[]
        y=[]

        for i in range(1,len(pontosDoCanny),2):

            x.append(pontosDoCanny[i-1]+320)
            y.append(240-pontosDoCanny[i])


        x=np.array(x)
        y=np.array(y)
        #print('x',x)
        #print('teste1',np.any(False))
        #print('teste2',x[:-1])



        interpolacao_linear = interp1d(x,y, kind='linear')
        xl = sorted(x)
        eixo_x = np.linspace(xl[0], xl[len(x)-1],500)
        interp = interpolacao_linear(eixo_x)
        #print('teste aqui ',interp)

        for i in range(0,len(eixo_x),1):
            if interp[i] != 'nan':
                pontosDoCannyReal.append(eixo_x[i]-320)
                pontosDoCannyReal.append(240-interp[i])
                plt.scatter(eixo_x[i],interp[i], s=4,color="green")

        print('tamanho',len(vetorPontosArquivos))
        #for i in range(1,len(vetorPontosArquivos),2):
          # plt.scatter(vetorPontosArquivos[i-1]+320,240-vetorPontosArquivos[i], s=4,color="red")

        fig.canvas.draw()
        #print('pontos do canny ',pontosDoCanny)


        #print('x: ',x,'y ',y,' interp ',interp)




def display_image_in_actual_size():
    cid = fig.canvas.mpl_connect('button_press_event', onclick)
    plt.show()


display_image_in_actual_size()
display_pdm_distance()
