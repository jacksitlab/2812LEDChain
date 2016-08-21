#!/usr/bin/env python
# -*- coding: utf-8 -*-

# enable debugging
from ws2812ledchain import *
import cgitb,cgi

cgitb.enable()
form=cgi.FieldStorage()
task=form.getvalue("task")

print "Content-Type: text/plain;charset=utf-8"
print

chain=WS2812Chain(1)
leds=chain.Add(0x44)
rcode=0
rmessage="nothing to do"

if task=="test":
    leds.Test2()
    rcode=1
    rmessage="testing successful"    
elif task=="offset":
    v=int(form.getvalue("value"))
    if v > -127 and v <= 127 and v <> 0 :
        leds.Offset(v)
        rcode=1
        rmessage="leds dimmed"
    else:
        rcode=0
        rmessage="invalid value"
else:
    rocde=0

print "{\"code\":%d,\"message\":\"%s\"}" % (rcode,rmessage)

