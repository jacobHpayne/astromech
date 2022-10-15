import requests, json


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
    print(dataJSON)

    el = dataJSON["altitude"]
    az = dataJSON["azimuth"]
    return [az, el]

def getRaDec(obj):
    url = requests.get("http://localhost:8090/api/objects/info?name="+obj+"&format=json")
    text = url.text

    dataJSON=json.loads(text)
    print(dataJSON)

    dec = dataJSON["dec"]
    ra = dataJSON["ra"]
    return [ra, dec]

print(getRaDec("M31"))
