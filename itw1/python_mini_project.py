from scipy import signal 
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
disaster = pd.read_csv("disaster.csv")

#-----------------------------------------------------------------------------------------------------------------------------------------------

# PART 1


drought = disaster[disaster["Entity"] == "Drought"]
x1 = drought["Year"]
y1 = drought["Deaths"]
plt.subplot(2, 2, 1)
plt.plot(x1, y1, label = "Drought")
earthquake = disaster[disaster["Entity"] == "Earthquake"]
x2 = earthquake["Year"]
y2 = earthquake["Deaths"]
plt.plot(x2, y2, label = "Earthquake")
epid = disaster[disaster["Entity"] == "Epidemic"]
x3 = epid["Year"]
y3 = epid["Deaths"]
plt.plot(x3, y3, label = "Epidemic")
ext_temp = disaster[disaster["Entity"] == "Extreme temperature"]
x4 = ext_temp["Year"]
y4 = ext_temp["Deaths"]
plt.plot(x4, y4, label = "Extreme temperature")
ext_weather = disaster[disaster["Entity"] == "Extreme weather"]
x5 = ext_weather["Year"]
y5 = ext_weather["Deaths"]
plt.plot(x5, y5, label = "Extreme weather")
flood = disaster[disaster["Entity"] == "Floods"]
x6 = flood["Year"]
y6 = flood["Deaths"]
plt.plot(x6, y6, label = "Floods")
landslide = disaster[disaster["Entity"] == "Landslide"]
x7 = landslide["Year"]
y7 = landslide["Deaths"]
plt.plot(x7, y7, label = "landslide")
vol_act = disaster[disaster["Entity"] == "Volcanic activity"]
x8 = vol_act["Year"]
y8 = vol_act["Deaths"]
plt.plot(x8, y8, label = "Volcanic activity")
wildfire = disaster[disaster["Entity"] == "Wildfire"]
x9 = wildfire["Year"]
y9 = wildfire["Deaths"]
plt.plot(x9, y9, label = "Wildfire")

plt.xlabel("Year")
plt.ylabel("Deaths")
plt.title("Natural Disaster and Casulity Year wise", fontweight="bold")
plt.legend()
# #plt.plot(x, y)
# #plt.show()

#-----------------------------------------------------------------------------------------------------------------------------------------------

# PART 2

year = disaster[disaster["Year"] == 1947]
year = year.drop(46)
#print(year)
x = year["Entity"]
y = year["Deaths"]
plt.subplot(2, 2, 3)
c = ['blue', 'red', 'orange', 'green']
plt.bar(x, y, color=c)
plt.xlabel("Different Natural Disasters")
plt.ylabel("Number of Deaths")
plt.title("Number of people died in 1947", fontweight="bold")
plt.locator_params(axis="y", nbins=10)
# plt.ticklabel_format(style='plain')
# plt.tick_params(axis='x', rotation=90)

#-----------------------------------------------------------------------------------------------------------------------------------------------

# PART 3

drought = disaster[disaster["Entity"] == "Drought"]
total_drought = drought["Deaths"].sum()
earthquake = disaster[disaster["Entity"] == "Earthquake"]
total_earthquake = earthquake["Deaths"].sum()
epid = disaster[disaster["Entity"] == "Epidemic"]
total_epid = epid["Deaths"].sum()
ext_temp = disaster[disaster["Entity"] == "Extreme temperature"]
total_temperature = ext_temp["Deaths"].sum()
ext_weather = disaster[disaster["Entity"] == "Extreme weather"]
total_ext_weather = ext_weather["Deaths"].sum()
flood = disaster[disaster["Entity"] == "Floods"]
total_floods = flood["Deaths"].sum()
landslide = disaster[disaster["Entity"] == "Landslide"]
total_landslide = landslide["Deaths"].sum()
vol_act = disaster[disaster["Entity"] == "Volcanic activity"]
total_volcano = vol_act["Deaths"].sum()
wildfire = disaster[disaster["Entity"] == "Wildfire"]
total_wildfire = wildfire["Deaths"].sum()


arr = [total_drought, total_earthquake, total_epid, total_temperature, total_ext_weather, total_landslide]
x = ['Drought', 'Earthquake', 'Epidemic', 'Extreme Temperature', 'Extreme Weather', 'Landslide']
plt.subplot(2, 2, 4)
myexplode = [0.075, 0, 0, 0, 0, 0]
plt.gca().axis("equal")
centre_circle = plt.Circle((0,0),0.70,fc='white')
fig = plt.gcf()
fig.gca().add_artist(centre_circle)
plt.pie(arr, labels=x, explode=myexplode)
plt.legend(loc="upper right", fontsize=7, bbox_transform=plt.gcf().transFigure)
plt.title("Distribution of total number of deaths caused by major disasters", fontweight="bold")



