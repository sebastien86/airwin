# Fonctionne en reception pas d erreur MRL 1.0.1412
# attention reboot à chaque lancement sinon perd le fil des retour serie...
from org.myrobotlab.framework import MRLListener
from time import sleep

from org.myrobotlab.service import Runtime

serial = Runtime.createAndStart("serial","Serial")
serial.connect('COM10', 19200, 8, 1, 0)
sleep(1)

def serial1RX(data):
    num = data
    
    print "coucou"
    print chr(num)
    if (chr(num) == '1'):
        print "HELLO 1"
           
    if (num == 48):
       print "HELLO 0"

# fonctionne aussi. 
listener1 = MRLListener('publishRX', 'python', 'serial1RX')
serial.addListener(listener1)
# OK ci dessous fct
#serial.addListener("publishRX", python.name, "serial1RX")


print "10 clignotements de suite !"

# Clignotement de la LED de l'arduino pour test
for x in range(0,10):
	serial.write("LEDON\n") 
	sleep(1)
	serial.write("LEDOFF\n") 
	sleep(1) # delays for 5 seconds

######################################################################
 


