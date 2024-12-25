# MusicXmltoTarget

This is a tool for [GPS-GuitarPlaySimulation](https://github.com/MRXuanL/GPS-GuitarPlaySimulation) to convert MusicXml files to the model's target format.

**This tool is only applicable to sheet music without repeat signs. If the sheet music contains repeat signs, please convert it into a version without repeats before processing. Additionally, the tool will ignore any technical markings in the sheet music (such as strumming, plucking, or hammering) and will focus solely on the notes, converting them into a class that includes fret position, string number, start time, and duration for output.**

## Usage

It is easy to use!
Download this code to your computer with Linux OS.

Copy your new song MusicXml file to the songxml folder.

Run the command:
```sh
cd MusicXmltoTarget
output/main.exe
```

A new out.txt file will be generated! Copy it to the GPS-GuitarPlaySimulation project for training.