#plt.tight_layout()
#plt.show()
#-------------------------------------------------------------------------------------------------------------

#Use of OOP in Python:

# PART 4

class Deaths:
    by_drought = drought["Deaths"]
    by_earthquake = earthquake["Deaths"]
    by_epidemic = epid["Deaths"]
    by_xtreme_temp = ext_temp["Deaths"]
    by_xtreme_weather = ext_weather["Deaths"]
    by_floods = flood["Deaths"]
    by_landslides = landslide["Deaths"]
    by_volcanoes = vol_act["Deaths"]
    by_wildfire = wildfire["Deaths"]

    def printdeaths(self):
        print(self.by_drought)

deathcount = Deaths()
#deathcount.printdeaths()

drought_deaths = drought["Deaths"]

def calc_deaths(list):
    deatharr = []
    for x in list:
        deatharr.append(x)
    deatharr = np.array(deatharr)    

    sum = 0
    for x in deatharr:
        sum = sum + x
    return sum    


# tot_volcano_deaths = calc_deaths(vol_act["Deaths"])   
#print("Deaths dur to volcanic eruptions = ", tot_volcano_deaths) 

tot_volcano_deaths = calc_deaths(Deaths.by_volcanoes)
tot_drought_deaths = calc_deaths(Deaths.by_drought)
tot_epid_deaths = calc_deaths(Deaths.by_epidemic)
tot_earthquake_deaths = calc_deaths(Deaths.by_earthquake)
tot_volerup_deaths = calc_deaths(Deaths.by_volcanoes)
tot_exttemp_deaths = calc_deaths(Deaths.by_xtreme_temp)
tot_extweather_deaths = calc_deaths(Deaths.by_xtreme_weather)
tot_landslides_deaths = calc_deaths(Deaths.by_landslides)
tot_floods_deaths = calc_deaths(Deaths.by_floods)
tot_wildfire_deaths = calc_deaths(Deaths.by_wildfire)

#-----------------------------------------------------------------------------------------------------------------------------------------------

# PART 5

deaths = np.array([tot_drought_deaths, tot_earthquake_deaths, tot_epid_deaths, tot_exttemp_deaths, tot_extweather_deaths, tot_floods_deaths, tot_landslides_deaths, tot_volerup_deaths, tot_wildfire_deaths])
calamity_name = np.array(["Droughts", "Earthquakes", "Epidemics", "Extreme Temp", "Extreme Weather", "Floods", "Landslides", "Volcanic Eruptions", "Wildfires"])
plt.subplot(2, 2, 2)
plt.barh(calamity_name, deaths, color = "#9467bd")
plt.title("Total Casualaties Due To Different Calamities", fontweight = "bold")
plt.xlabel("Calamities")
plt.ylabel("Casualties")
plt.tight_layout()
plt.show()

#Calculating maximum and minimum deaths :

max_deaths = deaths[0]
for i in deaths:
    if i > max_deaths:
        max_deaths = i

min_deaths = deaths[0]
for i in deaths:
    if i < min_deaths:
        min_deaths = i

#Dictionary that stores (key:value) pairs as 'Deaths:Calamity' :
dict = {
    tot_drought_deaths : "Droughts",
    tot_earthquake_deaths : "Earthquakes",
    tot_epid_deaths : "Epidemics",
    tot_exttemp_deaths : "Extreme Temperature",
    tot_floods_deaths : "Floods",
    tot_extweather_deaths : "Extreme Weather",
    tot_landslides_deaths : "Landslides",
    tot_volerup_deaths : "Volcanic Eruptions",
    tot_wildfire_deaths : "Wildfires"
}
    
x_ = dict[min_deaths]

y_ = dict[max_deaths]

#An audio message indicating the minimum and maximum deaths along with the calamity:

from gtts import gTTS
  
import os
  
#msg = 'Maximum deaths are caused due to ' + y_ + ', which equal to about' + str(max_deaths) + '. However, minimum casualties are due to ' + x_ + ', which equal to ' + str(min_deaths) + 'deaths.'
msg = "सबसे अधिकतम मौतें " + y_ + " से हुई हैं, जो हैं " + str(max_deaths) + ", और सबसे कम मौतें " + x_ + " कि वजह से हुई हैं , जो हैं " + str(min_deaths)  
language = 'hi'
  
myobj = gTTS(text=msg, lang=language, slow=False)
  
myobj.save("pyprojectvoice.mp3")
  
os.system("start pyprojectvoice.mp3")
