import folium
import openrouteservice as ors
import math
import mysql.connector

# Establish MySQL connection
conn = mysql.connector.connect(
    host="localhost",
    user="root",
    password="",
    database="garbagemsdb"
)
cursor = conn.cursor()

# Fetch latitude and longitude from the tblbin table
cursor.execute("SELECT longitude, latitude FROM tblbin WHERE distance > 100")
coords = cursor.fetchall()

# Close MySQL connection
cursor.close()
conn.close()

# Convert Decimal values to float
coords = [(float(longitude), float(latitude)) for longitude, latitude in coords]

# Define coordinates and vehicle start location
vehicle_start = coords[0]

# Initialize the map
m = folium.Map(location=list(reversed(vehicle_start)), tiles="cartodbpositron", zoom_start=14)

# Add markers for coordinates and vehicle start location
for coord in coords:
    folium.Marker(location=list(reversed(coord))).add_to(m)

folium.Marker(location=list(reversed(vehicle_start)), icon=folium.Icon(color="red")).add_to(m)

# Initialize OpenRouteService client
client = ors.Client(key='5b3ce3597851110001cf62487bdd2299f7b04c53844a4bd72fbb64b5')

# Define vehicles and jobs for optimization
vehicles = [
    ors.optimization.Vehicle(id=0, profile='driving-car', start=vehicle_start, end=vehicle_start, capacity=[5]),
    ors.optimization.Vehicle(id=1, profile='driving-car', start=vehicle_start, end=vehicle_start, capacity=[5])
]
jobs = [ors.optimization.Job(id=index, location=coord, amount=[1]) for index, coord in enumerate(coords)]

# Perform optimization
optimized = client.optimization(jobs=jobs, vehicles=vehicles, geometry=True)

# Add routes and arrival time markers to the map
line_colors = ['green', 'orange', 'blue', 'yellow']
for route in optimized['routes']:
    folium.PolyLine(locations=[list(reversed(coord)) for coord in ors.convert.decode_polyline(route['geometry'])['coordinates']], color=line_colors[route['vehicle']]).add_to(m)
    for step in route['steps']:
        if step['type'] == 'job':
            folium.Marker(location=list(reversed(step['location'])), popup=f"Arrival time: {math.floor(step['arrival'] / (60*60))} hours {math.floor((step['arrival'] % (60*60)) / 60)} minutes", icon=folium.Icon(color=line_colors[route['vehicle']])).add_to(m)

# Save the map as an HTML file
m.save("newcheck.html")
