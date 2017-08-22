#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys
if(str(sys.version).find("2.7") != -1) : 
    import Tkinter as tk
else:
    import tkinter as tk

class FullScreenApp(object):
    def __init__(self, master, **kwargs):
        self.root = master
        # self.tk.attributes('-zoomed', True)  # This just maximizes it so we can see the window. It's nothing to do with fullscreen.
        self.frame = tk.Frame(self.root)
        self.frame.pack()
        self.state = False
        self.root.bind("<F11>", self.toggle_fullscreen)
        self.root.bind("<Control-Alt-x>", self.toggle_fullscreen)
        self.root.bind("<Alt-Tab>", self.toggle_fullscreen)
        self.root.bind("<Escape>", self.end_fullscreen)

    def toggle_fullscreen(self, event=None):
        self.state = not self.state  # Just toggling the boolean
        self.root.attributes("-fullscreen", self.state)
        return "break"

    def end_fullscreen(self, event=None):
        self.state = False
        self.root.attributes("-fullscreen", False)
        return "break"

root=tk.Tk()
app=FullScreenApp(root)
root.mainloop()