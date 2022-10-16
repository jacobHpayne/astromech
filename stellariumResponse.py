import requests, json
import serial
import time

#arduino = serial.Serial(port='COM3', baudrate=9600, timeout=3)

# def write_read(x):
#     arduino.write(bytes(x,"UTF-8"))
#     time.sleep(0.05)
#     data = arduino.readline()
#     return data

# while True:
#     num = input("Enter a number: ")
#     value = write_read(num)
#     print(value)

def getObjName():
    url = requests.get("google address")
    text = url.text
    dataJSON=json.loads(text)
    objName = dataJSON["object"]
    return objName

def getAzEl(obj):
    url = requests.get("http://localhost:8090/api/objects/info?name="+obj+"&format=json")
    text = url.text

    dataJSON=json.loads(text)
    #print(dataJSON)

    el = dataJSON["altitude"]
    az = dataJSON["azimuth"]
    return [az, el]

def getHaDec(obj):
    url = requests.get("http://localhost:8090/api/objects/info?name="+obj+"&format=json")
    text = url.text

    dataJSON=json.loads(text)
    #print(dataJSON)

    dec = dataJSON["dec"]
    ha = dataJSON["hourAngle-dd"]
    return [ha, dec]

def haDecString(ha,dec):
    return "{:.4f}".format(ha) + ", " + "{:.4f}".format(dec)

#arduino.write(str('20.5\n').encode('UTF-8'))
#time.sleep(0.05)
#print(arduino.readline())
again = True
while again:
    targetName = input("Please enter a target name: ")
    if targetName != "Exit":
        targetHa, targetDec = getHaDec(targetName)
        targetString = haDecString(targetHa, targetDec)
        print("Coords are: ", targetString)
    else:
        print("Exiting...")
        again = False
    #write_read(targetString)

