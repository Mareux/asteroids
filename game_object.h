#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
    virtual void movement();

    void getObjectFromUnderworld(int map_width, int map_height);

    bool collision(double x, double y, int w, int h);

    void setSpeed(double s);

    void setDirection(double x, double y);

    double getDirectionX();

    double getDirectionY();

    void setObjectSize(int w, int h);

    int getWidth();

    int getHeight();

    void setPositionX(double x);

    void setPositionY(double y);

    int getLeftUpX();

    int getLeftUpY();

    int getRightDownX();

    double getRightDownY();

    int getScreenX();

    int getScreenY();

    double getSpeed();

protected:
    double positionX, positionY;
    double speed;
    double directionX, directionY;
    int width, height;
};


#endif