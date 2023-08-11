import math
import json
import csv 

# Modelos utilizados para cada um dos astros
ringFile = "../../Scenes/3dFiles/ring.3d"
planetFile = "../../Scenes/3dFiles/planeta.3d"
dwarfPlanetFile = "../../Scenes/3dFiles/planetaAnao.3d"
sunFile = "../../Scenes/3dFiles/sol.3d"
moonFile = "../../Scenes/3dFiles/lua.3d"
asteroidFile = "../../Scenes/3dFiles/asteroid3.3d"
cometFile = "../../Scenes/3dFiles/teapot.3d"
textureFolder = "../../Textures/"

catmullRomPoints = 8 #número de pontos das curvas de catmull rom

timeScaleTranslation = 0.1 #Escala a aplicar aos tempos de translacao dos planetas

timeScaleMoonTranslation = 10 #Escala a aplicar aos tempos de translacao das luas

timeScaleRotation = 10 #Escala a aplicar aos tempos de rotacao dos planetas

timeScaleMoonRotation = 10 #Escala a aplicar aos tempos de rotacao das luas

inclinationScale = 0.01 #Escala aplicada à inclinacao das orbitas dos planetas

inclinationComet = 1 #Escala aplicada à inclinacao da órbita do cometa

radius_Scale = 15 # Escala a aplicar aos raios

distance_Scale_UA = 200 # Escala a aplicar a distâncias exceto às que envolvem as luas

distance_Scale_UL = 100 * (1/384400) # Escala a aplicar à distância das luas

def writeOrbitPoints(f,tabs, points):
    for (x,y,z) in points:
        f.write("\n" + tabs + "<point X=\""+str(x)+"\" Y=\""+str(y)+"\" Z=\""+str(z)+"\"/>")


def getOrbitPointsPlanets(a, eccentricity, inclination):
    b = math.sqrt(pow(a,2)-pow((eccentricity * a),2))
    maxH = a*math.sin(inclination*inclinationScale)

    res = []
    step = 2*math.pi/(catmullRomPoints)
    for i in range(0,catmullRomPoints):
        x = a * math.sin(i * step)
        z = b * math.cos(i * step)
        res.append((x, (x*maxH)/a, z))
    
    return res

def getOrbitPointsMoon(radius):
    res = []
    step = 2*math.pi/(catmullRomPoints)
    for i in range(0,catmullRomPoints):
        res.append((radius*math.sin(i*step), 0, radius*math.cos(i*step)))
    return res 

