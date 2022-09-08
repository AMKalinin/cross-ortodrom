import numpy as np
from scipy.optimize import fsolve


p1 = np.array([55+45/60+7/3600, 37+36/60+56/3600])
p2 = np.array([59 + 53/60 + 39/3600, 30+19/60])
p3 = np.array([53+53/60+59/3600, 27+34/60])
p4 = np.array([59+13/60+26/3600, 39+53/60+2/3600])

def distance_between_coord(p1,p2):

    """ Расстояние в метрах между точками в градусах.
    y -- широта, x -- долгота."""

    y1, x1 = p1 
    y2, x2 = p2
    R = 6371110 # средний радиус по СК-42 и высота полёта

    # из градусов в радианы
    x1 = np.radians(x1)
    x2 = np.radians(x2)
    y1 = np.radians(y1)
    y2 = np.radians(y2)

    delta_lambda = x2 - x1
    p1 = np.sin(delta_lambda) * np.cos(y2)
    p2 = np.cos(y1) * np.sin(y2) - np.sin(y1) * np.cos(y2) * np.cos(delta_lambda)
    q = np.sin(y1) * np.sin(y2) + np.cos(y1) * np.cos(y2) * np.cos(delta_lambda)
    return abs(np.arctan2(np.sqrt(p1**2 + p2**2), q) * R)

# def distance_between_coord(p1,p2):

#     """ Расстояние в метрах между точками в градусах.
#     y -- широта, x -- долгота."""

#     y1, x1 = p1 
#     y2, x2 = p2

#     x1 = np.radians(x1)
#     x2 = np.radians(x2)
#     y1 = np.radians(y1)
#     y2 = np.radians(y2)

#     v = np.sin(y1)*np.sin(y2)+np.cos(y1)*np.cos(y2)*np.cos(x1-x2)
#     if v >= 1:
#         m = 0
#     elif v <= -1:
#         m = 10800
#     else:
#         m = 10800*np.arccos(v)/np.pi/0.00053996
#     return m

def formula1(start1, end1, start2, end2):
    p1_r = np.deg2rad(start1)
    p2_r = np.deg2rad(end1)
    p3_r = np.deg2rad(start2)
    p4_r = np.deg2rad(end2)

    p1_decart = np.array([np.cos(p1_r[0])*np.cos(p1_r[1]), np.cos(p1_r[0])*np.sin(p1_r[1]),  np.sin(p1_r[0])])
    p2_decart = np.array([np.cos(p2_r[0])*np.cos(p2_r[1]), np.cos(p2_r[0])*np.sin(p2_r[1]),  np.sin(p2_r[0])])
    p3_decart = np.array([np.cos(p3_r[0])*np.cos(p3_r[1]), np.cos(p3_r[0])*np.sin(p3_r[1]),  np.sin(p3_r[0])])
    p4_decart = np.array([np.cos(p4_r[0])*np.cos(p4_r[1]), np.cos(p4_r[0])*np.sin(p4_r[1]),  np.sin(p4_r[0])])

    v1 = np.cross(p1_decart, p2_decart)
    v2 = np.cross(p3_decart, p4_decart)

    u1 = v1/np.linalg.norm(v1)
    u2 = v2/np.linalg.norm(v2)

    d = np.cross(u1, u2)
    s1 = d/np.linalg.norm(d)
    s2 = -d/np.linalg.norm(d)

    lat1 = np.arcsin(s1[2])
    tmp = np.cos(lat1)
    sign = np.arcsin(s1[1]/tmp)
    if sign<0:
        lon1 = -abs(np.arccos(s1[0]/tmp))
    else:
        lon1 = np.arccos(s1[0]/tmp)
    
    lat1 = np.rad2deg(lat1)
    lon1 = np.rad2deg(lon1)

    lat2 = np.arcsin(s2[2])
    tmp = np.cos(lat2)
    sign = np.arcsin(s2[1]/tmp)
    if sign<0:
        lon2 = -abs(np.arccos(s2[0]/tmp))
    else:
        lon2 = np.arccos(s2[0]/tmp)

    lat2 = np.rad2deg(lat2)
    lon2 = np.rad2deg(lon2)

    obsh_dist1 = distance_between_coord(start1, end1)
    #test = distance_between_coord((0,0), (0,180))
    dist_do1 = distance_between_coord(start1, (lat1,lon1))
    dist_posle1 = distance_between_coord((lat1,lon1), end1)

    obsh_dist2 = distance_between_coord(start2, end2)
    dist_do2 = distance_between_coord(start2, (lat1,lon1))
    dist_posle2 = distance_between_coord((lat1,lon1), end2)

    a = obsh_dist1-dist_do1-dist_posle1
    b = obsh_dist2-dist_do2-dist_posle2
    prov = abs(a - b)
    if prov<=0.01:
        return (lat1, lon1)
    else:
        obsh_dist1 = distance_between_coord(start1, end1)
        dist_do1 = distance_between_coord(start1, (lat2,lon2))
        dist_posle1 = distance_between_coord((lat2,lon2), end1)

        obsh_dist2 = distance_between_coord(start2, end2)
        dist_do2 = distance_between_coord(start2, (lat2,lon2))
        dist_posle2 = distance_between_coord((lat2,lon2), end2)
        a = obsh_dist1-dist_do1-dist_posle1
        b = obsh_dist2-dist_do2-dist_posle2
        prov = abs(a - b)
        if prov<=0.01:
            return (lat2,lon2)
        else:
            print("что-то не так")

print(formula1(p1,p2,p3,p4))

p1 = np.array([-4.167194, -75.211180])
p2 = np.array([-19.592274, -43.821958])
p3 = np.array([-6.340083, -37.593191])
p4 = np.array([-18.879524, -101.986141])
print(formula1(p1,p2,p3,p4))



p1 = np.array([70.85974052371462, -125.37596200099908])
p2 = np.array([52.03095389264921, -65.81547861334019])
p3 = np.array([65.92435905335503, -138.11013842217648])
p4 = np.array([69.96831459928825, -84.59435903191195])

print(formula1(p1,p2,p3,p4))
