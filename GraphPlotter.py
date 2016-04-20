from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import csv


# create arrays to hold
lats = []
longs = []
weights = []

with open("input.csv") as input_csv:
    csv_reader = csv.reader(input_csv)
    next(csv_reader, None)
    for row in csv_reader:
        x, y, w = float(row[0]),  -1*float([row[2]]), float(row[1])
        lats.append(x)
        longs.append(y)
        weights.append(w)

# create background map
m = Basemap(llcrnrlon(-118), llcrnrlat(23.5), urcrnrlon(-60.85), urcrnrlat(48.85), lat_ts=20, resolution='c',
           projection='merc')

x1, y1 = m(longs, lats)

m.drawmapboundary
m.scatter(x1, y1, s=5, c="r", marker="o")

plt.show()