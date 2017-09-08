#include "WindowL.h"

WindowL::WindowL(std::string title, unsigned int width, unsigned int height):
    window(sf::VideoMode(width, height), title) {
}

void WindowL::draw(sf::Sprite sprite){
    this->window.draw(sprite); 
}   
//renderTarget.draw
void WindowL::close(){
    this->window.close();
}   

sf::RenderWindow& WindowL::getWindow(){
    return this->window;
}

std::tuple<int, int> WindowL::getWindowSize(){
    return std::make_tuple(window.getSize().x, window.getSize().y);
}   

void WindowL::setWindowSize(unsigned int width, unsigned int height){
    window.setSize(sf::Vector2u(width, height));
}   

void WindowL::setWindowTitle(std::string title){
    window.setTitle(title);
}   

void WindowL::setWindowIcon(std::string icon){ //TODO

}   

void WindowL::setVSync(bool val){
    window.setVerticalSyncEnabled(val);
}   

void WindowL::setCursorVisiblity(bool val){
    window.setMouseCursorVisible(val);
}   

void WindowL::setMouseCursorGrabbed(bool val){
    window.setMouseCursorGrabbed(val);
}   

void WindowL::setFrameLimit(unsigned int limit){
    window.setFramerateLimit(limit);
}   

void WindowL::setJoystickThreshold(float threshold){
    window.setJoystickThreshold(threshold);
}   
                       
std::tuple<float, float> WindowL::mapPixelToCoords(int x, int y){
    sf::Vector2f out = window.mapPixelToCoords(sf::Vector2i(x, y));
    return std::make_tuple(out.x, out.y);
}   

std::tuple<float, float> WindowL::mapPixelToCoordsThroughView(int x, int y, std::string id){
    sf::Vector2f out = window.mapPixelToCoords(sf::Vector2i(x, y), views[id]);
    return std::make_tuple(out.x, out.y);
}   

std::tuple<int, int> WindowL::mapCoordsToPixel(float x, float y){
    sf::Vector2i out = window.mapCoordsToPixel(sf::Vector2f(x, y));
    return std::make_tuple(out.x, out.y);
}   

std::tuple<int, int> WindowL::mapCoordsToPixelThroughView(float x, float y, std::string id){
    sf::Vector2i out = window.mapCoordsToPixel(sf::Vector2f(x, y), views[id]);
    return std::make_tuple(out.x, out.y);
}   

std::tuple<int, int> WindowL::getRenderSize(){
    auto out = window.getSize();
    return std::make_tuple(out.x, out.y);
}  

void WindowL::setView(std::string id){
    window.setView(views[id]);
}   

//std::string WindowL::getCurrentViewID(){

//}   
//renderTarget.getView  


void WindowL::addView(std::string id, float centerX, float centerY, float width,float height){
    sf::View view(sf::Vector2f(centerX, centerY), sf::Vector2f(width, height));
    views[id] = view;
}   

void WindowL::removeView(std::string id){
    views.erase(id);
}   

std::tuple<float, float> WindowL::getViewCenter(std::string id){
    sf::Vector2f out = views[id].getCenter();
    return std::make_tuple(out.x, out.y);
}   

void WindowL::setViewCenter(std::string id, float x, float y){
    views[id].setCenter(x, y);
}   

std::tuple<float, float> WindowL::getViewSize(std::string id){
    sf::Vector2f out = views[id].getSize();
    return std::make_tuple(out.x, out.y);
}   

void WindowL::setViewSize(std::string id, float width, float height){
    views[id].setSize(width, height);
}   

float WindowL::getViewRotation(std::string id){
    return views[id].getRotation();
}   

void WindowL::setViewRotation(std::string id, float angle){
    views[id].setRotation(angle);
}   

void WindowL::moveView(std::string id, float x, float y){
    views[id].move(x, y);
}   

void WindowL::rotateView(std::string id, float angle){
    views[id].rotate(angle);
}   

void WindowL::zoomView(std::string id, float factor){
    views[id].zoom(factor);
}   

bool WindowL::viewContainsPoint(std::string id, float x, float y){
    return window.getViewport(views[id]).contains(x,y);
}

std::tuple<int,int,int,int> WindowL::getViewDimensions(std::string view){
    sf::FloatRect rect = views[view].getViewport();
    return std::make_tuple(rect.left, rect.top, rect.width, rect.height);
}
