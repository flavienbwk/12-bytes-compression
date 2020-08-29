dataTypeBytes = {
    "Pression": {
        "bits": 12,
        "function": lambda x: (x + 8700) / 10,
        "unit": "hP"
    },
    "Turbidity": {
        "bits": 11,
        "function": lambda x: (round(x * (10 / 2)) / 10) * 5 / 1023,
        "unit": "V"
    },
    "Temperature": {
        "bits": 10,
        "function": lambda x: x / 10,
        "unit": "°C"
    },
    "GPS_lat": {
        "bits": 20,
        "function": lambda x: round(x * (10 / 4)) / 10000,
        "unit": "°"
    },
    "GPS_long": {
        "bits": 19,
        "function": lambda x: round(x * (10 / 4)) / 10000,
        "unit": "°"
    },
    "GPS_long_sign": {
        "bits": 1,
        "function": lambda x: x,
        "unit": ""
    },
    "GPS_lat_sign": {
        "bits": 1,
        "function": lambda x: x,
        "unit": ""
    },
    "pH": {
        "bits": 7,
        "function": lambda x: x / 10,
        "unit": ""
    },
    "In Water": {
        "bits": 1,
        "function": lambda x: x,
        "unit": ""
    },
    "ORP / RedOx": {
        "bits": 10,
        "function": lambda x: round(x * (10 / 2)) - 2000,
        "unit": ""
    },
    "Antenna Battery": {
        "bits": 2,
        "function": lambda x: x * 25,
        "unit": "%"
    },
    "Floater Battery": {
        "bits": 2,
        "function": lambda x: x * 25,
        "unit": "%"
    },
}

def decompress(data):
    result = {}
    binary = "{0:096b}".format(int(data, 16))
    actualBit = 0
    for dataType, item in dataTypeBytes.items():
        print(dataType + " has " + str(item["bits"]) + " bit(s) and begin at bit " + str(actualBit))
        binaryValue = binary[actualBit:actualBit + item["bits"]]
        print("Binary value : " + binaryValue)
        decimalValue = int(binaryValue, 2)
        print("Decimal value : " + str(decimalValue))
        value = item["function"](decimalValue)
        print("Value : " + str(value) + item["unit"])
        print()
        actualBit += item["bits"]
        result[dataType] = value
    return result