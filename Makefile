CC = g++
includes = include
args = -I $(includes) -std=c++0x -llua5.2 -ldl -Wall
objdir = obj
source = src
build = build

_objects = main.o LuaAdapter/lua_adapter.o
objects = $(patsubst %, $(objdir)/%, $(_objects))
#sources = $(patsubst %, $(source)/%, $(_objects))
#headers := $(wildcard $(include)/*.h)

luamake: $(objects) 
	g++ -o $(build)/$@ $(objects) $(args)

$(objdir)/%.o: $(source)/%.cpp
	mkdir -p $(@D)
	g++ -o $@ -c $^ $(args) 

.PHONY: clean

clean:
	rm -f -r $(objdir)/* 