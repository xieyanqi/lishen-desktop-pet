#include "../tests/SvgCanvas.hpp"
static Animation animation;
static std::string svg;
extern "C" {
void letter(int vk){animation.letter(vk);}
void glasses(){animation.preview(Action::Glasses);}
const char* render(double dt,float x,float y,int hovered){
 animation.hovered=hovered;
 animation.tick(dt,x,y);
 SvgCanvas canvas;canvas.out<<std::fixed<<std::setprecision(2);character(canvas,animation);
 svg=canvas.out.str();return svg.c_str();
}
unsigned length(){return svg.size();}
}
