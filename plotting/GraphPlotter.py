from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import csv

'''
    @author Sammy Tbeile
            st2918
'''




def prims(input_file= "input.csv"):
    vertexes = []

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        next(csv_reader,None)
        for row in csv_reader:
            x = dict(lat=float(row[0]), long=-1*float(row[1]), weight=row[2], name=row[3], neighbors=row[4].split(";"))
            vertexes.append(x)

    # background map
    m = Basemap(width=12000000,height=9000000,projection='merc',
            resolution='f',lat_1=45.,lat_2=55,lat_0=50,lon_0=-107)
    m.drawcoastlines()
    m.drawmapboundary(color='aqua')
    m.fillcontinents(color='coral', lake_color='aqua')
    m.drawstates()
    m.drawcountries()

    for i in range(0,(len(vertexes)-1)):

        xpt, ypt = m(vertexes[i].get("lat"), vertexes[i].get["long"])
        m.plot(xpt, ypt, "bo")
        plt.text(xpt + 1000, ypt + 1000)
        # while len(vertexes[0].get("neighbors")) != "":
        for neighbor in vertexes[i].get("neighbors"):
            neighbor_element = neighbor.split("_")
            for vertex in vertexes:
                if vertex.get("name") != neighbor_element[i]:
                    xptn, yptn = m(vertex.get("lat"), vertex.get("long"))
                    m.drawgreatcircle(xpt, ypt, xptn, yptn, linewidth=1, color="r")
                    plt.text((xpt+ypt)/2+1000, (xptn+yptn)/2+1000, neighbor_element[1])

    plt.show()


def general(input_file="input.csv"):
    # create arrays to hold
    lats = []
    longs = []
    weights = []
    names = []

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        #next(csv_reader, None)
        for row in csv_reader:
            #print (float(row[0]))
            
            x, y, w, n = float(row[0]),  -1*float(row[1]), float(row[2]), row[3]
            lats.append(x)
            longs.append(y)
            weights.append(w)
            names.append(n)

    # create background map
    m= Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64,
                               urcrnrlat=49, projection='lcc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='f', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(color='aqua')
    m.drawcounties()
    m.fillcontinents(color='coral', lake_color='aqua')
    m.drawstates()

    x1, y1 = m(lats[0], longs[0])
    m.plot(x1, y1, 'bo')
    plt.text(x1+1000, y1+1000, names[0])

    for i in range(1,(len(weights)-1)):
        xpt, ypt = m(lats[i], longs[i])
        m.plot(xpt, ypt, 'bo')
        plt.text(xpt+1000, ypt+1000, names[i])
        xptn, yptn = m(lats[i+1], longs[i+1])
        m.drawgreatcircle(xpt, ypt, xptn, yptn, linewidth=1, color="r")
        plt.text((xpt+ypt)/2+1000, (xptn+yptn)/2+1000, weights[i])

    plt.show()
    

decision = input('Are you using Prim\'s Algorithm? Enter y for yes, n for no: ')
inputFile = input("Where is your data stored? Please input the file name: ")
if decision == 'y':
    prims(inputFile)
else:
    general(inputFile)
