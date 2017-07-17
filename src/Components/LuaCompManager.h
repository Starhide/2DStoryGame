namespace luacomp{
extern std::map<std::string, sol::table> components;

static void createComponent(std::string type, sol::table& t){
    components[type]["new"]

}

} //end ns luacomp