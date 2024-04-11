"""
import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
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

        main_frame = ctk.CTkFrame(self, bg="#708090", height=431, width=626)
        main_frame.pack(fill="both", expand=True)

        frame_login = ctk.CTkFrame(main_frame, bg="blue", relief="groove", bd=2)
        frame_login.place(rely=0.30, relx=0.17, height=130, width=400)

        label_title = ctk.CTkLabel(frame_login, text="Login Page", font=("Trebuchet MS Bold", 16), background="blue")
        label_title.grid(row=0, column=1, columnspan=1)

        label_user = ctk.CTkLabel(frame_login, text="Username:", font=("Verdana", 14), background="blue", foreground="#E1FFFF")
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(frame_login, text="Password:", font=("Verdana", 14), background="blue", foreground="#E1FFFF")
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

        main_frame = ctk.CTkFrame(self, bg="#3F6BAA", height=150, width=250)
        main_frame.pack_propagate(0)
        main_frame.pack(fill="both", expand=True)

        text_styles = {"font": ("Verdana", 10), "background": "#3F6BAA", "foreground": "#E1FFFF"}

        label_user = ctk.CTkLabel(main_frame, text="New Username:", **text_styles)
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(main_frame, text="New Password:", **text_styles)
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

class MyApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.geometry("1024x600")
        self.title("Tkinter App Template")

        main_frame = ctk.CTkFrame(self)
        main_frame.configure(background="#84CEEB", height=600, width=1024)
        main_frame.pack(fill="both", expand=True)
        main_frame.grid_rowconfigure(0, weight=1)
        main_frame.grid_columnconfigure(0, weight=1)
        self.frames = {}
        pages = (Some_Widgets, PageOne, PageTwo, PageThree, PageFour)
        for F in pages:
            frame = F(main_frame, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        self.show_frame(Some_Widgets)
        menubar = MenuBar(self)
        self.config(menu=menubar)

    def show_frame(self, name):
        frame = self.frames[name]
        frame.tkraise()

    def OpenNewWindow(self):
        OpenNewWindow()

    def Quit_application(self):
        self.destroy()


class GUI(tk.Frame):
    def __init__(self, parent):
        tk.Frame.__init__(self, parent)
        self.main_frame = tk.Frame(self, bg="#BEB2A7", height=600, width=1024)
        self.main_frame.pack_propagate(0)
        self.main_frame.pack(fill="both", expand=True)
        self.main_frame.grid_rowconfigure(0, weight=1)
        self.main_frame.grid_columnconfigure(0, weight=1)


class Some_Widgets(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        frame1 = ctk.CTkLabelFrame(self, text="This is a LabelFrame containing a Treeview")
        frame1.place(rely=0.05, relx=0.02, height=400, width=400)

        frame2 = ctk.CTkLabelFrame(self, text="Some widgets")
        frame2.place(rely=0.05, relx=0.45, height=500, width=500)

        button1 = ctk.CTkButton(frame2, text="tk button", command=lambda: Refresh_data())
        button1.pack()
        button2 = ctk.CTkButton(frame2, text="ttk button", command=lambda: Refresh_data())
        button2.pack()

        Var1 = tk.IntVar()
        Var2 = tk.IntVar()
        Cbutton1 = ctk.CTkCheckbutton(frame2, text="tk CheckButton1", variable=Var1, onvalue=1, offvalue=0)
        Cbutton1.pack()
        Cbutton2 = ctk.CTkCheckbutton(frame2, text="tk CheckButton2", variable=Var2, onvalue=1, offvalue=0)
        Cbutton2.pack()

        Cbutton3 = ctk.CTkCheckbutton(frame2, text="ttk CheckButton1", variable=Var1, onvalue=1, offvalue=0)
        Cbutton3.pack()
        Cbutton3 = ctk.CTkCheckbutton(frame2, text="ttk CheckButton2", variable=Var2, onvalue=1, offvalue=0)
        Cbutton3.pack()

        Lbox1 = tk.Listbox(frame2, selectmode="multiple")
        Lbox1.insert(1, "This is a tk ListBox")
        Lbox1.insert(2, "Github")
        Lbox1.insert(3, "Python")
        Lbox1.insert(3, "StackOverflow")
        Lbox1.pack(side="left")

        Var3 = tk.IntVar()
        R1 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton1", variable=Var3, value=1)
        R1.pack()
        R2 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton2", variable=Var3, value=2)
        R2.pack()
        R3 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton3", variable=Var3, value=3)
        R3.pack()

        R4 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton1", variable=Var3, value=1)
        R4.pack()
        R5 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton2", variable=Var3, value=2)
        R5.pack()
        R6 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton3", variable=Var3, value=3)
        R6.pack()

        tv1 = ctk.CTkTreeview(frame1)
        column_list_account = ["Name", "Type", "Base Stat Total"]
        tv1['columns'] = column_list_account
        tv1["show"] = "headings"
        for column in column_list_account:
            tv1.heading(column, text=column)
            tv1.column(column, width=50)
        tv1.place(relheight=1, relwidth=0.995)
        treescroll = tk.Scrollbar(frame1)
        treescroll.configure(command=tv1.yview)
        tv1.configure(yscrollcommand=treescroll.set)
        treescroll.pack(side="right", fill="y")

        def Load_data():
            for row in pokemon_info:
                tv1.insert("", "end", values=row)

        def Refresh_data():
            tv1.delete(*tv1.get_children())  # *=splat operator
            Load_data()

        Load_data()


class PageOne(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page One")
        label1.pack(side="top")


class PageThree(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Three")
        label1.pack(side="top")


class PageFour(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Four")
        label1.pack(side="top")


class PageTwo(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Two")
        label1.pack(side="top")


class MenuBar(tk.Menu):
    def __init__(self, parent):
        tk.Menu.__init__(self, parent)

        menu_file = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu1", menu=menu_file)
        menu_file.add_command(label="All Widgets", command=lambda: parent.show_frame(Some_Widgets))
        menu_file.add_separator()
        menu_file.add_command(label="Exit Application", command=lambda: parent.Quit_application())

        menu_orders = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu2", menu=menu_orders)

        menu_pricing = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu3", menu=menu_pricing)
        menu_pricing.add_command(label="Page One", command=lambda: parent.show_frame(PageOne))

        menu_operations = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu4", menu=menu_operations)
        menu_operations.add_command(label="Page Two", command=lambda: parent.show_frame(PageTwo))
        menu_operations.add_separator()
        menu_operations.add_command(label="Page Three", command=lambda: parent.show_frame(PageThree))
        menu_operations.add_command(label="Page Four", command=lambda: parent.show_frame(PageFour))


if __name__ == "__main__":
    app = MyApp()
    app.mainloop()
"""


