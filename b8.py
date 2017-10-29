import xml.etree.ElementTree as ET

tree = ET.parse("parsing_table.xml")
root = tree.getroot()

term = []
non_term = []

lsprod = []
rsprod = []
n=0

for child in root:
	if child.tag == "states":
		n = int(child.text)
	elif child.tag == "term":
		term.append(child.text)
	elif child.tag == "nterm":
		non_term.append(child.text)
	elif child.tag == "productions":
		for ch in child:
			lsprod.append(ch[0].text)
			rsprod.append(ch[1].text)
	elif child.tag == "actiontable":
		action = [[] for x in range(n)]
		i=0
		for ch in child:
			for c in ch:
				action[i].append(c.text)
			i+=1
	elif child.tag=="gototable":
		goto = [[] for x in range(n)]
		i=0
		for ch in child:
			for c in ch:
				goto[i].append(c.text)
			i+=1

nterms = len(term)
nnterm = len(non_term)
nprod = len(lsprod)
	
print "Terminals"
print term

print "Non terminals"
print non_term

print "Productions"
for i in xrange(nprod):
	print lsprod[i]," -> ",rsprod[i]

print "Action table"
for i in action:	
	print i

print "Goto table"
for i in goto:
	print i


while 1:
	istr = raw_input("Enter string")
	iptr = 0
	stack = ['$',0]
	while 1:
		print "Stack:"
		print stack
		stop = stack[-1]
		isym = istr[iptr]
		isindex = term.index(isym)
		ac = action[stop][isindex]
		print "Action for stop",stop,"and index",isindex,"is",ac

		if ac == "Error":
			print "Syntax error"
			break
		elif ac == "Accept":
			print "Correct String"
			break
		elif "s" in ac:
			stack.append(isym)
			ns = ac.replace("s","")
			stack.append(int(ns))
			iptr+=1
		elif "r" in ac:
			rrule = int(ac.replace("r",""))
			print "Using reduce rule", lsprod[rrule-1], "->",rsprod[rrule-1]
			for i in xrange(2*len(rsprod[rrule-1])):
				stack.pop()
			print stack
			stack.append(lsprod[rrule-1])
			pstate = stack[-2]
			ntindex = non_term.index(lsprod[rrule-1])
			nstate = goto[pstate][ntindex]
			stack.append(int(nstate))
			print stack
