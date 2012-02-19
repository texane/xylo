#!/usr/bin/env python

# http://www.siteduzero.com/forum-83-350633-p1-delire-de-geek-faites-chanter-votre-pc.html

s = ''
i = 0

f = open('fu', 'r')

while (True):
    l = f.readline()
    if l == None or len(l) == 0:
        break
    l = l.strip()
    if len(l) == 0:
        continue
    if l[0] != '_':
        n = l.split()[0]
        if n[-1] == '_':
            n += 'MINOR'
    else:
        n = 'SILENCE'
    s += n + ','
    if (i and ((i % 8) == 0)):
        s += '\n'
    i = i + 1

print(s)

f.close()
