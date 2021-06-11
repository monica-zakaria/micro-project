import gmplot
from math import radians, cos, sin, asin, sqrt

lat = []
long =[]
E = []
N = []
latitude_list = []
longitude_list = []
# Reading from txt file 
# put the name of the txt file you are reading from
with open("New Text Document.txt", 'r') as f:
    putty = f.readlines()

s = putty[1]
while(1):
    n = s.find(',')
    sub = s[0:n]

    x = sub.find(" ")
    lat.append(sub[0:x])
    sub = sub[x+1:len(sub)]

    x = sub.find(" ")
    long.append(sub[0:x])
    sub = sub[x+1:len(sub)]


    x = sub.find(" ")
    N.append(sub[0:x])
    sub = sub[x+1:len(sub)]


    x = sub.find(" ")
    E.append(sub)
    s = s[n+1:len(s)]
    if(len(s)<=0):
        break

x= len(lat)
y = x/2
y = int(y)

for i in range(x):
    value = float(lat[i])  
    decimal_value = value/100
    degrees  = int(decimal_value)
    temp   = (decimal_value - int(decimal_value))/0.6
    position = float(degrees) + temp
    lat[i] = position 
    if(N[i] == "S"):
        position= position*-1

for i in range(x):
    value = float(long[i])  
    decimal_value = value/100
    degrees = int(decimal_value)
    temp  = (decimal_value - int(decimal_value))/0.6
    position = float(degrees) + temp
    long[i] = position 
    if(E[i] == "W"):
        position= position*-1
     
#making an array of the longtiude & latitude

for i in range(x):
    latitude_list.append(float(lat[i]))
    longitude_list.append(float(long[i]))

distance = 0
r = 6371

for i in range(x-1):
    lat1 = radians(lat[i])
    lat2 = radians(lat[i+1])
    long1 = radians(long[i])
    long2 = radians(long[i+1])
    dlon = long2 - long1
    dlat = lat2 - lat1
    a = sin(dlat / 2)**2 + cos(lat1) * cos(lat2) * sin(dlon / 2)**2
    c = 2 * asin(sqrt(a))
    distance = distance + c*r

distance = distance * 1000
print(distance)
#Drawing the map
gmap3 = gmplot.GoogleMapPlotter(lat[y+1],long[y+1], 20)
gmap3.scatter(latitude_list, longitude_list,size = 0.5, marker = False)
gmap3.plot(latitude_list, longitude_list,'cornflowerblue', edge_width = 3)
# put the directory you are reading the txt file from followed by the name of the map
gmap3.draw( "F:\\College\\Computer\\2nd term\\Microprocessor\\project\\maps\\map15.html" )

