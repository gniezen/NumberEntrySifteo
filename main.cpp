/*
 * 
 * Author: Gerrit Niezen
 * 
 * Modified from Sifteo Stars SDK Example.
 */

#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

static const unsigned gNumCubes = 1;
Random gRandom;
int tileNr = 6;
float oldBG = 0.0f;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(GameAssets);

//static AssetSlot NumberSlot = AssetSlot::allocate();

static Metadata M = Metadata()
    .title("Stars SDK Example")
    .package("edu.swansea.numsifteo", "1.0")
    .icon(Icon)
    .cubeRange(gNumCubes);


class StarDemo {
public:
//    static const float bgScrollSpeed = 10.0f;
    static const float bgTiltSpeed = 10.0f;

    void init(CubeID cube)
    {
        frame = 0;
        bg.x = 0;
        bg.y = 0;

        vid.initMode(BG0);
        vid.attach(cube);

        // Number consists of 6 tiles (144x24)
        for(int i=0; i<6; i++) {
            vid.bg0.image(vec(0,i*3), Numbers,i);
        }

    }

    int round(float f)
    {
        return floor(f*5 + 0.5)/5;
    }
    
    void update(TimeDelta timeStep)
    {
        // Get accelerometer value
        Int2 accel = vid.physicalAccel().xy();

        frame++;
        fpsTimespan += timeStep;

        Float2 bgVelocity = accel * bgTiltSpeed + vec(0.0f, -1.0f); 
        bg += float(timeStep) * bgVelocity;
        vid.bg0.setPanning(vec(0.0f,bg.y).round());

        LOG("%d %d\n",round(bg.y),(tileNr-5)*24);

        if(bg.y >oldBG) {
            //increasing

            if( abs(round(bg.y)) > abs(((tileNr-5)*24)) )  {
                LOG("Increasing Tilenr: %d\n",tileNr);
                


                    vid.bg0.image(vec(0, tileNr % 6 * 3), Numbers,tileNr % 60);
                    tileNr++;

            }
        } /*else{
            //decreasing
            if( abs(round(bg.y)) > abs(((tileNr-5)*24)) )  {
                LOG("Decreasing Tilenr: %d\n",tileNr); 
                tileNr--;
                vid.bg0.image(vec(0, (tileNr % 6 + 6) * 3), Numbers,tileNr % 60);
            }
        }*/
    



        oldBG = bg.y;

    }

private:   
    
    VideoBuffer vid;
    unsigned frame;
    Float2 bg;
    float fpsTimespan;

};


void main()
{
    static StarDemo instances[gNumCubes];

    for (unsigned i = 0; i < arraysize(instances); i++)
        instances[i].init(i);
    
    TimeStep ts;
    while (1) {
        for (unsigned i = 0; i < arraysize(instances); i++)
            instances[i].update(ts.delta());

        System::paint();
        ts.next();
    }
}
