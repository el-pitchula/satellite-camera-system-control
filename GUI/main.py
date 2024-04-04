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

# Inicializar a comunicação serial
ser = serial.Serial('COMX', 9600)  # Substitua 'COMX' pela porta serial correta

# Função para enviar comandos para o Arduino
def enviar_comando(comando):
    ser.write(comando.encode())

# Função para receber dados do Arduino
def receber_dados():
    return ser.readline().decode().strip()

# Função para capturar e exibir a visão da câmera
def capturar_camera():
    cap = cv2.VideoCapture(0)  # Captura de vídeo da câmera (substitua 0 pela câmera correta)
    
    while True:
        ret, frame = cap.read()  # Captura um quadro do vídeo
        
        if ret:
            # Converter a imagem OpenCV em formato adequado para Tkinter
            img = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(img)
            imgtk = ImageTk.PhotoImage(image=img)
            
            # Exibir a imagem na interface
            label_camera.imgtk = imgtk
            label_camera.config(image=imgtk)
        
        # Atualizar a interface
        janela.update_idletasks()
        janela.update()

# Criar janela principal
janela = tk.Tk()
janela.title('Estabilidade da Câmera no Satélite')

# Criar label para exibir a visão da câmera
label_camera = tk.Label(janela)
label_camera.pack()

# Botão para iniciar a captura da câmera
botao_capturar = tk.Button(janela, text='Capturar Câmera', command=capturar_camera)
botao_capturar.pack()

# Função para resetar o sistema
def resetar_sistema():
    enviar_comando('R')  # Enviar comando 'R' para resetar o sistema no Arduino
    time.sleep(1)  # Aguardar 1 segundo
    dados = receber_dados()  # Receber dados do Arduino
    print('Dados recebidos:', dados)

# Criar botão de reset
botao_reset = tk.Button(janela, text='Resetar Sistema', command=resetar_sistema)
botao_reset.pack()

# Função para mostrar o monitor serial em uma nova janela
def mostrar_monitor_serial():
    # Lógica para mostrar o monitor serial em uma nova janela
    pass

# Carregar o ícone do monitor serial
icon_serial = Image.open('Python/assets/icon_serial.png')
icon_serial = icon_serial.resize((32, 32), Image.ANTIALIAS)  # Redimensionar o ícone se necessário
icon_serial = ImageTk.PhotoImage(icon_serial)

# Criar botão com o ícone para abrir o monitor serial
botao_serial = tk.Button(janela, image=icon_serial, command=mostrar_monitor_serial)
botao_serial.pack()

# Função para mostrar informações relevantes do projeto em uma nova janela
def mostrar_informacoes():
    # Lógica para mostrar informações relevantes do projeto em uma nova janela
    pass

# Carregar o ícone de informações
icon_info = Image.open('Python/assets/icon_info.png')
icon_info = icon_info.resize((32, 32), Image.ANTIALIAS)  # Redimensionar o ícone se necessário
icon_info = ImageTk.PhotoImage(icon_info)

# Criar botão com o ícone para mostrar informações relevantes
botao_info = tk.Button(janela, image=icon_info, command=mostrar_informacoes)
botao_info.pack()

# Loop principal da interface gráfica
janela.mainloop()
