import math
import json

# Modelos utilizados para cada um dos astros
ringFile = "../../Scenes/3dFiles/ring.3d"
planetFile = "../../Scenes/3dFiles/planeta.3d"
dwarfPlanetFile = "../../Scenes/3dFiles/planetaAnao.3d"
sunFile = "../../Scenes/3dFiles/sol.3d"
moonFile = "../../Scenes/3dFiles/lua.3d"
asteroidFile = "../../Scenes/3dFiles/asteroid3.3d"
cometFile = "../../Scenes/3dFiles/cometa.3d"

radius_Scale = 15 # Escala a aplicar aos raios
distance_Scale_UA = 200 # Escala a aplicar a distâncias exceto às que envolvem as luas
distance_Scale_UL = 100*(1/384400) # Escala a aplicar à distância das luas

def sun(data,f):
    raioSol = str(data['sun'][0]['relative_radius']*radius_Scale)

    f.write("\t<group>\n")
    f.write("\t\t<scale X=\"" + raioSol + "\" Y= \"" + raioSol + "\" Z= \"" + raioSol + "\"/>\n")
    f.write("\t\t<models>\n")
    f.write("\t\t\t<model file=\""+sunFile+"\"/>\n")
    f.write("\t\t</models>\n")
    f.write("\t</group>\n")

def rings(planet,f):
    f.write("\t\t\t\t<group>\n")
    f.write("\t\t\t\t<rotate angle =\"" + str(planet['axis_inclination']) + "\" axisX=\"0\" axisY=\"0\" axisZ=\"1\"/>\n")
    f.write("\t\t\t\t<models>\n")
    f.write("\t\t\t\t\t\t<model file=\""+ringFile+"\"/>")
    f.write("\n\t\t\t\t</models>\n")
    f.write("\t\t\t\t</group>\n")

def planets(data,f):
    f.write("\t<group>\n")
    for planet in data['Planets']:
        novoRaioPlaneta = planet['relative_radius']*radius_Scale
        novaDistPlaneta = distance_Scale_UA*((planet['distance_to_sun']*150e6 - data['sun'][0]['radius'] - planet['radius'])/150e6)+radius_Scale*data['sun'][0]['relative_radius'] + novoRaioPlaneta
        f.write("\t\t<group>\n")
        f.write("\t\t\t<rotate angle=\"Rand(0.0,360.0)\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
        f.write("\t\t\t<translate X=\"" +str(novaDistPlaneta)+"\"/>\n")
        f.write("\t\t\t<scale X=\"" + str(novoRaioPlaneta)+ "\" Y= \"" +str(novoRaioPlaneta)+  "\" Z= \"" +str(novoRaioPlaneta)+ "\"/>\n")
        f.write("\t\t\t<models>\n")
        f.write("\t\t\t\t<model file=\"" + planetFile + "\"/>\n")
        f.write("\t\t\t</models>\n")
        if planet['rings'] == 'True':
            rings(planet,f)
        for moon in planet['Moons']:
            raioLua = moon['radius']
            raioPlaneta = planet['radius']
            distanciaLua = moon['distance_to_planet']
            novoRaioLua = moon['relative_radius'] * radius_Scale
            distanciaSemRaios = distanciaLua - raioLua - raioPlaneta
            novaDistLua = distanciaSemRaios*distance_Scale_UL + radius_Scale * planet['relative_radius'] + radius_Scale*moon['relative_radius']
            f.write("\t\t\t<group>\n")
            f.write("\t\t\t\t<rotate angle=\"Rand(0.0,360.0)\" axisX=\"0\" axisY=\"1\" axisZ=\"0\"/>\n")
            f.write("\t\t\t\t<translate Z=\"" + str(novaDistLua/novoRaioPlaneta) + "\"/>\n")
            f.write("\t\t\t\t<scale X=\"" + str(novoRaioLua/novoRaioPlaneta) + "\" Y= \"" + str(novoRaioLua/novoRaioPlaneta) +  "\" Z= \"" + str(novoRaioLua/novoRaioPlaneta) + "\"/>\n")
            f.write("\t\t\t\t<models>\n")
            f.write("\t\t\t\t\t<model file=\""+moonFile+"\"/>\n")
            f.write("\t\t\t\t</models>\n")
            f.write("\t\t\t</group>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def dwarfPlanets(data,f):
    f.write("\t<group>\n")
    for dwarfPlanet in data['Dwarf_planets']:
        novoRaioPlaneta = dwarfPlanet['relative_radius']*radius_Scale
        novaDistPlaneta = dwarfPlanet['distance_to_sun']*distance_Scale_UA
        f.write("\t\t<group>\n")
        f.write("\t\t\t<translate X=\"" +str(novaDistPlaneta)+"\"/>\n")
        f.write("\t\t\t<scale X=\"" + str(novoRaioPlaneta)+ "\" Y= \"" +str(novoRaioPlaneta)+  "\" Z= \"" +str(novoRaioPlaneta)+ "\"/>\n")
        f.write("\t\t\t<models>\n")
        f.write("\t\t\t\t<model file=\""+dwarfPlanetFile+"\"/>\n")
        f.write("\t\t\t</models>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def comets(data,f):
    f.write("\t<group>\n")
    for comet in data['Comets']:
        novoRaio = comet['relative_radius']*radius_Scale
        novaDist = comet['aphelion']*distance_Scale_UA
        f.write("\t\t<group>\n")
        f.write("\t\t\t<translate X=\"" +str(novaDist)+"\"/>\n")
        f.write("\t\t\t<scale X=\"" + str(novoRaio)+ "\" Y= \"" +str(novoRaio)+  "\" Z= \"" +str(novoRaio)+ "\"/>\n")
        f.write("\t\t\t<models>\n")
        f.write("\t\t\t\t<model file=\""+cometFile+"\"/>\n")
        f.write("\t\t\t</models>\n")
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
        f.write("\t\t\t\t<model file=\""+asteroidFile+"\"/>\n")
        f.write("\t\t\t</models>\n")
        f.write("\t\t</group>\n")
    f.write("\t</group>\n")

def main():
    out = input("Qual é o ficheiro de output: ")
    f = open(out,"w")
    json_file = open("solarSystem.json","r")
    data = json.load(json_file)
    f.write("<scene>\n")
    sun(data,f)
    planets(data,f)
    dwarfPlanets(data,f)
    comets(data,f)
    asteroids(data,f)
    f.write("</scene>")
    json_file.close()
    f.close()

if __name__ == "__main__":
    main()

