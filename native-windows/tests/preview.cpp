#include "SvgCanvas.hpp"
int main(){
 for(int action=0;action<3;action++)for(int i=0;i<120;i++) {
   Animation a;a.time=double(i)/30; a.action=static_cast<Action>(action);a.actionStart=0;
   if(action==1){
     auto tap=[](double t){return t<.24?std::pow(std::sin(t/.24*3.141592653589793),2):0.0;};
     a.pulseLeft=tap(std::fmod(a.time,.40));
     a.pulseRight=tap(std::fmod(a.time+.20,.40));
   }
   SvgCanvas c;c.out<<std::fixed<<std::setprecision(2);character(c,a);
   std::cout<<action<<"\t"<<i<<"\t"<<c.out.str()<<"\n";
 }
}