import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
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

        main_frame = ctk.CTkFrame(self, bg="#708090", height=431, width=626)
        main_frame.pack(fill="both", expand=True)

        frame_login = ctk.CTkFrame(main_frame, bg="blue", relief="groove", bd=2)
        frame_login.place(rely=0.30, relx=0.17, height=130, width=400)

        label_title = ctk.CTkLabel(frame_login, text="Login Page", font=("Trebuchet MS Bold", 16), background="blue")
        label_title.grid(row=0, column=1, columnspan=1)

        label_user = ctk.CTkLabel(frame_login, text="Username:", font=("Verdana", 14), background="blue", foreground="#E1FFFF")
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(frame_login, text="Password:", font=("Verdana", 14), background="blue", foreground="#E1FFFF")
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

        main_frame = ctk.CTkFrame(self, bg="#3F6BAA", height=150, width=250)
        main_frame.pack_propagate(0)
        main_frame.pack(fill="both", expand=True)

        text_styles = {"font": ("Verdana", 10), "background": "#3F6BAA", "foreground": "#E1FFFF"}

        label_user = ctk.CTkLabel(main_frame, text="New Username:", **text_styles)
        label_user.grid(row=1, column=0)

        label_pw = ctk.CTkLabel(main_frame, text="New Password:", **text_styles)
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

