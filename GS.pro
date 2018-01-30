TEMPLATE = subdirs
SUBDIRS = \
    GS/3rdparty/flann \
    GS/3rdparty/rrt \
    GS/UAV-Forge-New.pro


CONFIG += ordered
rrt.depends = flann
UAV-Forge-New.depends = rrt flann
