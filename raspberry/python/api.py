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
resp=type('lamdbaobject', (object,), {})()
resp.code=0
resp.message="nothing to do"

if task=="test":
    leds.Test2()
    resp.code=1
    resp.message="testing successful"    
elif task=="offset":
    v=int(form.getvalue("value"))
    if v > -127 and v <= 127 and v <> 0 :
        leds.Offset(v)
        resp.code=1
        resp.message="leds dimmed"
    else:
        resp.code=0
        resp.message="invalid value"
elif task=="fadein":
    v=int(form.getvalue("value"))
    if v>0 and v<65535:
        leds.FadeIn(v)
        resp.code=1
        resp.message="fading in"
elif task=="fadeout":
    v=int(form.getvalue("value"))
    if v>0 and v<65535:
        leds.FadeOut(v)
        resp.code=1
        resp.message="fading out"   

else:
    resp.ocde=0

print "{\"code\":%d,\"message\":\"%s\"}" % (resp.code,resp.message)

