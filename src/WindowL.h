#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <tuple>

class WindowL {
private:
    std::map<std::string, sf::View> views;
    sf::RenderWindow window;

public:
    WindowL(std::string title, unsigned int width, unsigned int height);
    void draw(sf::Sprite sprite);                                                                              
    void close();                                                                               
    std::tuple<int, int> getWindowSize();                                                       
    void setWindowSize(unsigned int width, unsigned int height);                                
    void setWindowTitle(std::string title);                                                     
    void setWindowIcon(std::string icon);                                                       
    void setVSync(bool val);                                                                    
    void setCursorVisiblity(bool val);                                                          
    void setMouseCursorGrabbed(bool val);                       
    void setFrameLimit(unsigned int limit);                                                              
    void setJoystickThreshold(float threshold);                                                 
    void setView(std::string id);                                                               
    //std::string getCurrentViewID();                                                                   
    std::tuple<float, float> mapPixelToCoords(int x, int y);                                    
    std::tuple<float, float> mapPixelToCoordsThroughView(int x, int y, std::string id);                         
    std::tuple<int, int> mapCoordsToPixel(float x, float y);                                    
    std::tuple<int, int> mapCoordsToPixelThroughView(float x, float y, std::string id);                         
    std::tuple<int,int,int,int> getViewDimensions(std::string view);                            
    std::tuple<int, int> getRenderSize();                                                       
    void addView(std::string id, float centerX, float centerY, float width, float height);       
    void removeView(std::string id);                                                                          
    std::tuple<float, float> getViewCenter(std::string id);                                     
    void setViewCenter(std::string id, float x, float y);                                       
    std::tuple<float, float> getViewSize(std::string id);                                       
    void setViewSize(std::string id, float width, float height);                                
    float getViewRotation(std::string id);                                                      
    void setViewRotation(std::string id, float angle);                                          
    void moveView(std::string id, float x, float y);                                            
    void rotateView(std::string id, float angle);                                               
    void zoomView(std::string id, float factor);       
    bool viewContainsPoint(std::string id, float x, float y);
    sf::RenderWindow& getWindow();
};
