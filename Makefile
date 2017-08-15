CC = g++
includes = include
args = -I $(includes) -std=c++17 -llua5.3 -ldl -Wall -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs
objdir = obj
source = src
build = build

_objects = main.o Entity/Entity.o LuaSprite.o
objects = $(patsubst %, $(objdir)/%, $(_objects))
#sources = $(patsubst %, $(source)/%, $(_objects))
#headers := $(wildcard $(include)/*.h)

luamake: $(objects) 
	g++ -g -o $(build)/$@ $(objects) $(args)

$(objdir)/%.o: $(source)/%.cpp
	mkdir -p $(@D)
	g++ -g -o $@ -c $^ $(args) 

.PHONY: clean

clean:
	rm -f -r $(objdir)/* 
