# ----------- compreendendo estruturas gerais -----------
# link site oficial: https://customtkinter.tomschimansky.com/

import customtkinter

def button_callback(): # ação/função do botão
    print("button pressed") # mostrado no terminal

# propriedades da janela (lib)
app = customtkinter.CTk() # começo da janela
app.title("my app") # título janela
app.geometry("400x150") # tamanho tela
# app.grid_columnconfigure(0, weight=1) # significa q toda a janela é uma COLUNA só
# !!estudar mais a influência dessa função!!

# propriedades do botão (lib)
button = customtkinter.CTkButton(app, text="my button", command=button_callback) # "back" do botão (funcional)
button.grid(row=0, column=0, padx=20, pady=20) # estilo do botão (sistema de grade)

# adiciona duas caixas de seleção na segunda LINHA
# propriedades dos checkbox (lib)
checkbox_1 = customtkinter.CTkCheckBox(app, text="checkbox 1") # def funcionalidade
checkbox_1.grid(row=1, column=0, padx=20, pady=(0, 20), sticky="w") # estilo em grade
checkbox_2 = customtkinter.CTkCheckBox(app, text="checkbox 2")
checkbox_2.grid(row=1, column=1, padx=20, pady=(0, 20), sticky="w")

app.mainloop() # fim da janela

"""
# ----------- Orientado a objeto (a ordem importa): -----------

class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        self.title("my app")
        self.geometry("400x150")
        self.grid_columnconfigure((0, 1), weight=1)

        self.button = customtkinter.CTkButton(self, text="my button", command=self.button_callback)
        self.button.grid(row=0, column=0, padx=20, pady=20, sticky="ew", columnspan=2)
        self.checkbox_1 = customtkinter.CTkCheckBox(self, text="checkbox 1")
        self.checkbox_1.grid(row=1, column=0, padx=20, pady=(0, 20), sticky="w")
        self.checkbox_2 = customtkinter.CTkCheckBox(self, text="checkbox 2")
        self.checkbox_2.grid(row=1, column=1, padx=20, pady=(0, 20), sticky="w")
        
    def button_callback(self):
        print("button pressed")

app = App()
app.mainloop()
"""
