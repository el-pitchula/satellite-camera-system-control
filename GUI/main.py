# comunicação com o arduino

"""
import serial
import time

# comunicação serial
ser = serial.Serial('COMX', 9600)  # COMX é a porta serial

# funções para enviar e receber comandos do Arduino
def enviar_comando(comando):
    ser.write(comando.encode())
def receber_dados():
    return ser.readline().decode().strip()

# exemplo
enviar_comando('R')  # enviar comando 'R' para resetar o sistema no Arduino
time.sleep(1)  # espera 1s
dados = receber_dados()
print('Dados recebidos:', dados)

ser.close() # fechar a comunicação serial
"""

import tkinter as tk
from PIL import Image, ImageTk
import cv2
import matplotlib.pyplot as plt
from mayavi import mlab
import serial
import time

ser = serial.Serial('COMX', 9600)

def enviar_comando(comando):
    ser.write(comando.encode())

def receber_dados():
    return ser.readline().decode().strip()

def capturar_camera():
    cap = cv2.VideoCapture(0)
    
    while True:
        ret, frame = cap.read() # em vídeo
        
        if ret:
            # converter a imagem OpenCV em formato adequado para Tkinter
            img = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(img)
            imgtk = ImageTk.PhotoImage(image=img)
            
            # exibir a imagem na interface
            label_camera.imgtk = imgtk
            label_camera.config(image=imgtk)
        
        # real time
        janela.update_idletasks()
        janela.update()

# janela principal
janela = tk.Tk()
janela.title('Estabilidade da Câmera no Satélite')

# label para exibir a visão da câmera
label_camera = tk.Label(janela)
label_camera.pack()
# botão para iniciar câmera
botao_capturar = tk.Button(janela, text='Capturar Câmera', command=capturar_camera)
botao_capturar.pack()

def resetar_sistema():
    enviar_comando('R')  # enviar comando 'R' para resetar o sistema no Arduino
    time.sleep(1)
    dados = receber_dados()
    print('Dados recebidos:', dados)

# botão reset
botao_reset = tk.Button(janela, text='Resetar Sistema', command=resetar_sistema)
botao_reset.pack()

# monitor serial em uma nova janela
def mostrar_monitor_serial():
    # criar lógica para mostrar o monitor serial
    pass

icon_serial = Image.open('Python/assets/icon_serial.png')
icon_serial = icon_serial.resize((32, 32), Image.ANTIALIAS) # redimencionar
icon_serial = ImageTk.PhotoImage(icon_serial)
botao_serial = tk.Button(janela, image=icon_serial, command=mostrar_monitor_serial)
botao_serial.pack()

# info em uma nova janela
def mostrar_informacoes():
    # criar lógica para mostrar informações do projeto
    pass

icon_info = Image.open('Python/assets/icon_info.png')
icon_info = icon_info.resize((32, 32), Image.ANTIALIAS)
icon_info = ImageTk.PhotoImage(icon_info)
botao_info = tk.Button(janela, image=icon_info, command=mostrar_informacoes)
botao_info.pack()

# loop principal da interface gráfica (GUI)
janela.mainloop()
