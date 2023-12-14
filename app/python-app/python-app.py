import tkinter as tk
from tkinter import PhotoImage
import requests
import json

url = "http://192.168.218.110/" # Clover node url

root = tk.Tk()
root.title("Clover monitor")

def update_display():
    try:
        response = requests.get(url)
        data = json.loads(response.text)

        moisture_status = data["plant_management"]["soil_moisture"]
        
        if moisture_status == "moist":
            icon_path = "assets/moist.png"
        elif moisture_status == "dry":
            icon_path = "assets/dry.png"
        elif moisture_status == "wet":
            icon_path = "assets/wet.png"

        icon = PhotoImage(file=icon_path)

        label.config(image=icon)
        label.image = icon

        root.after(2000, update_display)

    except Exception as e:
        print("Error:", e)
        root.after(2000, update_display)

label = tk.Label(root)
label.pack()

update_display()

root.mainloop()
