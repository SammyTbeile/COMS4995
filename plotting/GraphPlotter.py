from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import csv

'''
    @author Sammy Tbeile
            st2918
'''


def tarjans(input_file= "input.csv"):
    lats = []
    longs = []
    names = []
    colors = ['bo','ro','co','mo','yo','ko','wo']
    used_colors = []
    counter = 0

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        for row in csv_reader:
            x,y,n = float(row[0]), float(row[1]), row[2]
            lats.append(x)
            longs.append(y)
            names.append(n)
    
    m= Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64,
                               urcrnrlat=49, projection='lcc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    m.drawcountries()
    
    ypt, xpt = m(longs, lats)
    for i in range(0,len(xpt)):
        if counter > len(xpt):
            counter = 0
        used_colors.append(colors[counter])
        counter = counter +1
    for y,x,c in zip(ypt,xpt,used_colors):
        m.plot(y,x, c, markersize=10)
    for y,x,name in zip(ypt,xpt,names):
        plt.text(y+1000,x+1000,name)
    

def prims(input_file= "input.csv"):
    lats = []
    longs = []
    weights = []
    names = []
    neighbors = []

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
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

    ypt, xpt = m(longs, lats)
    m.plot(ypt, xpt, 'bo', markersize=10)
    for y, x, name in zip(ypt,xpt,names):
        plt.text(y+1000,x+1000,name)    
        
    for i in range(0,(len(neighbors)-1)):
        neighbors_list = neighbors[i].split("_");
        inner_lats = []
        inner_longs = []
        inner_weight = []
        for neighbor in neighbors_list:
            if(neighbor==''):
                continue
            value_list = neighbor.split(";")
            lat = float(value_list[0])
            long = float(value_list[1])
            w = float(value_list[2])
            inner_lats.append(lat)
            inner_longs.append(long)
            inner_weight.append(w)
        inner_y, inner_x = m(inner_longs,inner_lats)
        for j in range(0,len(inner_lats)):
            m.drawgreatcircle(longs[i],lats[i],inner_longs[j],inner_lats[j], linewidth=1,color="r")
            plt.text((ypt[i]+inner_y[j])/2,(xpt[i]+inner_x[j])/2,inner_weight[j])


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
            
            x, y, w, n = float(row[0]),  float(row[1]), row[2], row[3]
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
    ypt, xpt = m(longs, lats)
    m.plot(ypt, xpt, 'bo', markersize=10)
    for y, x, name in zip(ypt,xpt,names):
        plt.text(y+1000,x+1000,name)

    for i in range(0,len(ypt)-1):
        m.drawgreatcircle(longs[i], lats[i], longs[i+1], lats[i+1], linewidth=1, color='r')
    
    for i in range(0,len(weights)-1):
        plt.text(((ypt[i]+ypt[i+1])/2),((xpt[i]+xpt[i+1])/2),weights[i+1])
    
    plt.show()
    
print("Menu: ")
print("1. Shortest Path Algorithm ")
print("2. Prim's Algorithm")
print("3. Tarjan's Algorithm")
decision = int(input('Please input the number of your option: '))
inputFile = input("Where is your data stored? Please input the file name: ")
if decision == 1:
    general(inputFile)
elif decision == 2:
    prims(inputFile)
elif decision == 3:
    tarjans(inputFile)

