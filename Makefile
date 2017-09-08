CC = g++
includes = include
args = -I "include" -L "lib" -std=c++17 -llua -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs
objdir = obj
source = src
build = build

_objects = main.o LuaSprite.o WindowL.o
objects = $(patsubst %, $(objdir)/%, $(_objects))
#sources = $(patsubst %, $(source)/%, $(_objects))
#headers := $(wildcard $(include)/*.h)

luamake.exe: $(objects) 
	g++ -o $(build)/$@ $(objects) $(args)

$(objdir)/%.o: $(source)/%.cpp
	if not exist "$(@D)" mkdir "$(@D)"
	g++ -o $@ -c $^ $(args) 

.PHONY: clean

clean:
	rm -f -r $(objdir)/* 
