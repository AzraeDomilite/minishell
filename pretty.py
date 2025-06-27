# # Class to handle the actual printing
# class SplitPrinter():

# 	def __init__(self, val):
# 		self.val = val

# 	def to_string(self):
# 		i = self.val
# 		while (i.dereference() != 0):
# 			print (i.dereference())
# 			i = i + 1

# class VectorPrinter():

# 	def __init__(self, val):
# 		self.val = val

# 	def to_string(self):
# 		v = self.val
# 		vals = []
# 		p  = v["values"]
# 		#return(str(p.dereference()))
# 		for i in range(0, v["size"]):
# 			vals.append(float(p.dereference()))
# 			p = p + 1
# 			i = i + 1
# 		#return "".join(["{:>3.2f}"]*len(vals))
# 		return "".join(["{:>8.2f}"]*len(vals)).format(*vals)

# class EdgePrinter():

# 	def __init__(self, val):
# 		self.val = val

# 	def to_string(self):
# 		v = self.val
# 		start = []
# 		end = []
# 		pstart  = v["start"]
# 		pend = v["end"]
# 		ppstart = pstart["values"]
# 		ppend = pend["values"]
# 		#return(str(p.dereference()))
# 		for i in range(0, pstart["size"]):
# 			start.append(float(ppstart.dereference()))
# 			end.append(float(ppend.dereference()))
# 			ppstart = ppstart + 1
# 			ppend = ppend + 1
# 			i = i + 1
# 		#return "".join(["{:>3.2f}"]*len(vals))
# 		return "".join(["{:>8.2f}"]*len(start)).format(*start) + "     -> " + "".join(["{:>8.2f}"]*len(end)).format(*end)

# class MapPrinter():

# 	def __init__(self, val):
# 		self.val = val

# 	def to_string(self):
# 		map = self.val
# 		out = []
# 		out.append("width: " + str(map["width"]) + ", height: " + str(map["height"]))
# 		line = ""
# 		pos = map["z"]
# 		print(pos)
# 		if map["width"] == -1 and map["height"] == -1:
# 			pass
# 		elif map["height"] == -1:
# 			for i in range(0,map["width"]):
# 				line += str(map["z"][i]) + "\t"
# 			out.append(line)
# 		else:
# 			for i in range(0,map["width"] * map["height"]):
# 				line += str(pos.dereference()) + "\t"
# 				pos += 1
# 			out.append(line)

# 		return "\n".join(out)

import gdb

# to use it, cast the list to (t_elist *) before printing
class CharListPrinter():

	def __init__(self, val):
		self.val = val

	def to_string(self):
		v = self.val
		start = []
		end = []
		while (v != 0):
			content = v["token"]#.cast(gdb.lookup_type("char *").pointer)
			print (content, ", ")
			v = v["next"]
		#print(v.dereference())

def register_printers(val):

	if str(val.type)=="t_tokens *":
		return CharListPrinter(val)
	if str(val.type)=="struct s_tokens *":
		return CharListPrinter(val)

#remove older versions of the Printer
for printer in gdb.pretty_printers:
	gdb.pretty_printers = [item for item in gdb.pretty_printers \
						if not ( type(item).__name__ == "function" and item.__name__ == "register_printers" )]

# add new Printer to pretty printers
gdb.pretty_printers.append(register_printers)