def sun(data,f):
    raioSol = str(data['sun'][0]['relative_radius']*radius_Scale)
    f.write("\t<group>\n")
    f.write("\t\t\t\t<rotate time=\"" + str(data['sun'][0]['rotation_period']*timeScaleRotation) +"\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
    f.write("\t\t<scale X=\"" + raioSol + "\" Y= \"" + raioSol + "\" Z= \"" + raioSol + "\"/>\n")
    f.write("\t\t<models>\n")
    f.write("\t\t\t<model file=\"" + sunFile + "\" texture=\"" + textureFolder+data['sun'][0]['texture']+"\" flagLight=\"false\"/>\n")
    f.write("\t\t</models>\n")
    f.write("\t</group>\n")

def rings(planet,f):
    f.write("\t\t\t\t<group>\n")
    
    f.write("\t\t\t\t<models>\n")
    f.write("\t\t\t\t\t\t<model file=\""+ringFile+"\" texture =\""+textureFolder+planet['texture_rings']+"\"/>")
    f.write("\n\t\t\t</models>\n")
    f.write("\t\t\t\t</group>\n")

def planets(data,f):
    f.write("\t<group>\n")
    for planet in data['Planets']:
        novoRaioPlaneta = planet['relative_radius']*radius_Scale
        novaDistPlaneta = distance_Scale_UA*((planet['distance_to_sun']*150e6 - data['sun'][0]['radius'] - planet['radius'])/150e6)+radius_Scale*data['sun'][0]['relative_radius'] + novoRaioPlaneta
        planetOrbit = getOrbitPointsPlanets(novaDistPlaneta, planet['eccentricity'], planet['inclination'])
        f.write("\t\t<group>\n")
        f.write("\t\t\t<translate time=\""+str(planet['orbital_period']*timeScaleTranslation)+"\">")
        writeOrbitPoints(f,"\t\t\t\t",planetOrbit)
        f.write("\n\t\t\t</translate>")
        f.write("\n\t\t\t<group>\n")
        f.write("\t\t\t\t<rotate angle =\"" + str(planet['axis_inclination']) + "\" axisX=\"0\" axisY=\"0\" axisZ=\"1\"/>\n")
        f.write("\t\t\t\t<rotate time=\"" + str(planet['rotation_period']*timeScaleRotation) +"\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
        f.write("\t\t\t\t<scale X=\"" + str(novoRaioPlaneta)+ "\" Y= \"" +str(novoRaioPlaneta)+  "\" Z= \"" +str(novoRaioPlaneta)+ "\"/>\n")
        f.write("\t\t\t\t<models>\n")
        f.write("\t\t\t\t\t<model file=\"" + planetFile + "\" texture=\"" + textureFolder+planet['texture'] + "\" />\n")
        f.write("\t\t\t\t</models>\n")
        if planet['rings'] == 'True':
            rings(planet,f)
        f.write("\n\t\t\t</group>\n")
        for moon in planet['Moons']:
            raioLua = moon['radius']
            raioPlaneta = planet['radius']
            distanciaLua = moon['distance_to_planet']
            novoRaioLua = moon['relative_radius'] * radius_Scale
            distanciaSemRaios = distanciaLua - raioLua - raioPlaneta
            novaDistLua = distanciaSemRaios*distance_Scale_UL + radius_Scale * planet['relative_radius'] + radius_Scale*moon['relative_radius']
            moonOrbit = getOrbitPointsMoon(novaDistLua)
            f.write("\t\t\t<group>\n")
            f.write("\t\t\t<translate time=\""+str(moon['orbital_period']*timeScaleMoonTranslation)+"\">")
            writeOrbitPoints(f,"\t\t\t\t",moonOrbit)
            f.write("\n\t\t\t</translate>")
            if moon['rotation_period'] > 0:
                f.write("\n\t\t\t<rotate time=\""+str(moon['rotation_period']*timeScaleMoonRotation)+"\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
            f.write("\n\t\t\t\t<scale X=\"" + str(novoRaioLua) + "\" Y= \"" + str(novoRaioLua) +  "\" Z= \"" + str(novoRaioLua) + "\"/>\n")
            f.write("\t\t\t\t<models>\n")
            if moon['texture'] != "":
                f.write("\t\t\t\t\t<model file=\"" + moonFile + "\" texture=\""+textureFolder + moon['texture']+"\"/>\n")
            else:
                f.write("\t\t\t\t\t<model file=\"" + moonFile + "\"/>\n")
            f.write("\t\t\t\t</models>\n")
            f.write("\t\t\t</group>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def dwarfPlanets(data,f):
    f.write("\t<group>\n")
    for dwarfPlanet in data['Dwarf_planets']:
        novoRaioPlaneta = dwarfPlanet['relative_radius']*radius_Scale
        novaDistPlaneta = dwarfPlanet['distance_to_sun']*distance_Scale_UA
        planetOrbit = getOrbitPointsPlanets(novaDistPlaneta, dwarfPlanet['eccentricity'], dwarfPlanet['inclination'])
        f.write("\t\t<group>\n")
        f.write("\t\t\t<translate time=\""+str(dwarfPlanet['orbital_period']*timeScaleTranslation)+"\">")
        writeOrbitPoints(f,"\t\t\t\t",planetOrbit)
        f.write("\n\t\t\t</translate>")
        f.write("\t\t\t\t<rotate angle =\"" + str(dwarfPlanet['axis_inclination']) + "\" axisX=\"0\" axisY=\"0\" axisZ=\"1\"/>\n")
        f.write("\t\t\t\t<rotate time=\"" + str(dwarfPlanet['rotation_period']*timeScaleRotation) +"\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
        f.write("\t\t\t<scale X=\"" + str(novoRaioPlaneta)+ "\" Y= \"" +str(novoRaioPlaneta)+  "\" Z= \"" +str(novoRaioPlaneta)+ "\"/>\n")
        f.write("\t\t\t<models>\n")
        if dwarfPlanet['texture'] != "":
            f.write("\t\t\t\t<model file=\""+dwarfPlanetFile+"\" texture=\""+textureFolder+dwarfPlanet['texture']+"\" />\n")
        else:
            f.write("\t\t\t\t<model file=\""+dwarfPlanetFile+"\"/>\n")
        f.write("\t\t\t</models>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")


def getOrbitPointsComet(a, eccentricity, inclination):
    b = math.sqrt(pow(a,2) - pow((eccentricity * a),2))
    maxH = b*math.cos(inclination*inclinationComet)

    res = []

    step = 2*math.pi/(catmullRomPoints)
    for i in range(0,catmullRomPoints):
        x = a * math.sin(i * step)
        z = b * math.cos(i * step)
        res.append((x, (z*maxH)/b, z))
    
    return res

def applyVec(points, vec):
    res = []
    for (x1,y1,z1) in points:
        res.append((x1+vec[0],y1+vec[1],z1+vec[2]))
    return res


def comets(data,f):
    f.write("\t<group>\n")
    for comet in data['Comets']:
        novoRaio = comet['relative_radius']*radius_Scale
        novaDist = comet['aphelion']*distance_Scale_UA
        midPoint  = ((comet['aphelion'] + comet['perihelion'])* distance_Scale_UA)/2
        points = getOrbitPointsComet(midPoint,comet['eccentricity'], comet['inclination'])
        
        points = applyVec(points, (midPoint-comet['perihelion']*distance_Scale_UA-data['sun'][0]['relative_radius']*radius_Scale,0,0))
        
        f.write("\t\t<group>\n")
        f.write("\t\t\t<translate time=\"" + str(comet['orbital_period'] * 0.005)+"\">")
        writeOrbitPoints(f,"\t\t\t\t", points)
        f.write("\n\t\t\t</translate>")
        f.write("\t\t\t<scale X=\"" + str(novoRaio)+ "\" Y= \"" +str(novoRaio)+  "\" Z= \"" +str(novoRaio)+ "\"/>\n")
        f.write("\t\t\t<group>\n")
        f.write("\t\t\t<rotate angle=\"90\" axisX=\"1\" axisY=\"0\" axisZ=\"0\"/>\n")
        f.write("\t\t\t\t<models>\n")
        f.write("\t\t\t\t\t<model file=\""+cometFile+"\" texture=\"" + textureFolder+comet["texture"] + "\"/>\n")
        f.write("\t\t\t\t</models>\n")
        f.write("\t\t\t</group>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def asteroids(data,f):
    f.write("\t<group>\n")

    for asteroid_belt in data['Asteroid_belts']:
        novoTamanho = asteroid_belt['relative_radius']*radius_Scale
        raioInterior = str(asteroid_belt['inner_radius']*distance_Scale_UA)
        raioExterior = str(asteroid_belt['outter_radius']*distance_Scale_UA)
        f.write("\t\t<group>\n")
        f.write("\t\t\t<replicate N=\"200\"/>\n")
        f.write("\t\t\t<rotate angle=\"Rand(0.0,360.0)\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
        f.write("\t\t\t<translate X=\"Rand("+raioInterior+","+raioExterior+")\" Y=\"Rand(-50,50)\"/>\n")
        f.write("\t\t\t<scale X=\"" + str(novoTamanho)+ "\" Y= \"" +str(novoTamanho)+  "\" Z= \"" +str(novoTamanho)+ "\"/>\n")
        f.write("\t\t\t<models>\n")
        f.write("\t\t\t\t<model file=\"" + asteroidFile + "\" texture=\""+textureFolder+asteroid_belt["texture"]+"\"/>\n")
        f.write("\t\t\t</models>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def writeLights(lights, f):
    f.write("\t<lights>\n")
    for light in lights:
        f.write("\t\t<light type=\""+light[0]+"\" posX=\""+light[1]+"\" posY=\""+light[2]+"\" posZ=\""+light[3]+"\" />\n")
    f.write("\t</lights>\n")

def main():
    out = input("Qual é o ficheiro de output: ")
    f = open(out,"w")
    json_file = open("solarSystem.json","r")
    lights_file = open("lights.csv","r")
    lights = csv.reader(lights_file)
    next(lights)
    data = json.load(json_file)
    f.write("<scene>\n")
    writeLights(lights, f)
    sun(data,f)
    planets(data,f)
    dwarfPlanets(data,f)
    comets(data,f)
    asteroids(data,f)
    f.write("</scene>")
    json_file.close()
    lights_file.close()
    f.close()

if __name__ == "__main__":
    main()
