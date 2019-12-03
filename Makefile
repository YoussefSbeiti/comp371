# OBJS specifies which files to compile as part of the project
OBJS = main.cpp Geometry/Geometry.hpp Geometry/Geometry.cpp Camera/Camera.hpp Camera/Camera.cpp Shader/Shader.h Glad/glad.c Geometry/stb_image.h Material/Material.hpp Mesh/Mesh.hpp Mesh/Mesh.cpp 3dObjects/Orientation.hpp 3dObjects/Orientation.cpp 3dObjects/Car.h Light/PointLight.hpp  Light/PointLight.cpp Light/DirectionalLight.hpp Light/DirectionalLight.cpp

# CC specifies which compiler we're using
CC = g++ -std=c++11

# COMPILER_FLAGS specifies the additional compilation options we're using
# -Wall will turn on all standard warnings
COMPILER_FLAGS = -Wall

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGL -lGLU -lglut -lGLEW -lglfw -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor 

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
