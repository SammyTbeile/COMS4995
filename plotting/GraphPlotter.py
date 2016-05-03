from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import csv

'''
    @author Sammy Tbeile
            st2918
'''


def johnsons(input_file="input.csv"):
    lats = []
    longs = []
    weights = []
    names = []
    path = []
    paths = []
    minLat = 90;
    minLong = 180;
    maxLat = -90
    maxLong =-180

    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        for row in csv_reader:
            if row[0] != "done":    
                x, y, w, n = float(row[0]),  float(row[1]), row[2], row[3]

                lats.append(x)
                longs.append(y)
                weights.append(w)
                names.append(n)
                if x<minLat:
                    minLat=x
                if y<minLong:
                    minLong = y
                if x>maxLat:
                    maxLat = x
                if y>maxLong:
                    maxLong = y
            else:
                path.append(lats)
                path.append(longs)
                path.append(weights)
                path.append(names)
                paths.append(path)
                lats = []
                longs = []
                weights = []
                names = []
                path = []


    # create background map 
    if minLat -10 >-90:
        minLat = minLat-10
    if maxLat +10 <90:
        maxLat = maxLat +10
    if minLong -10 >-180:
        minLong = minLong-10
    if maxLong +10<180:
        maxLong = maxLong+10
    m= Basemap(llcrnrlon=minLong, llcrnrlat=minLat, urcrnrlon=maxLong,
                               urcrnrlat=maxLat, projection='merc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.drawcountries()
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    
    for p in paths:
        in_lats= p[0];
        in_longs =p[1];
        in_names = p[3];
        in_weight = p[2];
        ypt, xpt = m(in_longs, in_lats)
        m.plot(ypt, xpt, 'bo', markersize=10)
        for y, x, name in zip(ypt,xpt,in_names):
            plt.text(y-1000,x+1000,name)
    
        for i in range(0,len(in_lats)-1):
            m.drawgreatcircle(in_longs[i], in_lats[i], in_longs[i+1], in_lats[i+1], linewidth=1, color='r')
        
        for i in range(0,len(in_weight)-1):
            plt.text(((ypt[i]+ypt[i+1])/2),((xpt[i]+xpt[i+1])/2),in_weight[i+1])
    plt.show()
        
        
        
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
    minLat=min(lats)
    maxLat=max(lats)
    minLong = min(longs)
    maxLong = max(longs)    
    if minLat -10 >-90:
        minLat = minLat-10
    if maxLat +10 <90:
        maxLat = maxLat +10
    if minLong -10 >-180:
        minLong = minLong-10
    if maxLong +10<180:
        maxLong = maxLong+10
    m= Basemap(llcrnrlon=minLong, llcrnrlat=minLat, urcrnrlon=maxLong,
                               urcrnrlat=maxLat, projection='merc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    '''
    m= Basemap(llcrnrlon=-119, llcrnrlat=22, urcrnrlon=-64,
                               urcrnrlat=49, projection='lcc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    '''
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    m.drawcountries()
    
    ypt, xpt = m(longs, lats)
    for i in range(0,len(xpt)):
        if counter > len(colors) - 1:
            counter = 0
        used_colors.append(colors[counter])
        counter = counter +1
    for y,x,c in zip(ypt,xpt,used_colors):
        m.plot(y,x, c, markersize=10)
    for y,x,name in zip(ypt,xpt,names):
        plt.text(y+1000,x+1000,name)
    plt.show()
    

def prims(input_file= "input.csv"):
    lats = []
    longs = []
    weights = []
    names = []
    neighbors = []


    with open(input_file) as input_csv:
        csv_reader = csv.reader(input_csv)
        for row in csv_reader:
            x,y,w,n,ne = float(row[0]), float(row[1]), row[2], row[3], row[4]        
            lats.append(x)
            longs.append(y)
            weights.append(w)
            names.append(n)
            neighbors.append(ne)
    
  

    # background map
    minLat=min(lats)
    maxLat=max(lats)
    minLong = min(longs)
    maxLong = max(longs)    
    if minLat -10 >-90:
        minLat = minLat-10
    if maxLat +10 <90:
        maxLat = maxLat +10
    if minLong -10 >-180:
        minLong = minLong-10
    if maxLong +10<180:
        maxLong = maxLong+10
    m= Basemap(llcrnrlon=minLong, llcrnrlat=minLat, urcrnrlon=maxLong,
                               urcrnrlat=maxLat, projection='merc', lat_1=33, lat_2=45,
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
        
    for i in range(0,(len(longs))):
        neighbors_list = neighbors[i].split("_");
        inner_lats = []
        inner_longs = []
        inner_weight = []
        for neighbor in neighbors_list:
            if(neighbor==''):
                continue
            value_list = neighbor.split(";")            
            if(len(value_list)>=2):                
                if(value_list[0] != " " and value_list[1] != " "):
                    lat = float(value_list[0])
                    lng = float(value_list[1])
                    w = float(value_list[2])
                    inner_lats.append(lat)
                    inner_longs.append(lng)
                    inner_weight.append(w)
        if(inner_longs!= []):
            in_ypt, in_xpt = m(inner_longs, inner_lats)
            m.plot(in_ypt, in_xpt, 'bo', markersize=10)
            inner_y, inner_x = m(inner_longs,inner_lats)
            for j in range(0,len(inner_longs) - 1):
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
    minLat=min(lats)
    maxLat=max(lats)
    minLong = min(longs)
    maxLong = max(longs)    
    if minLat -10 >-90:
        minLat = minLat-10
    if maxLat +10 <90:
        maxLat = maxLat +10
    if minLong -10 >-180:
        minLong = minLong-10
    if maxLong +10<180:
        maxLong = maxLong+10
    m= Basemap(llcrnrlon=minLong, llcrnrlat=minLat, urcrnrlon=maxLong,
                               urcrnrlat=maxLat, projection='merc', lat_1=33, lat_2=45,
                               lon_0=-95, resolution='c', area_thresh=10000)
    m.drawcoastlines()
    m.drawmapboundary(fill_color='aqua')
    m.drawcountries()
    m.fillcontinents(color='green', lake_color='aqua')
    m.drawstates()
    ypt, xpt = m(longs, lats)
    m.plot(ypt, xpt, 'bo', markersize=10)
    for y, x, name in zip(ypt,xpt,names):
        plt.text(y-1000,x+1000,name)

    for i in range(0,len(ypt)-1):
        m.drawgreatcircle(longs[i], lats[i], longs[i+1], lats[i+1], linewidth=1, color='r')
    
    for i in range(0,len(weights)-1):
        plt.text(((ypt[i]+ypt[i+1])/2),((xpt[i]+xpt[i+1])/2),weights[i+1])
    
    plt.show()
    
print("Menu: ")
print("1. Shortest Path Algorithm")
print("2. Prim's Algorithm")
print("3. Tarjan's Algorithm")
print("4. Johnson's Algorithm")
decision = int(input('Please input the number of your option: '))
inputFile = input("Where is your data stored? Please input the file name: ")
if decision == 1:
    general(inputFile)
elif decision == 2:
    prims(inputFile)
elif decision == 3:
    tarjans(inputFile)
elif decision ==4:
    johnsons(inputFile)
else:
    print("Please select a valid option")
