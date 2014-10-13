# -*- coding: utf-8 -*-
"""
@Author JunruShao(yz_sjr@163.com)
"""

import os

def checkExist(f):
	f = os.path.splitext(f)[0]
	return os.path.exists(f + ".cpp") or os.path.exists(f + ".java") or os.path.exists(f + ".py") or os.path.exists(f + ".sh")

def processFile(f):
	if os.path.isfile(f) and not f.startswith("."):
		if f.endswith((".cpp", ".java", ".sh", ".py")):
			print("File " + f)
			toWrite = "\\begin{lstlisting}"
			toWrite += "\n"
			with open(f, "r") as infile:
				for line in infile.readlines():
					line = line.replace("	", "  ")
					toWrite += line
			toWrite += "\n"
			toWrite += "\\end{lstlisting}"
			with open(os.path.splitext(f)[0] + ".tex", "w") as outfile:
				outfile.write(toWrite)

		if f.endswith((".tex")) and not checkExist(f):
			print("File " + f)
			toWrite = ""
			with open(f, "r") as infile:
				for line in infile.readlines():
					line = line.replace("	", "  ")
					line = line.replace("。", ". ")
					line = line.replace("，", ", ")
					line = line.replace("（", "( ")
					line = line.replace("）", ") ")
					line = line.replace("！", "! ")
					line = line.replace("？", "? ")
					toWrite += line
			with open(f, "w") as outfile:
				outfile.write(toWrite)

def walkFolder(depth):
	for f in os.listdir(os.getcwd()):
		if os.path.isdir(f):
			if not f.startswith("."):
				print("Enter " + f)
				os.chdir(f)
				walkFolder(depth + 1)
				os.chdir("..")
				print("Exit")
		else:
	#		if not (depth == 0 and (f == "convert.py" or f == "main.tex")):
			if not (depth == 0 and (f == "convert.py" or f == "convert2.7.py")):
				processFile(f)

def main():
	walkFolder(0)

if __name__ == "__main__":
	main()
