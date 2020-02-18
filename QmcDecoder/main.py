#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

'''
Name   : QmcDecoder/main.py
Author : Modnar
Date   : 2020/02/18
Copyrights (c) 2020 Modnar. All rights reserved.
'''

import os, tkinter
from tkinter import filedialog, ttk, messagebox

if not os.path.exists('cache/'):
    os.makedirs('cache/')

IS_RUNNING = False
SUFFIXS = {'qmc0', 'qmcogg', 'qmcflac'}

class QmcDecoder:
    def __init__(self, titleName):
        self.root = tkinter.Tk()
        self.root.title(titleName)
        self.add_widgets()
        self.root.resizable(False, False)
        self.root.mainloop()

    def add_widgets(self):
        inputFrame = ttk.Frame(self.root)
        outputFrame = ttk.Frame(self.root)
        loggingFrame = ttk.Frame(self.root)
        inputFrame.grid(padx=5, pady=5, row=0, column=0, sticky='we')
        outputFrame.grid(padx=5, pady=5, row=1, column=0, sticky='we')
        loggingFrame.grid(padx=5, pady=5, row=0, column=1, rowspan=2)

        self.tableView = ttk.Treeview(inputFrame, show='headings', columns=('col',))
        self.tableView.column('col', width=300, anchor='center')
        self.tableView.heading('col', text='输入文件路径')
        self.tableView.grid(padx=3, pady=3, row=0, column=0, sticky='nwe')
        chooseInputButton = ttk.Button(inputFrame, text='选择文件', \
                command=self.chooseFiles)
        chooseInputButton.grid(padx=3, pady=3, row=1, column=0, sticky='n')

        self.entryText = tkinter.StringVar()
        self.entryText.set('输入/选择输出文件夹')
        self.getOutputEntry = ttk.Entry(outputFrame, textvariable=self.entryText, \
                width=30)
        self.getOutputEntry.grid(padx=5, pady=5, row=0, column=0, sticky='n')
        chooseOutputButton = ttk.Button(outputFrame, text='浏览目录', \
                command=self.chooseDir)
        chooseOutputButton.grid(padx=5, pady=5, row=1, column=0, sticky='n')

        self.textPanel = tkinter.Text(loggingFrame, width=30, height=20)
        self.textPanel.grid(padx=5, pady=5, row=0, column=0, sticky='n')
        self.textPanel.config(state=tkinter.DISABLED)
        runButton = ttk.Button(loggingFrame, text='RUN !', command=self.decode)
        runButton.grid(padx=5, pady=5, row=1, column=0, sticky='n')


    def chooseFiles(self):
        self.filenames = filedialog.askopenfilenames()
        passCheck = True
        for filename in self.filenames:
            if self.checkFileFailed(filename.split('/')[-1]): 
                passCheck = False
                break
        if passCheck:
            self.__updateFilenames()


    def __updateFilenames(self):
        for _ in map(self.tableView.delete, self.tableView.get_children('')):
            pass
        for i in range(len(self.filenames)):
            print(self.filenames[i])
            self.tableView.insert('', i, values=(self.filenames[i].split('/')[-1],))


    def chooseDir(self):
        self.entryText.set(filedialog.askdirectory())


    def decode(self):
        global IS_RUNNING
        if IS_RUNNING:
            messagebox.showinfo(title='INFORMATION', message='程序执行中，请稍候。')
        elif self.getOutputEntry.get() == '':
            messagebox.showwarning(title='WARNING', message='请指定结果文件存储目录!')
        elif len(self.filenames) == 0:
            messagebox.showwarning(title='WARNING', message='请选择要处理的文件!')
        else:
            IS_RUNNING = True
            with open('cache/cache.txt', 'w', encoding='utf-8') as writeFile:
                for file_path in self.filenames:
                    writeFile.write(file_path+'\n')
                writeFile.write('\n')
                writeFile.write(self.getOutputEntry.get())
            os.system('./QmcDecoder cache/cache.txt')
            self.updateLogging()
            IS_RUNNING = False


    def checkFileFailed(self, filename):
        if filename.split('.')[-1] not in SUFFIXS:
            messagebox.showwarning(title='WARNING', \
                    message='Failed: %s\n请确保输入的是QMC加密文件!' % filename)
            return True
        return False


    def updateLogging(self):
        self.textPanel.config(state=tkinter.NORMAL)
        self.textPanel.delete('1.0', 'end')
        with open('cache/cache.log', 'r') as readFile:
            self.textPanel.insert(tkinter.INSERT, readFile.read())
        self.textPanel.see(tkinter.END)
        self.textPanel.config(state=tkinter.DISABLED)

def main():
    QmcDecoder('QmcDecoder v1.0')

if __name__ == '__main__':
    main()
