# interface gráfica GUI (pyserial e tkinter)

"""
import tkinter as tk

# janela principal
janela = tk.Tk()
janela.title('Estabilidade da Câmera no Satélite')

# widgets (botões, labels...)
label = tk.Label(janela, text='Interface Gráfica para Estabilidade da Câmera')
label.pack()

botao_reset = tk.Button(janela, text='Resetar Sistema')
botao_reset.pack()

# Loop principal da interface gráfica
janela.mainloop()
"""


import tkinter as tk

# Criar janela principal
janela = tk.Tk()
janela.title('Estabilidade da Câmera no Satélite')

# Criar label para exibir a visão da câmera
label_camera = tk.Label(janela, text='Visão da Câmera (GoPro)')
label_camera.pack()

# Criar label para exibir o modelo 3D do MPU6050
label_mpu = tk.Label(janela, text='Modelo 3D do MPU6050')
label_mpu.pack()

# Criar gráfico em branco para o controle PID
canvas_grafico = tk.Canvas(janela, width=400, height=300, bg='white')
canvas_grafico.pack()

# Botão para resetar o sistema
botao_reset = tk.Button(janela, text='Resetar Sistema')
botao_reset.pack()

# Função para mostrar o monitor serial em uma nova janela
def mostrar_monitor_serial():
    # Lógica para mostrar o monitor serial em uma nova janela
    pass

# Criar botão para abrir o monitor serial
botao_serial = tk.Button(janela, text='Monitor Serial', command=mostrar_monitor_serial)
botao_serial.pack()

# Função para mostrar informações relevantes do projeto em uma nova janela
def mostrar_informacoes():
    # Lógica para mostrar informações relevantes do projeto em uma nova janela
    pass

# Criar botão para mostrar informações relevantes
botao_info = tk.Button(janela, text='Informações', command=mostrar_informacoes)
botao_info.pack()

# Loop principal da interface gráfica
janela.mainloop()
