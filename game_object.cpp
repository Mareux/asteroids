//
// Created by Mariia Nosko on 10.01.2020.
//

#include "game_object.h"

void GameObject :: movement() {
    positionX += (directionX * speed);
    positionY += (directionY * speed);
}

void GameObject :: getObjectFromUnderworld(int map_width, int map_height)
{
    if (positionX - width / 2.0 > map_width)
        positionX = - width / 2.0;
    else if (positionX + width < 0)
        positionX = map_width + width / 2.0;
    if (positionY - height / 2.0 > map_height)
        positionY = - height / 2.0;
    else if (positionY + height < 0)
        positionY = map_height + height / 2.0;
}

bool GameObject :: collision(double x, double y, int w, int h) {
    if (positionX + w / 2.0 < x - w / 2.0 )
        return false;
    if (positionX - w / 2.0 > x + w / 2.0 )
        return false;
    if (positionY + h / 2.0 < y - h / 2.0 )
        return false;
    if(positionY - h / 2.0 > y + h / 2.0)
        return false;
    return true;
}

void GameObject :: setSpeed(double s) {
    speed = s;
}

void GameObject :: setDirection(double x, double y){
    directionX = x;
    directionY = y;
}

double GameObject :: getDirectionX(){
    return directionX;
}

double GameObject :: getDirectionY(){
    return directionY;
}

void GameObject :: setObjectSize(int w, int h) {
    width = w;
    height = h;
}

int GameObject :: getWidth(){
    return width;
}

int GameObject :: getHeight(){
    return height;
}

void GameObject :: setPositionX(double x){
    positionX = x;
}

void GameObject :: setPositionY(double y){
    positionY = y;
}

int GameObject :: getLeftUpX() {
    return (int)positionX;
}

int GameObject :: getLeftUpY() {
    return (int)positionY;
}

int GameObject :: getRightDownX() {
    return int(positionX + width);
}

double GameObject :: getRightDownY() {
    return (positionY + height);
}

int GameObject :: getScreenX() {
    return int(positionX - width / 2.0);
}

int GameObject :: getScreenY() {
    return int(positionY - height / 2.0);
}

double GameObject :: getSpeed(){
    return speed;
}