class MyApp(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        self.geometry("1024x600")
        self.title("Tkinter App Template")

        main_frame = ctk.CTkFrame(self, bg="#84CEEB", height=600, width=1024)
        main_frame.pack_propagate(0)
        main_frame.pack(fill="both", expand=True)
        main_frame.grid_rowconfigure(0, weight=1)
        main_frame.grid_columnconfigure(0, weight=1)
        self.frames = {}
        pages = (Some_Widgets, PageOne, PageTwo, PageThree, PageFour)
        for F in pages:
            frame = F(main_frame, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")
        self.show_frame(Some_Widgets)
        menubar = MenuBar(self)
        self.config(menu=menubar)

    def show_frame(self, name):
        frame = self.frames[name]
        frame.tkraise()

    def OpenNewWindow(self):
        OpenNewWindow()

    def Quit_application(self):
        self.destroy()

class GUI(ctk.CTkFrame):
    def __init__(self, parent):
        ctk.CTkFrame.__init__(self, parent)
        self.main_frame = ctk.CTkFrame(self, bg="#BEB2A7", height=600, width=1024)
        self.main_frame.pack_propagate(0)
        self.main_frame.pack(fill="both", expand=True)
        self.main_frame.grid_rowconfigure(0, weight=1)
        self.main_frame.grid_columnconfigure(0, weight=1)

class Some_Widgets(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)

        frame1 = ctk.CTkLabelFrame(self, text="This is a LabelFrame containing a Treeview")
        frame1.place(rely=0.05, relx=0.02, height=400, width=400)

        frame2 = ctk.CTkLabelFrame(self, text="Some widgets")
        frame2.place(rely=0.05, relx=0.45, height=500, width=500)

        button1 = ctk.CTkButton(frame2, text="tk button", command=lambda: Refresh_data())
        button1.pack()
        button2 = ctk.CTkButton(frame2, text="ttk button", command=lambda: Refresh_data())
        button2.pack()

        Var1 = tk.IntVar()
        Var2 = tk.IntVar()
        Cbutton1 = ctk.CTkCheckbutton(frame2, text="tk CheckButton1", variable=Var1, onvalue=1, offvalue=0)
        Cbutton1.pack()
        Cbutton2 = ctk.CTkCheckbutton(frame2, text="tk CheckButton2", variable=Var2, onvalue=1, offvalue=0)
        Cbutton2.pack()

        Cbutton3 = ctk.CTkCheckbutton(frame2, text="ttk CheckButton1", variable=Var1, onvalue=1, offvalue=0)
        Cbutton3.pack()
        Cbutton3 = ctk.CTkCheckbutton(frame2, text="ttk CheckButton2", variable=Var2, onvalue=1, offvalue=0)
        Cbutton3.pack()

        Lbox1 = tk.Listbox(frame2, selectmode="multiple")
        Lbox1.insert(1, "This is a tk ListBox")
        Lbox1.insert(2, "Github")
        Lbox1.insert(3, "Python")
        Lbox1.insert(3, "StackOverflow")
        Lbox1.pack(side="left")

        Var3 = tk.IntVar()
        R1 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton1", variable=Var3, value=1)
        R1.pack()
        R2 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton2", variable=Var3, value=2)
        R2.pack()
        R3 = ctk.CTkRadiobutton(frame2, text="tk Radiobutton3", variable=Var3, value=3)
        R3.pack()

        R4 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton1", variable=Var3, value=1)
        R4.pack()
        R5 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton2", variable=Var3, value=2)
        R5.pack()
        R6 = ctk.CTkRadiobutton(frame2, text="ttk Radiobutton3", variable=Var3, value=3)
        R6.pack()

        tv1 = ctk.CTkTreeview(frame1)
        column_list_account = ["Name", "Type", "Base Stat Total"]
        tv1['columns'] = column_list_account
        tv1["show"] = "headings"
        for column in column_list_account:
            tv1.heading(column, text=column)
            tv1.column(column, width=50)
        tv1.place(relheight=1, relwidth=0.995)
        treescroll = tk.Scrollbar(frame1)
        treescroll.configure(command=tv1.yview)
        tv1.configure(yscrollcommand=treescroll.set)
        treescroll.pack(side="right", fill="y")

        def Load_data():
            for row in pokemon_info:
                tv1.insert("", "end", values=row)

        def Refresh_data():
            tv1.delete(*tv1.get_children())  # *=splat operator
            Load_data()

        Load_data()

class PageOne(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)
        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page One")
        label1.pack(side="top")

class PageThree(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)
        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Three")
        label1.pack(side="top")

class PageFour(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)
        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Four")
        label1.pack(side="top")

class PageTwo(GUI):
    def __init__(self, parent, controller):
        GUI.__init__(self, parent)
        label1 = ctk.CTkLabel(self.main_frame, font=("Verdana", 20), text="Page Two")
        label1.pack(side="top")

class MenuBar(tk.Menu):
    def __init__(self, parent):
        tk.Menu.__init__(self, parent)

        menu_file = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu1", menu=menu_file)
        menu_file.add_command(label="All Widgets", command=lambda: parent.show_frame(Some_Widgets))
        menu_file.add_separator()
        menu_file.add_command(label="Exit Application", command=lambda: parent.Quit_application())

        menu_orders = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu2", menu=menu_orders)

        menu_pricing = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu3", menu=menu_pricing)
        menu_pricing.add_command(label="Page One", command=lambda: parent.show_frame(PageOne))

        menu_operations = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu4", menu=menu_operations)
        menu_operations.add_command(label="Page Two", command=lambda: parent.show_frame(PageTwo))
        menu_operations.add_separator()
        menu_operations.add_command(label="Page Three", command=lambda: parent.show_frame(PageThree))
        menu_operations.add_command(label="Page Four", command=lambda: parent.show_frame(PageFour))

        menu_help = tk.Menu(self, tearoff=0)
        self.add_cascade(label="Menu6", menu=menu_help)
        menu_help.add_command(label="Open New Window", command=lambda: parent.OpenNewWindow())

class OpenNewWindow(tk.Toplevel):
    def __init__(self, *args, **kwargs):
        tk.Toplevel.__init__(self, *args, **kwargs)
        self.title("Here is the Title of the Window")
        self.geometry("500x500")
        self.resizable(0, 0)

        main_frame = ctk.CTkFrame(self)
        main_frame.pack_propagate(0)
        main_frame.pack(fill="both", expand=True)

        frame1 = ctk.CTkLabelFrame(main_frame, text="This is a ttk LabelFrame")
        frame1.pack(expand=True, fill="both")

        label1 = ctk.CTkLabel(frame1, font=("Verdana", 20), text="OpenNewWindow Page")
        label1.pack(side="top")

root = MyApp()
top = LoginPage(root)
root.mainloop()
