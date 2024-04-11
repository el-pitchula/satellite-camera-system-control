import tkinter as tk
from tkinter import messagebox
import customtkinter as ctk

# Definindo a aparência e o tema padrão para dark e blue
ctk.set_appearance_mode("dark")
ctk.set_default_color_theme("blue")

pokemon_info = [['Bulbasaur', 'Grass', '318'], ['Ivysaur', 'Grass', '405']]

class LoginPage(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.geometry("626x431")
        self.title("Modern Login UI using Customtkinter")

        main_frame = ctk.CTkFrame(self)
        main_frame.pack(fill="both", expand=True)
        main_frame._bg_color = ctk.get_color("bg")  # Define a cor de fundo do frame

        frame_login = ctk.CTkFrame(main_frame, relief="groove", bd=2)
        frame_login.place(rely=0.30, relx=0.17, height=130, width=400)

        label_title = ctk.CTkLabel(frame_login, text="Login Page", font=("Trebuchet MS Bold", 16))
        label_title.grid(row=0, column=1, columnspan=1)

        label_user = ctk.CTkLabel(frame_login, text="Username:", font=("Verdana", 14))
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(frame_login, text="Password:", font=("Verdana", 14))
        label_pw.grid(row=2, column=0)

        self.entry_user = ctk.CTkEntry(frame_login, width=45, cursor="xterm")
        self.entry_user.grid(row=1, column=1)

        self.entry_pw = ctk.CTkEntry(frame_login, width=45, cursor="xterm", show="*")
        self.entry_pw.grid(row=2, column=1)

        button = ctk.CTkButton(frame_login, text="Login", command=self.get_login)
        button.place(rely=0.70, relx=0.50)

        signup_btn = ctk.CTkButton(frame_login, text="Register", command=self.get_signup)
        signup_btn.place(rely=0.70, relx=0.75)

    def get_signup(self):
        SignupPage()

    def get_login(self):
        username = self.entry_user.get()
        password = self.entry_pw.get()
        validation = self.validate(username, password)
        if validation:
            messagebox.showinfo("Login Successful", "Welcome {}".format(username))
            root.deiconify()
            top.destroy()
        else:
            messagebox.showerror("Information", "The Username or Password you have entered are incorrect ")

    def validate(self, username, password):
        try:
            with open("credentials.txt", "r") as credentials:
                for line in credentials:
                    line = line.split(",")
                    if line[1] == username and line[3] == password:
                        return True
                return False
        except FileNotFoundError:
            print("You need to Register first or amend Line 71 to if True:")
            return False


class SignupPage(tk.Toplevel):
    def __init__(self, *args, **kwargs):
        tk.Toplevel.__init__(self, *args, **kwargs)
        self.geometry("250x150")
        self.title("Registration")

        main_frame = ctk.CTkFrame(self)
        main_frame.pack(fill="both", expand=True)
        main_frame._bg_color = ctk.get_color("bg")  # Define a cor de fundo do frame

        label_user = ctk.CTkLabel(main_frame, text="New Username:", font=("Verdana", 10))
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(main_frame, text="New Password:", font=("Verdana", 10))
        label_pw.grid(row=2, column=0)

        self.entry_user = ctk.CTkEntry(main_frame, width=20, cursor="xterm")
        self.entry_user.grid(row=1, column=1)

        self.entry_pw = ctk.CTkEntry(main_frame, width=20, cursor="xterm", show="*")
        self.entry_pw.grid(row=2, column=1)

        button = ctk.CTkButton(main_frame, text="Create Account", command=self.signup)
        button.grid(row=4, column=1)

    def signup(self):
        user = self.entry_user.get()
        pw = self.entry_pw.get()
        validation = self.validate_user(user)
        if not validation:
            messagebox.showerror("Information", "That Username already exists")
        else:
            if len(pw) > 3:
                credentials = open("credentials.txt", "a")
                credentials.write(f"Username,{user},Password,{pw},\n")
                credentials.close()
                messagebox.showinfo("Information", "Your account details have been stored.")
                self.destroy()
            else:
                messagebox.showerror("Information", "Your password needs to be longer than 3 values.")

    def validate_user(self, username):
        try:
            with open("credentials.txt", "r") as credentials:
                for line in credentials:
                    line = line.split(",")
                    if line[1] == username:
                        return False
            return True
        except FileNotFoundError:
            return True

root = LoginPage()
root.mainloop()
