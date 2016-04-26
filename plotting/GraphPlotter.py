from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import csv

'''
    @author Sammy Tbeile
            st2918
'''




def prims(input_file= "input.csv"):
    lats = []
    longs = []
    weights = []
    names = []
    neighbors = []

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        next(csv_reader,None)
        for row in csv_reader:
            x,y,w,n,ne = float(row[0]), float(row[1]), float(row[2]), row[3], row[4]
            lats.append(x)
            longs.append(y)
            weights.append(w)
            names.append(n)
            neighbors.append(ne)

    # background map
    m= Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64,
                               urcrnrlat=49, projection='lcc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    m.drawcountries()

    xpt, ypt = m(longs, lats)
    m.plot(xpt, ypt, 'bo', markersize=10)
    for x, y, name in zip(xpt,ypt,names):
        plt.text(x+1000,y+1000,name)    
        
    for i in range(0,(len(neighbors)-1)):
        neighbors_list = neighbors[i].split("_");
        inner_lats = []
        inner_longs = []
        inner_weight = []
        for neighbor in neighbors_list:
            value_list = neighbor.split(";")
            inner_lats.append(float(value_list[0]))
            inner_longs.append(float(value_list[1]))
            inner_weight.append(float(value_list[2]))
        
        for j in range(0,len(inner_lats)-1):
            m.drawgreatcircle(longs[i],lats[i],inner_longs[j],inner_lats[j], linewidth=1,color="r")


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
            
            x, y, w, n = float(row[0]),  float(row[1]), float(row[2]), row[3]
            lats.append(x)
            longs.append(y)
            weights.append(w)
            names.append(n)


    # create background map
    m= Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64,
                               urcrnrlat=49, projection='lcc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.drawcounties()
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    xpt, ypt = m(longs, lats)
    m.plot(xpt, ypt, 'bo', markersize=10)
    for x, y, name in zip(xpt,ypt,names):
        plt.text(x+1000,y+1000,name)

    for i in range(0,len(xpt)-1):
        m.drawgreatcircle(longs[i], lats[i], longs[i+1], lats[i+1], linewidth=1, color='r')
    
    plt.show()
    

decision = input('Are you using Prim\'s Algorithm? Enter y for yes, n for no: ')
inputFile = input("Where is your data stored? Please input the file name: ")
if decision == 'y':
    prims(inputFile)
else:
    general(inputFile)
