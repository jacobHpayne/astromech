import requests, json

objName = "moon"

url = requests.get("http://localhost:8090/api/objects/info?name="+objName+"&format=json")
text = url.text

dataJSON=json.loads(text)
print(dataJSON)

el = dataJSON["altitude"]
az = dataJSON["azimuth"]
print(az, el)
