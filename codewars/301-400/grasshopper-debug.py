def weather_info (temp):
    c = convertToCelsius(temp)
    if (c < 0):
        return (str(c) + ' is freezing temperature')
    else:
        return (str(c) + " is above freezing temperature")

def convertToCelsius (t):
    return (t - 32) * 5.0 / 9
