import customtkinter

def button_callback():
    print("button clicked")

app = customtkinter.CTk()
app.geometry("400x150")

button = customtkinter.CTkButton(app, text="my button", command=button_callback)
button.pack(padx=20, pady=20)

app.mainloop()